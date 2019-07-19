<?php
/**
 * @file
 * wim_external_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_external_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return ["version" => "1"];
  }
}
