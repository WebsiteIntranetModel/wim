<?php
/**
 * @file
 * wim_search.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_search_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "apachesolr" && $api == "apachesolr_environments") {
    return ["version" => "1"];
  }
  if ($module == "apachesolr_search" && $api == "apachesolr_search_defaults") {
    return ["version" => "3"];
  }
  if ($module == "facetapi" && $api == "facetapi_defaults") {
    return ["version" => "1"];
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}
