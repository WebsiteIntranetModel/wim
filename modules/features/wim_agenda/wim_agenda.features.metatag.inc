<?php
/**
 * @file
 * wim_agenda.features.metatag.inc
 */

/**
 * Implements hook_metatag_export_default().
 */
function wim_agenda_metatag_export_default() {
  $config = array();

  // Exported Metatag config instance: node:agenda.
  $config['node:agenda'] = array(
    'instance' => 'node:agenda',
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
