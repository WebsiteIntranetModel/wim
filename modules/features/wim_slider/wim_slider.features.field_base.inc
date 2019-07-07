<?php
/**
 * @file
 * wim_slider.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_slider_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_slide_item'.
  $field_bases['field_slide_item'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_slide_item',
    'indexes' => [],
    'locked' => 0,
    'module' => 'paragraphs',
    'settings' => [],
    'translatable' => 0,
    'type' => 'paragraphs',
  ];

  return $field_bases;
}
