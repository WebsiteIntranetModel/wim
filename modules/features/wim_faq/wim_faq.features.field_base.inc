<?php
/**
 * @file
 * wim_faq.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_faq_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_faq_additional_information'.
  $field_bases['field_faq_additional_information'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_faq_additional_information',
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

  // Exported field_base: 'field_faq_category'.
  $field_bases['field_faq_category'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_faq_category',
    'indexes' => [
      'tid' => [
        0 => 'tid',
      ],
    ],
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => [
      'allowed_values' => [
        0 => [
          'vocabulary' => 'faq_categories',
          'parent' => 0,
        ],
      ],
    ],
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  ];

  // Exported field_base: 'field_show_on_overview'.
  $field_bases['field_show_on_overview'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_show_on_overview',
    'indexes' => [
      'value' => [
        0 => 'value',
      ],
    ],
    'locked' => 0,
    'module' => 'list',
    'settings' => [
      'allowed_values' => [
        0 => '',
        1 => '',
      ],
      'allowed_values_function' => '',
    ],
    'translatable' => 0,
    'type' => 'list_boolean',
  ];

  // Exported field_base: 'field_weight'.
  $field_bases['field_weight'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_weight',
    'indexes' => [
      'value' => [
        0 => 'value',
      ],
    ],
    'locked' => 0,
    'module' => 'weight',
    'settings' => [],
    'translatable' => 0,
    'type' => 'weight',
  ];

  return $field_bases;
}
