<?php
/**
 * @file
 * wim_product.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_product_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:product.
  $config['node:product'] = array(
    'instance' => 'node:product',
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
