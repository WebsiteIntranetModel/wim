<?php

/**
 * @file
 * wim_linked_keywords.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_linked_keywords_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_external_description'.
  $field_bases['field_external_description'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_external_description',
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

  // Exported field_base: 'field_external_title'.
  $field_bases['field_external_title'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_external_title',
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

  // Exported field_base: 'field_referenced_content'.
  $field_bases['field_referenced_content'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_referenced_content',
    'indexes' => [],
    'locked' => 0,
    'module' => 'link',
    'settings' => [
      'attributes' => [
        'class' => '',
        'rel' => '',
        'target' => 'default',
      ],
      'display' => [
        'url_cutoff' => 80,
      ],
      'enable_tokens' => 1,
      'title' => 'optional',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
    ],
    'translatable' => 0,
    'type' => 'link_field',
  ];

  // Exported field_base: 'field_reminder_email'.
  $field_bases['field_reminder_email'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_reminder_email',
    'indexes' => [],
    'locked' => 0,
    'module' => 'email',
    'settings' => [],
    'translatable' => 0,
    'type' => 'email',
  ];

  return $field_bases;
}
