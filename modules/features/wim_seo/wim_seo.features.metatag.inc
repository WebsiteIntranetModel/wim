<?php
/**
 * @file
 * wim_seo.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_seo_metatag_export_default() {
  $config = [];

  // Exported Metatag config instance: global.
  $config['global'] = [
    'instance' => 'global',
    'disabled' => FALSE,
    'config' => [
      'title' => [
        'value' => '[current-page:title] | [current-page:pager][site:name]',
      ],
      'generator' => [
        'value' => 'Drupal 7 (http://drupal.org)',
      ],
      'canonical' => [
        'value' => '[current-page:url:absolute]',
      ],
      'shortlink' => [
        'value' => '[current-page:url:unaliased]',
      ],
    ],
  ];

  // Exported Metatag config instance: user.
  $config['user'] = [
    'instance' => 'user',
    'disabled' => TRUE,
    'config' => [
      'title' => [
        'value' => '[user:name] | [site:name]',
      ],
    ],
  ];

  return $config;
}
