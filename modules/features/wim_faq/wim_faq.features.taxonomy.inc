<?php
/**
 * @file
 * wim_faq.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wim_faq_taxonomy_default_vocabularies() {
  return [
    'faq_categories' => [
      'name' => 'FAQ Categories',
      'machine_name' => 'faq_categories',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ],
  ];
}
