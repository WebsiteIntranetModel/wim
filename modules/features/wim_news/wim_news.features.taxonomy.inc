<?php
/**
 * @file
 * wim_news.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wim_news_taxonomy_default_vocabularies() {
  return [
    'news_categories' => [
      'name' => 'News Categories',
      'machine_name' => 'news_categories',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ],
  ];
}
