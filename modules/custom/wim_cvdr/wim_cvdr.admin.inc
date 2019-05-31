<?php

/**
 * @file
 * WIM CVDR file for the admin interface.
 */

/**
 * Generate admin form.
 *
 * @return array
 *   Containing the form elements.
 */
function _wim_cvdr_admin_page() {
  $form = [];

  // Create textfield for setting webservice url.
  $form['wim_cvdr_url'] = [
    '#type' => 'textfield',
    '#maxlength' => 600,
    '#size' => 200,
    '#title' => t('CVDR XML URL'),
    '#description' => t('The full URL to the webservice which outputs an XML file.'),
    '#required' => TRUE,
    '#default_value' => variable_get('wim_cvdr_url', ''),
  ];

  // Modify subject source
  $form['wim_cvdr_subject_source'] = [
    '#type' => 'radios',
    '#title' => t('Source of subject'),
    '#options' => [
      'overheidrg:onderwerp' => t('Onderwerp'),
      'dcterms:subject' => t('Beleidsonderwerp'),
    ],
    '#default_value' => variable_get('wim_cvdr_subject_source', 'overheidrg:onderwerp'),
  ];

  // Allow to modify the cache time.
  $form['wim_cvdr_cache_time'] = [
    '#type' => 'select',
    '#title' => t('Cache time'),
    '#description' => t('The time the results from the webservice should be cached. 
        This is done to reduce load time and decrease the requests to the webservice.
        <br /><strong>Lowering this value will severly hurt performance!</strong>'),
    '#options' => [
      0 => t('No caching (hurts performance!)'),
      15 => t('15 minutes'),
      30 => t('30 minutes'),
      60 => t('1 hour'),
      120 => t('2 hours'),
      360 => t('6 hours'),
      720 => t('12 hours'),
      1440 => t('1 day'),
      10080 => t('1 week'),
    ],
    '#default_value' => variable_get('wim_cvdr_cache_time', 60),
  ];

  $form['wim_cvdr_max_visible'] = [
    '#type' => 'textfield',
    '#description' => t('Specify how much items should be visible before adding a "more button".'),
    '#title' => t('Visible items'),
    '#default_value' => variable_get('wim_cvdr_max_visible', 5),
  ];

  return system_settings_form($form);
}
