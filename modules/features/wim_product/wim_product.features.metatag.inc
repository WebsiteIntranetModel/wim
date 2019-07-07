<?php
/**
 * @file
 * wim_product.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_product_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: node:product.
  $config['node:product'] = [
    'instance' => 'node:product',
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
