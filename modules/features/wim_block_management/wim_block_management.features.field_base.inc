<?php
/**
 * @file
 * wim_block_management.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_block_management_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_aria_label'.
  $field_bases['field_aria_label'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_aria_label',
    'indexes' => [
      'format' => [
        0 => 'format',
      ],
    ],
    'locked' => 0,
    'module' => 'text',
    'settings' => [
      'max_length' => 255,
    ],
    'translatable' => 0,
    'type' => 'text',
  ];

  // Exported field_base: 'field_body'.
  $field_bases['field_body'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_body',
    'indexes' => [
      'format' => [
        0 => 'format',
      ],
    ],
    'locked' => 0,
    'module' => 'text',
    'settings' => [],
    'translatable' => 0,
    'type' => 'text_long',
  ];

  // Exported field_base: 'field_title'.
  $field_bases['field_title'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_title',
    'indexes' => [
      'format' => [
        0 => 'format',
      ],
    ],
    'locked' => 0,
    'module' => 'text',
    'settings' => [
      'max_length' => 255,
    ],
    'translatable' => 0,
    'type' => 'text',
  ];

  return $field_bases;
}
