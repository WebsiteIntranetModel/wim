<?php
/**
 * @file
 * wim_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "breakpoints" && $api == "default_breakpoint_group") {
    return ["version" => "1"];
  }
  if ($module == "elysia_cron" && $api == "default_elysia_cron_rules") {
    return ["version" => "1"];
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return ["version" => "2"];
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_views_api().
 */
function wim_core_views_api($module = NULL, $api = NULL) {
  return ["api" => "3.0"];
}
