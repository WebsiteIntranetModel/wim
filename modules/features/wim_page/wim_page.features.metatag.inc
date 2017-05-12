<?php
/**
 * @file
 * wim_page.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_page_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:page.
  $config['node:page'] = array(
    'instance' => 'node:page',
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
