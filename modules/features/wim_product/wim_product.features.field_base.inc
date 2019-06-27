<?php
/**
 * @file
 * wim_product.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_product_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_product_avg'.
  $field_bases['field_product_avg'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_avg',
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

  // Exported field_base: 'field_product_upl'.
  $field_bases['field_product_upl'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_upl',
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
  
  return $field_bases;
}
