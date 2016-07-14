<?php
/**
 * @file
 * wim_agenda.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_agenda_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function wim_agenda_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function wim_agenda_node_info() {
  $items = array(
    'agenda' => array(
      'name' => t('Agenda'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
