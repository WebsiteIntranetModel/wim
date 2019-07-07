<?php
/**
 * @file
 * wim_agenda.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_agenda_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: node:agenda.
  $config['node:agenda'] = [
    'instance' => 'node:agenda',
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
