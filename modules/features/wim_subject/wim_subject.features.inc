<?php
/**
 * @file
 * wim_subject.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_subject_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_node_info().
 */
function wim_subject_node_info() {
  $items = [
    'subject_page' => [
      'name' => t('Subject page'),
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
