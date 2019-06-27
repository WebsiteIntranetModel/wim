<?php
/**
 * @file
 * wim_news.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_news_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: node:news.
  $config['node:news'] = [
    'instance' => 'node:news',
    'disabled' => FALSE,
    'config' => [
      'title' => [
        'value' => '[node:title] | [site:name]',
      ],
      'image_src' => [
        'value' => '[node:field_image]',
      ],
    ],
  ];

  return $config;
}
