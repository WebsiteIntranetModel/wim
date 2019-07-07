<?php
/**
 * @file
 * wim_faq.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_faq_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: node:faq.
  $config['node:faq'] = [
    'instance' => 'node:faq',
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
