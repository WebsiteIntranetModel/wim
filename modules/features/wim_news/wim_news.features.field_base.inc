<?php
/**
 * @file
 * wim_news.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_news_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_news_category'.
  $field_bases['field_news_category'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_news_category',
    'indexes' => [
      'tid' => [
        0 => 'tid',
      ],
    ],
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => [
      'allowed_values' => [
        0 => [
          'vocabulary' => 'news_categories',
          'parent' => 0,
        ],
      ],
    ],
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  ];

  return $field_bases;
}
