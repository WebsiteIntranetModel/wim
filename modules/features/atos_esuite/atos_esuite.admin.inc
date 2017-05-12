<?php
/**
 * @file
 * Administration forms for Atos E-suite.
 */

/**
 * Form callback for 'admin/settings/config/atos-esuite'.
 */
function atos_esuite_admin_settings_form($form, &$form_state) {
  $form = array();

  // Actions.
  $form['atos_esuite_actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Atos esuite actions'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
  );
  $form['atos_esuite_actions']['run-all'] = array(
    '#type' => 'submit',
    '#value' => t('Start import'),
    '#submit' => array('atos_esuite_batch_run_all_submit'),
  );

  if (user_access('administer site configuration')) {
    // Settings.
    $form['atos_esuite_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Settings'),
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
    );
    $form['atos_esuite_settings']['atos_esuite_url'] = array(
      '#type' => 'textfield',
      '#title' => t('Atos search callback'),
      '#default_value' => variable_get('atos_esuite_url', ''),
      '#description' => t('Full url to the search.xml callback. Do not include a query string.'),
    );

    $form['atos_esuite_settings']['atos_esuite_chunk_size'] = array(
      '#type' => 'textfield',
      '#title' => t('Chunk site'),
      '#default_value' => variable_get('atos_esuite_chunk_size', 100),
      '#description' => t('Number of items to fetch per request'),
    );
  }

  return system_settings_form($form);
}

/**
 * Run all submit handler for atos_esuite page.
 */
function atos_esuite_batch_run_all_submit($form, &$form_state) {
  if (variable_get('atos_esuite_url', '')) {
    module_load_include('inc', 'atos_esuite', 'atos_esuite.import');
    atos_esuite_import_batch_start();
  }
  else {
    drupal_set_message(t('Atos search callback is not set or settings are not saved. Please set correct callback.'), 'error');
  }
}
