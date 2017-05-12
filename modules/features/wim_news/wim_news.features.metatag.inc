<?php
/**
 * @file
 * wim_news.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_news_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:news.
  $config['node:news'] = array(
    'instance' => 'node:news',
    'disabled' => FALSE,
    'config' => array(
      'title' => array(
        'value' => '[node:title] | [site:name]',
      ),
      'image_src' => array(
        'value' => '[node:field_image]',
      ),
    ),
  );

  return $config;
}
