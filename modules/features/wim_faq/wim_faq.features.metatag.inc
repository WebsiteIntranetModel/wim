<?php
/**
 * @file
 * wim_faq.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_faq_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:faq.
  $config['node:faq'] = array(
    'instance' => 'node:faq',
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
