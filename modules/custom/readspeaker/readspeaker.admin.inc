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
  $form['readspeaker_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => variable_get('readspeaker_title', t('Listen to this page using ReadSpeaker')),
  );
  $form['readspeaker_button_text'] = array(
    '#type' => 'textfield',
    '#title' => t('Button text'),
    '#default_value' => variable_get('readspeaker_button_text', t('Listen')),
  );

  return system_settings_form($form);
}
