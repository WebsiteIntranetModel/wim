<?php
/**
 * @file
 * wim_linked_keywords.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_linked_keywords_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function wim_linked_keywords_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function wim_linked_keywords_node_info() {
  $items = array(
    'linked_keywords' => array(
      'name' => t('Linked Keywords'),
      'base' => 'node_content',
      'description' => t('Click on "Search" to select "Related content" and set a higher priority in the search results.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
