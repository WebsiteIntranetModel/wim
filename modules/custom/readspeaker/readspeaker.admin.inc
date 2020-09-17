<?php

/**
 * @file
 * Administration pages.
 */

/**
 * Settings form for Read Speaker.
 */
function readspeaker_settings_form() {
  $form = [];
  $form['readspeaker_customerid'] = [
    '#type' => 'textfield',
    '#title' => t('Customer ID'),
    '#default_value' => variable_get('readspeaker_customerid'),
    '#required' => TRUE,
  ];
  $form['readspeaker_title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => variable_get('readspeaker_title', t('Listen to this page using ReadSpeaker')),
  ];
  $form['readspeaker_button_text'] = [
    '#type' => 'textfield',
    '#title' => t('Button text'),
    '#default_value' => variable_get('readspeaker_button_text', t('Listen')),
  ];

  $form['readspeaker_readfromid'] = [
    '#type' => 'textfield',
    '#title' => t('Lees voor vanaf id'),
    '#description' => t('Add one or more (comma seperated) id\'s or classes where readspeaker should start.<br />What ever appears first in the code will be read first.'),
    '#default_value' => variable_get('readspeaker_readfromid', 'main'),
    '#required' => TRUE,
  ];

  $form['readspeaker_language'] = [
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => readspeaker_supported_languages(),
    '#default_value' => variable_get('readspeaker_language', 'nl_nl'),
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}
