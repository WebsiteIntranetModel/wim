<?php
/**
 * @file
 * wim_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wim_core_taxonomy_default_vocabularies() {
  return [
    'tags' => [
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ],
  ];
}
