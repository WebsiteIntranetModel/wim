<?php
/**
 * @file
 * Additional functions.
 */

/**
 * Private function to get all nodes that require updates.
 */
function _content_reminder_get_required_nodes() {

  $orcond = db_or();
  $types = node_type_get_types();
  $orcondswitch = FALSE;

  foreach ($types as $type) {
    if (variable_get('content_reminder_types_' . $type->type, 0) == 1) {
      $dband = db_and();
      $duedate = time() - (variable_get('content_reminder_types_' . $type->type . '_days', 20) * 86400);
      $dband->condition('n.type', $type->type, '=');
      $dband->condition('n.status', 1, '=');
      $dband->condition('nr.timestamp', $duedate, '<');
      $orcond->condition($dband);
      $orcondswitch = TRUE;
    }
  }

  if ($orcondswitch == TRUE) {
    $query = db_select('node', 'n');
    $query->leftjoin('node_revision', 'nr', 'nr.vid = n.vid');
    $query->leftjoin('users', 'u', 'u.uid = nr.uid');
    $query->fields('n', ['nid', 'title', 'changed', 'type'])
      ->fields('nr', ['status'])
      ->fields('u', ['mail']);
    $query->condition($orcond)->groupBy('n.nid')->orderBy('n.type', 'ASC');
    $results = $query->execute()->fetchAll();

    return $results;
  }
  else {
    return [];
  }
}

/**
 * Private function to send an e-mail with nodes that require an update.
 */
function _content_reminder_prepare_nodes($nodes, $mailtype) {

  $email_nodes = [];
  foreach ($nodes as $node) {
    $send_to_author = variable_get('content_reminder_types_' . $node->type . '_send_to_author', 1);

    if ($send_to_author) {
      if (!isset($email_nodes[$node->mail])) {
        $email_nodes[$node->mail] = [];
      }
      $node->url = l($node->title, 'node/' . $node->nid, ['absolute' => TRUE]);
      $email_nodes[$node->mail][] = $node;
    }
  }

  $loaded_node = [];
  foreach ($nodes as $node) {
    $loaded_node[$node->nid] = node_load($node->nid);
  }

  $emailremindernodes = [];
  foreach ($loaded_node as $node) {
    $emails = [];
    if (!empty($node->field_reminder_email) || !empty(variable_get('content_reminder_types_' . $node->type . '_email'))) {
      // Add the email addresses to the node.
      if (!empty($node->field_reminder_email)) {
        foreach ($node->field_reminder_email[LANGUAGE_NONE] as $mail_list) {
          foreach ($mail_list as $value) {
            $emails[] = $value;
          }
        }
      }
      if (!empty(variable_get('content_reminder_types_' . $node->type . '_email'))) {
        $emails[] = variable_get('content_reminder_types_' . $node->type . '_email');
      }
      $id = implode(',', $emails);
      $emailremindernodes[$id][$node->nid] = new stdClass();
      $emailremindernodes[$id][$node->nid]->nid = $node->nid;
      $emailremindernodes[$id][$node->nid]->title = $node->title;
      $emailremindernodes[$id][$node->nid]->changed = $node->changed;
      $emailremindernodes[$id][$node->nid]->type = $node->type;
      $emailremindernodes[$id][$node->nid]->mail = implode(', ', $emails);
      $emailremindernodes[$id][$node->nid]->status = $node->status;
      $emailremindernodes[$id][$node->nid]->url = l($node->title, 'node/' . $node->nid, ['absolute' => TRUE]);
    }
  }

  if (!empty($email_nodes)) {
    // Mail the node author (user).
    _content_reminder_send_mails($email_nodes, $mailtype);
  }
  // Mail the people defined in the node's "reminder email field".
  _content_reminder_send_mails($emailremindernodes, $mailtype);
}

/**
 * Private function to get expired nodes and update the status to 0 if needed.
 */
function _content_reminder_get_old_nodes() {

  $orcond = db_or();
  $types = node_type_get_types();
  $orcondswitch = FALSE;

  foreach ($types as $type) {
    if (variable_get('content_reminder_types_' . $type->type . '_depub_box', 0) == 1) {
      $dband = db_and();
      $duedate = time() - (variable_get('content_reminder_types_' . $type->type . '_depub', 20) * 86400);
      $dband->condition('n.type', $type->type, '=');
      $dband->condition('n.status', 1, '=');
      $dband->condition('nr.timestamp', $duedate, '<');
      $orcond->condition($dband);
      $orcondswitch = TRUE;
    }
  }

  if ($orcondswitch == TRUE) {
    $query = db_select('node', 'n');
    $query->leftjoin('field_data_field_reminder_email', 're', 're.entity_id = n.nid');
    $query->leftjoin('node_revision', 'nr', 'nr.vid = n.vid');
    $query->leftjoin('users', 'u', 'u.uid = nr.uid');
    $query->fields('n', ['nid', 'title', 'changed', 'type'])
      ->fields('nr', ['status'])
      ->fields('u', ['mail'])
      ->fields('re', ['field_reminder_email_email']);
    $query->condition($orcond)->groupBy('n.nid')->orderBy('n.type', 'ASC');
    $mailnodes = $query->execute()->fetchAll();

    $workbench_exists = module_exists('workbench_moderation');
    if ($workbench_exists) {
      $workbench_to_state = workbench_moderation_state_none();
    }
    foreach ($types as $type) {
      if (variable_get('content_reminder_types_' . $type->type . '_depub_box', 0) == 1) {
        $query = db_select('node_revision', 'nr');
        $query->leftjoin('node', 'n', 'n.vid = nr.vid');
        $query->fields('n', ['nid']);
        $query->condition($orcond);
        $results = $query->execute()->fetchAll();
        foreach ($results as $result) {
          foreach ($mailnodes as &$mailnode) {
            if ($result->nid == $mailnode->nid) {
              $mailnode->status = 0;
            }
          }
          $node = node_load($result->nid);
          // Unpublish the current live revision.
          // @see workbench_moderation_node_history_view()
          // @see workbench_moderation_node_unpublish_form()
          if ($workbench_exists && !empty($node->workbench_moderation['published']) && $node->vid == $node->workbench_moderation['published']->vid) {
            // Remove the moderation record's "published" flag.
            db_update('workbench_moderation_node_history')
              ->condition('hid', $node->workbench_moderation['published']->hid)
              ->fields(['published' => 0])
              ->execute();

            // Moderate the revision.
            workbench_moderation_moderate($node, $workbench_to_state);

            // Make sure the 'current' revision is the 'live'
            // revision -- ie, the revision in {node}.
            $live_revision = workbench_moderation_node_current_load($node);
            $live_revision->status = 0;
            $live_revision->revision = 0;
            $live_revision->workbench_moderation['updating_live_revision'] = TRUE;
            node_save($live_revision);
          }
          else {
            $node->status = 0;
            node_save($node);
          }
        }
      }
    }
    return $mailnodes;
  }
  else {
    return [];
  }

}

/**
 * Private function to send e-mails.
 */
function _content_reminder_send_mails($mailnodes, $mailtype) {
  foreach ($mailnodes as $mail => $nodes) {
    $build = [
      '#theme' => 'content_reminder',
      '#nodes' => $nodes,
      '#mailtype' => $mailtype,
      '#content_reminder_text' => variable_get('content_reminder_' . $mailtype . '_text', 'Inhoud die verlopen is of binnenkort verloopt.'),
    ];

    if ($mailtype === 'expire') {
      $subject = variable_get('content_reminder_expire_subject', '@count item(s) zijn verlopen en offline geplaatst');
    }
    else {
      $subject = variable_get('content_reminder_reminder_subject', 'Je moet @count item(s) bekijken');
    }
    $subject = str_replace('@count', count($nodes), $subject);

    $mail_token = microtime();
    $from = variable_get('site_mail');
    $message = [
      'id' => 'custom_' . $mail_token,
      'to' => $mail,
      'subject' => $subject,
      'body' => drupal_render($build),
      'headers' => [
        'From' => $from,
        'Sender' => $from,
        'Return-Path' => $from,
        'Content-Type' => 'text/html; charset=UTF-8; format=flowed',
      ],
    ];

    $system = drupal_mail_system('custom', $mail_token);
    $system->mail($message);
  }
}

/**
 * Function which validates the entered email address.
 */
function _content_reminder_email_element_validate($element, &$form_state, $form) {
  if (!empty($element['#value']) && !valid_email_address($element['#value'])) {
    form_error($element, t('Please enter a valid email address.'));
  }
}
