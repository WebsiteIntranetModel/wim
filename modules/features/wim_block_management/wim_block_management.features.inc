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
    return ["version" => "5"];
  }
  if ($module == "context" && $api == "context") {
    return ["version" => "3"];
  }
}

/**
 * Implements hook_views_api().
 */
function wim_block_management_views_api($module = NULL, $api = NULL) {
  return ["api" => "3.0"];
}
