<?php

/**
 * @file
 * Form callbacks and handlers.
 */

/**
 * Form callback for settings form.
 */
function sduconnect_settings_form($form, &$form_state) {

  $form['sduconnect_account'] = array(
    '#type' => 'textfield',
    '#title' => t('SduConnect account id'),
    '#description' => t('Only numbers are allowed.'),
    '#default_value' => variable_get('sduconnect_account', ''),
    '#required' => TRUE,
    '#size' => 17,
  );

  return system_settings_form($form);
}

/**
 * Form validate handler for settings form.
 */
function sduconnect_settings_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!preg_match('/^[1-9][0-9]*$/', $values['sduconnect_account'])) {
    form_set_error('sduconnect_account', t('This is not a valid account number.'));
  }
}

/**
 * Form callback for collection form.
 */
function sduconnect_collection_form($form, &$form_state, $collection = NULL) {
  $form['#collection'] = $collection;

  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Type'),
    '#options' => array('pdc' => t('PDC'), 'vac' => t('VAC')),
    '#default_value' => $collection ? $collection->type : 'pdc',
    '#description' => t('Must match the type as known in SduConnect'),
    '#required' => TRUE,
  );

  $form['external_id'] = array(
    '#type' => 'textfield',
    '#title' => t('SDU Collection id'),
    '#default_value' => $collection ? $collection->external_id : '',
    '#description' => t('SDU collection as known in SduConnect.'),
    '#required' => TRUE,
    '#size' => 17,
  );

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $collection ? $collection->name : '',
    '#description' => t('Used for display in admin interface.'),
    '#required' => TRUE,
  );

  if (module_exists('domain')) {
    $domains = db_select('domain', 'd')
      ->fields('d', array('domain_id', 'sitename'))
      ->orderBy('d.is_default', 'desc')
      ->orderBy('d.sitename', 'asc')
      ->execute()
      ->fetchAllKeyed();
    $form['domains'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Publication domains'),
      '#options' => $domains,
      '#default_value' => drupal_map_assoc($collection ? $collection->domains : array(1)),
      '#required' => TRUE,
    );
  }

  $form['frequency'] = array(
    '#type' => 'radios',
    '#title' => t('Frequency'),
    '#options' => drupal_map_assoc(array(3600, 3600 * 3, 3600 * 6, 3600 * 12, 3600 * 24), 'format_interval'),
    '#default_value' => $collection ? $collection->frequency : 3600,
    '#description' => t('Time to wait between imports.'),
  );

  $form['import_private'] = array(
    '#type' => 'checkbox',
    '#title' => t('Import private fields'),
    '#default_value' => $collection ? $collection->import_private : FALSE,
    '#description' => t('Should only be used when not publishing to public domains.'),
  );

  $form['buttons'] = array();
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['buttons']['cancel'] = array(
    '#markup' => l(t('Cancel'), 'admin/config/content/sduconnect'),
  );

  return $form;
}

/**
 * Form validate handler for collection form.
 */
function sduconnect_collection_form_validate($form, &$form_state) {
  $values = $form_state['values'];
  if (!preg_match('/^[1-9][0-9]*$/', $values['external_id'])) {
    form_set_error('external_id', t('This is not a valid collection id.'));
  }
}

/**
 * Form submit handler for collection form.
 */
function sduconnect_collection_form_submit($form, &$form_state) {
  $values = $form_state['values'];

  $collection = $form['#collection'] ? $form['#collection'] : new stdClass();
  $collection->type = $values['type'];
  $collection->external_id = $values['external_id'];
  $collection->name = $values['name'];
  $collection->frequency = $values['frequency'];
  $collection->import_private = $values['import_private'];
  $collection->domains = array_filter(array_values($values['domains']));
  sduconnect_collection_save($collection);

  drupal_set_message(t('The collection %name has been saved.', array('%name' => $collection->name)));

  $form_state['redirect'] = 'admin/config/content/sduconnect';
}

/**
 * Form callback for delete collection form.
 */
function sduconnect_collection_delete_form($form, &$form_state, $collection) {
  $form['#collection'] = $collection;
  $question = t('Are you sure you want to delete the collection %name?', array('%name' => $collection->name));
  return confirm_form($form, $question, 'admin/config/content/sduconnect');
}

/**
 * Form submit handler for delete collection form.
 */
function sduconnect_collection_delete_form_submit($form, &$form_state) {
  $collection = $form['#collection'];

  sduconnect_collection_delete($collection->cid);
  drupal_set_message(t('The collection %name has been deleted.', array('%name' => $collection->name)));

  $form_state['redirect'] = 'admin/config/content/sduconnect';
}

/**
 * Form callback for import collection form.
 */
function sduconnect_collection_import_form($form, &$form_state, $collection) {
  $form['#collection'] = $collection;

  if ($collection->updated_till > REQUEST_TIME - 900) {
    drupal_set_message(t('This import was already started within the last 15 minutes. Starting another import may violate the fair-use policy.'), 'warning');
  }

  $question = t('Do you want to start an import for the collection %name?', array('%name' => $collection->name));
  $description = t('This will add the import job to the queue. After starting the import, you can watch the number of queued items on the overview page.');
  return confirm_form($form, $question, 'admin/config/content/sduconnect', $description);
}

/**
 * Form submit handler for import collection form.
 */
function sduconnect_collection_import_form_submit($form, &$form_state) {
  $collection = $form['#collection'];

  module_load_include('inc', 'sduconnect', 'sduconnect.delta');
  $stats = sduconnect_delta_import($collection);
  if ($stats) {
    drupal_set_message(t('Import is started. Items are queued and processed in cron. Please look at the overview page to see the number of remaining items in the queue.'));
    drupal_set_message(t('There were @added items added, @changed changed and @removed removed.', array(
      '@added' => $stats->added,
      '@changed' => $stats->changed,
      '@removed' => $stats->removed,
    )), 'status');
  }
  else {
    drupal_set_message(t('There was an error retrieving the list of updated items.'), 'error');
  }

  $form_state['redirect'] = 'admin/config/content/sduconnect';
}
