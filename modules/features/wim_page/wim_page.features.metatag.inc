<?php
/**
 * @file
 * wim_page.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_page_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: node:page.
  $config['node:page'] = [
    'instance' => 'node:page',
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
