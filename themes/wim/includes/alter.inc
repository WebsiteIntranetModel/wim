<?php
/**
 * @file
 * The primary PHP file for the Drupal Wim theme.
 *
 * This file contain alter functions.
 */

/**
 * Implements hook_form_views_exposed_form_alter().
 */
function wim_form_views_exposed_form_alter(&$form, &$form_state) {
  if ($form['#id'] === 'views-exposed-form-news-news-overview') {
    $form['#info']['filter-date_filter']['label'] = '';
    $form['date']['min']['#title'] = t('From');
    $form['date']['min']['#date_format'] = variable_get('date_format_short', 'F j, Y');
    $form['date']['max']['#title'] = t('To');
    $form['date']['max']['#date_format'] = variable_get('date_format_short', 'F j, Y');
  }
}

/**
 * Implements hook_date_popup_process_alter().
 */
function wim_date_popup_process_alter(&$element, &$form_state, $context) {
  unset($element['date']['#description']);
  unset($element['time']['#description']);
}
