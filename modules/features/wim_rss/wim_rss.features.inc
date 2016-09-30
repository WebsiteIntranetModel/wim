<?php
/**
 * @file
 * wim_rss.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_rss_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
