<?php
/**
 * @file
 * wim_slider.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_slider_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_slide_item'.
  $field_bases['field_slide_item'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_slide_item',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => array(),
    'translatable' => 0,
    'type' => 'paragraphs',
  );

  return $field_bases;
}
