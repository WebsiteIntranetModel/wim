<?php
/**
 * @file
 * wim_block_management.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_block_management_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
