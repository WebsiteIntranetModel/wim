<?php
/**
 * @file
 * wim_search.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_search_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_attachments_entity_bundle_indexing_document';
  $strongarm->value = 'none';
  $export['apachesolr_attachments_entity_bundle_indexing_document'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_active_modules';
  $strongarm->value = [
    'apachesolr_search' => 'apachesolr_search',
    'file_entity' => 0,
    'node' => 0,
    'user' => 0,
  ];
  $export['search_active_modules'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'search_default_module';
  $strongarm->value = 'apachesolr_search';
  $export['search_default_module'] = $strongarm;

  return $export;
}
