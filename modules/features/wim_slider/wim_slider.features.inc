<?php
/**
 * @file
 * wim_slider.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_slider_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "bean_admin_ui" && $api == "bean") {
    return array("version" => "5");
  }
}
