<?php
/**
 * @file
 * wim_block_management.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_block_management_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "bean_admin_ui" && $api == "bean") {
    return array("version" => "5");
  }
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function wim_block_management_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_paragraphs_info().
 */
function wim_block_management_paragraphs_info() {
  $items = array(
    'slider_item' => array(
      'name' => 'Slider item',
      'bundle' => 'slider_item',
      'locked' => '1',
    ),
  );
  return $items;
}
