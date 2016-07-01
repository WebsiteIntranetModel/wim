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
    $form['field_publication_date_value']['value']['#date_format'] = variable_get('date_format_medium', 'd F Y');
    $form['field_publication_date_value_1']['value']['#date_format'] = variable_get('date_format_medium', 'd F Y');
  }
}

/**
 * Implements hook_date_popup_process_alter().
 */
function wim_date_popup_process_alter(&$element, &$form_state, $context) {
  unset($element['date']['#description'], $element['time']['#description']);
}
