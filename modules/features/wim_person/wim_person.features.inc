<?php
/**
 * @file
 * wim_person.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_person_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_node_info().
 */
function wim_person_node_info() {
  $items = [
    'person' => [
      'name' => t('Person'),
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
