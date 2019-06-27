<?php
/**
 * @file
 * wim_agenda.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_agenda_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return ["version" => "1"];
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_views_api().
 */
function wim_agenda_views_api($module = NULL, $api = NULL) {
  return ["api" => "3.0"];
}

/**
 * Implements hook_node_info().
 */
function wim_agenda_node_info() {
  $items = [
    'agenda' => [
      'name' => t('Agenda'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ],
  ];
  drupal_alter('node_info', $items);
  return $items;
}
