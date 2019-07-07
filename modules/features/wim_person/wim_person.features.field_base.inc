<?php
/**
 * @file
 * wim_person.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_person_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_person_address'.
  $field_bases['field_person_address'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_person_address',
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

  // Exported field_base: 'field_person_phone'.
  $field_bases['field_person_phone'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_person_phone',
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

  // Exported field_base: 'field_person_roles'.
  $field_bases['field_person_roles'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_person_roles',
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
