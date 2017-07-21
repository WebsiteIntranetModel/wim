<?php
/**
 * @file
 * Import for Atos E-suite.
 */

/**
 * Start batch.
 */
function atos_esuite_import_batch_start() {
  $batch = array(
    'operations' => array(),
    'finished' => 'atos_esuite_import_batch_finished',
    'title' => t('Atos eSuite import'),
    'init_message' => t('Preparing import..'),
    'progress_message' => t('Importing...'),
    'error_message' => t('Batch has encountered an error.'),
    'file' => drupal_get_path('module', 'atos_esuite') . '/atos_esuite.import.inc',
  );
  $batch['operations'][] = array(
    'atos_esuite_import_batch_worker',
    array(ATOS_ESUITE_FAQ),
  );
  $batch['operations'][] = array(
    'atos_esuite_import_batch_worker',
    array(ATOS_ESUITE_PRODUCT),
  );
  batch_set($batch);

  if (function_exists('drush_backend_batch_process')) {
    // Drush does not start the batch automatically, but we cannot skip
    // this batch without side effects.
    drush_backend_batch_process();
  }
}

/**
 * Worker callback for batch process.
 *
 * @param string $type
 *   Type of import. Can be vac or pdc.
 * @param array $context
 *   Batch context.
 */
function atos_esuite_import_batch_worker($type, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['done'] = 0;
    $context['sandbox']['max'] = 250;
    $context['sandbox']['last'] = 0;
    $context['sandbox']['page'] = 0;
    $context['sandbox']['errors'] = 0;
    $context['sandbox']['starttime'] = REQUEST_TIME;
  }

  $url = variable_get('atos_esuite_url', '');
  $query = array(
    'rows' => variable_get('atos_esuite_chunk_size', 100),
    'page' => $context['sandbox']['page'],
    'type' => $type,
  );

  $url = url($url, array('external' => TRUE, 'query' => $query));
  if ($result = _atos_esuite_process_feed($url)) {
    list($done, $errors, $total) = $result;
    $context['sandbox']['done'] += $done;
    $context['sandbox']['last'] += variable_get('atos_esuite_chunk_size', 100);
    $context['sandbox']['max'] = $total;
    $context['sandbox']['page']++;
    $context['sandbox']['errors'] += $errors;
  }
  else {
    $context['sandbox']['errors']++;
  }

  $context['message'] = t('Imported @count items.', array(
    '@count' => $context['sandbox']['done'],
  ));

  $context['finished'] = $context['sandbox']['last'] >= $context['sandbox']['max'];
  if ($context['finished']) {
    $mapping = array(
      ATOS_ESUITE_PRODUCT => 'product',
      ATOS_ESUITE_FAQ => 'faq',
    );
    if ($context['sandbox']['done'] > 0) {
      drupal_set_message(format_plural($context['sandbox']['done'], '1 ' . $mapping[$type] . ' node imported successfully. ', '@count ' . $mapping[$type] . ' nodes imported.'));
      _atos_esuite_delete_nodes($context['sandbox']['starttime'], $type);
    }
    else {
      drupal_set_message(t('0 !type node imported.', array('!type' => $mapping[$type])), 'status');
    }
    if ($context['sandbox']['errors'] > 0) {
      drupal_set_message(t('There was some errors during import. Please check logs.'), 'error');
      drupal_mail('atos_esuite', 'failed', variable_get('site_mail'), LANGUAGE_NONE);
    }
    $context['results']['count'] = $context['sandbox']['done'];
  }
}

/**
 * Unpublish nodes which were not found during the batch.
 *
 * @param int $start_time
 *    Timestamp.
 * @param int $type
 *    Type of node.
 */
function _atos_esuite_delete_nodes($start_time, $type) {
  $deleted = array();
  $mapping = array(
    ATOS_ESUITE_PRODUCT => 'product',
    ATOS_ESUITE_FAQ => 'faq',
  );
  // We need to add deduct time from start time,
  // because every time when batch processing a bunch it takes new REQUEST_TIME.
  // We add 5 minute, hope is enough :).
  $start_time -= 5 * 60;
  // Lock the operation.
  if (lock_acquire('atos_esuite_delete')) {
    // There was a count before, .
    $deleted = db_select('atos_esuite', 'a')
      ->fields('a', array(
        'identifier',
        'nid',
      ))
      ->condition('a.changed', $start_time, '<')
      ->condition('a.type', array($mapping[$type]), 'IN')
      ->execute()
      ->fetchAllKeyed();

    if (count($deleted)) {
      // We will mark all items, that we suspect to
      // be removed from feed as unpublished.
      db_update('node')
        ->fields(array('status' => '0'))
        ->condition('nid', array_values($deleted), 'IN')
        ->execute();
      db_update('node_revision')
        ->fields(array('status' => '0'))
        ->condition('nid', array_values($deleted), 'IN')
        ->execute();

      // If a broken feed gets restored,
      // nodes should be automatically published again.
      db_update('atos_esuite')
        ->fields(array('hash' => ''))
        ->condition('identifier', array_keys($deleted), 'IN')
        ->execute();
    }
    lock_release('atos_esuite_delete');
  }

  if (count($deleted)) {
    atos_esuite_notify($deleted, $type);
    drupal_set_message(format_plural(count($deleted), '1 ' . $mapping[$type] . ' node deleted. ', '@count ' . $mapping[$type] . ' nodes deleted.'));
  }
}

/**
 * Batch 'finished' callback.
 */
function atos_esuite_import_batch_finished($success, array $results, array $operations) {
  if (isset($results['count'])) {
    drupal_set_message('Import finished!');
  }
}

/**
 * Request url and process items.
 *
 * @param string $url
 *    URL.
 *
 * @return array
 *   array(int $imported, int $errors, int $total).
 */
function _atos_esuite_process_feed($url) {

  $imported = 0;
  $errors = 0;

  $results = simplexml_load_file($url);

  $total_items = 0;
  if (isset($results->{'total-items'})) {
    $total_items = (int) $results->{'total-items'};
  }
  else {
    watchdog('atos esuite import', 'There is something strange with the feed. Check :url', array(':url' => $url));
  }

  if (isset($results->result)) {
    foreach ($results->result as $data) {
      try {
        $atos_id = atos_esuite_map_node($data->asXML());
        ++$imported;
      }
      catch (Exception $e) {
        ++$errors;
      }
    }
  }

  watchdog('atos esuite batch report', 'Total items: :total. Errors: :errors. Imported: :imported.', array(
    ':total' => $total_items,
    ':errors' => $errors,
    ':imported' => $imported,
  ));

  return array($imported, $errors, $total_items);
}

/**
 * Update node.
 *
 * @param string $documentXML
 *    XML string.
 * @param bool $force
 *    Force saving node.
 *
 * @return object
 *    Node object.
 *
 * @throws \Exception
 * @throws \InvalidMergeQueryException
 *
 * @internal param string $type 'product' or 'vac'
 */
function atos_esuite_map_node($documentXML, $force = FALSE) {
  $xml_hash = md5($documentXML);
  $documentDOM = new DOMDocument();
  $documentDOM->loadXML($documentXML);
  $xpath = new DOMXPath($documentDOM);

  $xml_type = $xpath->query('/result/type')->item(0)->nodeValue;
  switch ($xml_type) {
    case 'Product':
      $type = 'product';
      break;

    case 'Vraag/Antwoord Combinatie':
      $type = 'faq';
      break;

    default:
      return FALSE;
  }

  $id = $type . '-' . trim($xpath->query('/result/id')->item(0)->nodeValue);

  if ($id) {
    if ($type === 'product' && $xml_type === 'Vraag/Antwoord Combinatie') {
      return FALSE;
    }

    // Get the current version from the database.
    $current = db_select('atos_esuite', 'a')->fields('a', array(
      'identifier',
      'type',
      'hash',
      'nid',
    ))->condition('identifier', $id)->execute()->fetchAssoc();

    // Is this an actual update.
    if (!$force && $current && $xml_hash == $current['hash']) {
      // Update the changed date, so we know that this item still exists.
      db_merge('atos_esuite')
        ->key(array('identifier' => $id))
        ->fields(array('changed' => REQUEST_TIME))
        ->execute();
      return FALSE;
    }

    // Are we updating or inserting.
    if ($current && !empty($current['nid'])) {
      $node = node_load($current['nid']);
      $node->status = 1;
    }
    else {
      $node = new stdClass();
      $node->uid = 1;
      $node->type = $type;
      $node->language = LANGUAGE_NONE;
    }

    $node->title = $xpath->query('/result/title')->item(0)->nodeValue;
    $node->created = $xpath->query('/result/created')->item(0)->nodeValue;
    $node->changed = $xpath->query('/result/changed')->item(0)->nodeValue;
    $callback = 'atos_esuite_map_node_' . $type;
    $callback($node, $documentDOM, $xpath);

    node_save($node);

    // Add to the atos_esuite table for hash checking and identifying.
    if ($node->nid) {
      db_merge('atos_esuite')->key(array('identifier' => $id))->fields(array(
        'hash' => $xml_hash,
        'type' => $type,
        'nid' => $node->nid,
        'xml' => $documentXML,
        'changed' => REQUEST_TIME,
      ))->execute();
    }

    return $id;
  }
  else {
    throw new Exception('Could not determine id');
  }

}

/**
 * Fill Product node fields.
 *
 * @param \stdClass $node
 *    Node class.
 * @param \DOMDocument $documentDOM
 *    DOM object.
 * @param \DOMXPath $xpath
 *    XPath object.
 */
function atos_esuite_map_node_product(stdClass $node, DOMDocument $documentDOM, DOMXPath $xpath) {
  // Prevent wrong format.
  $formats = filter_formats();
  $default_format = reset($formats);
  $format = variable_get('atos_default_format', $default_format->format);

  // Description.
  $description = $xpath->query('/result/beschrijving')->item(0)->nodeValue;
  $body = $description;
  if (isset($node->body[LANGUAGE_NONE][0]['summary']) && $node->body[LANGUAGE_NONE][0]['summary']) {
    $summary = $node->body[LANGUAGE_NONE][0]['summary'];
  }
  else {
    $summary = truncate_utf8(strip_tags($description, '<p>'), 250, TRUE);
  }

  // Helper array to map xml tags to fields in node.
  $mapping = array(
    'aanvraag' => 'field_product_procedure',
    'contact' => 'field_product_contact',
    'bezwaar' => 'field_product_objection',
    'kosten' => 'field_product_costs',
    'bijzonderheden' => 'field_product_particulars',
    'termijn' => 'field_product_period',
    'voorwaarden' => 'field_product_conditions',

  );

  // Here we set mapped fields.
  foreach ($mapping as $tag => $filed_name) {
    $$tag = trim($xpath->query('/result/' . $tag)->item(0)->nodeValue);
    if (strlen($$tag) > 0) {
      $node->$filed_name = array(
        LANGUAGE_NONE => array(
          array(
            'value' => $$tag,
            'format' => $format,
          ),
        ),
      );
    }
  }

  // Tags.
  $node->field_tags = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/keywords/keyword') as $item) {
    $node->field_tags[LANGUAGE_NONE][] = array('tid' => atos_esuite_get_term_tid($item->nodeValue));
  }

  // Related FAQ items.
  $node->field_related_faq = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/relatedvac/id') as $item) {
    $node->field_related_faq[LANGUAGE_NONE][] = array('target_id' => 'faq-' . trim($item->nodeValue));
  }

  // Related Products.
  $node->field_related_product = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/relatedpdc/id') as $item) {
    $node->field_related_product[LANGUAGE_NONE][] = array('target_id' => 'product-' . trim($item->nodeValue));
  }

  // Target audience co-operating catalog.
  $node->field_sc_audience = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/doelgroepen/doelgroep') as $item) {
    $node->field_sc_audience[LANGUAGE_NONE][] = array('value' => trim($item->nodeValue));
  }

  // Publication date.
  $pub_date = $xpath->query('/result/created')->item(0)->nodeValue;
  $date[] = array(
    'value' => date('Y-m-d H:i:s', $pub_date),
    'value2' => '',
    'timezone' => variable_get('date_default_timezone'),
    'timezone_db' => 'UTC',
    'date_type' => 'datetime',
  );
  $node->field_publication_date = array(LANGUAGE_NONE => $date);

  $node->body = array(
    LANGUAGE_NONE => array(
      array(
        'value' => $body,
        'summary' => $summary,
        'format' => $format,
      ),
    ),
  );

  // Information stored in Link fields.
  $links_mapping = array(
    'wet' => 'field_product_related_laws',
    // 'field_product_request_online',.
    'formulier' => 'field_product_forms',
    'meer_info' => 'field_product_more_information',
  );

  // Inserting links.
  foreach ($links_mapping as $tag => $filed_name) {
    $$tag = trim($xpath->query('/result/' . $tag)->item(0)->nodeValue);
    if (strlen($$tag) > 0) {
      $node->$filed_name = array(LANGUAGE_NONE => array());
      foreach (_extract_urls($$tag) as $item) {
        $node->{$filed_name}[LANGUAGE_NONE][] = array(
          'url' => isset($item[2]) ? $item[2] : '',
          'title' => isset($item[3]) ? $item[3] : '',
        );
      }
    }
  }
}

/**
 * Fill FAQ node fields.
 *
 * @param \stdClass $node
 *    Node class.
 * @param \DOMDocument $documentDOM
 *    DOM object.
 * @param \DOMXPath $xpath
 *    XPath object.
 */
function atos_esuite_map_node_faq(stdClass $node, DOMDocument $documentDOM, DOMXPath $xpath) {

  // Tags.
  $node->field_tags = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/keywords/keyword') as $item) {
    $node->field_tags[LANGUAGE_NONE][] = array('tid' => atos_esuite_get_term_tid($item->nodeValue));
  }

  // Relate FAQ items.
  $node->field_related_faq = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/relatedvac/id') as $item) {
    $node->field_related_faq[LANGUAGE_NONE][] = array('target_id' => 'faq-' . trim($item->nodeValue));
  }

  // Related Products.
  $node->field_related_product = array(LANGUAGE_NONE => array());
  foreach ($xpath->query('/result/relatedpdc/id') as $item) {
    $node->field_related_product[LANGUAGE_NONE][] = array('target_id' => 'product-' . trim($item->nodeValue));
  }

  // This should be disabled for new items.
  if (!isset($node->nid)) {
    $node->field_show_on_overview[LANGUAGE_NONE][] = array('value' => 0);
  }

  $formats = filter_formats();
  $default_format = reset($formats);
  $format = variable_get('atos_default_format', $default_format->format);

  // Additional information. Actually not used.
  $more_info = trim($xpath->query('/result/meer_info')->item(0)->nodeValue);
  if (strlen($more_info) > 0) {
    $node->field_faq_additional_information = array(
      LANGUAGE_NONE => array(
        array(
          'value' => $more_info,
          'format' => $format,
        ),
      ),
    );
  }

  // Body.
  $node->body = array(
    LANGUAGE_NONE => array(
      array(
        'value' => $xpath->query('/result/antwoord')->item(0)->nodeValue,
        'format' => $format,
      ),
    ),
  );
}

/**
 * Get category term id by given name. Creates new term if not found.
 *
 * @param string $term_name
 *    Term name.
 *
 * @return int
 *    Term id.
 */
function atos_esuite_get_term_tid($term_name) {
  $vocabulary_name = variable_get('atos_esuite_tags_vocabulary_name', 'tags');
  $vocabulary = taxonomy_vocabulary_machine_name_load($vocabulary_name);

  $terms = taxonomy_get_term_by_name($term_name, $vocabulary_name);
  if (!count($terms)) {
    $term = new stdClass();
    $term->vid = $vocabulary->vid;
    $term->name = $term_name;
    taxonomy_term_save($term);
  }
  else {
    $term = reset($terms);
  }

  return $term->tid;
}

/**
 * Helper function to parse links from feed.
 *
 * @param string $input
 *   String containing html <a> tags.
 *
 * @return array
 *   Set of arrays, key 2 -  url, key 3 - title. Empty array if fail.
 */
function _extract_urls($input) {
  $input = strip_tags($input, '<a>');
  if (preg_match_all('/<a\s[^>]*href=(\"??)([^\" >]*?)\\1[^>]*>(.*)<\/a>/siU', $input, $matches, PREG_SET_ORDER)) {
    return $matches;
  }

  return array();
}
