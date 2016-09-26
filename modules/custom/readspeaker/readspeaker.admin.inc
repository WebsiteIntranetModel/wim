<?php
/**
 * @file
 * Administration pages.
 */

/**
 * Settings form for Read Speaker.
 */
function readspeaker_settings_form() {
  $form = array();

  $form['readspeaker_customerid'] = array(
    '#type' => 'textfield',
    '#title' => t('Customer ID'),
    '#default_value' => variable_get('readspeaker_customerid'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
