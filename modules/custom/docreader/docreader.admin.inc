<?php
/**
 * @file
 * Administration pages.
 */

/**
 * List of languages currently supported by docReader.
 *
 * (http://www.readspeaker.com/nl/readspeaker-docreader/).
 */
function docreader_supported_languages() {
  $languages = [
    'nl_nl' => 'Nederlands',
    'fy_nl' => 'Fries',
    'en_uk' => 'Brits Engels',
    'de_de' => 'Duits',
    'fr_fr' => 'Frans',
    'es_es' => 'Spaans',
    'sv_se' => 'Zweeds',
    'no_nb' => 'Noors (Bokmål)',
    'fi_fi' => 'Fins',
    'ru_ru' => 'Russisch',
    'ar_ar' => 'Arabisch',
  ];

  return $languages;
}

/**
 * Form builder.
 */
function docreader_settings_form($form, &$form_state) {
  $form['docreader_cid'] = [
    '#type' => 'textfield',
    '#title' => t('Customer id'),
    '#description' => t('You can ask your customer ID <a href="http://www.readspeaker.com/nl/readspeaker-docreader/">docReader</a>.'),
    '#default_value' => variable_get('docreader_cid', ''),
    '#required' => TRUE,
  ];
  $form['docreader_language'] = [
    '#type' => 'select',
    '#title' => t('Reading Language'),
    '#options' => docreader_supported_languages(),
    '#default_value' => variable_get('docreader_language', 'nl_nl'),
    '#required' => TRUE,
  ];
  $form['docreader_supported_file_extensions'] = [
    '#type' => 'textfield',
    '#title' => t('Supported file extensions'),
    '#default_value' => variable_get('docreader_supported_file_extensions', docreader_supported_file_extensions()),
    '#required' => TRUE,
  ];

  $form['docreader_button_text'] = [
    '#type' => 'textfield',
    '#title' => t('Button text'),
    '#default_value' => variable_get('docreader_button_text', 'Read for'),
    '#required' => TRUE,
  ];

  return system_settings_form($form);
}
