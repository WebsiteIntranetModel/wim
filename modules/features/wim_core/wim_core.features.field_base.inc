<?php
/**
 * @file
 * wim_core.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_core_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'body'.
  $field_bases['body'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [
      0 => 'node',
    ],
    'field_name' => 'body',
    'indexes' => [
      'format' => [
        0 => 'format',
      ],
    ],
    'locked' => 0,
    'module' => 'text',
    'settings' => [],
    'translatable' => 0,
    'type' => 'text_with_summary',
  ];

  // Exported field_base: 'field_attachment'.
  $field_bases['field_attachment'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_attachment',
    'indexes' => [
      'fid' => [
        0 => 'fid',
      ],
    ],
    'locked' => 0,
    'module' => 'file',
    'settings' => [
      'display_default' => 0,
      'display_field' => 0,
      'uri_scheme' => 'public',
    ],
    'translatable' => 0,
    'type' => 'file',
  ];

  // Exported field_base: 'field_email'.
  $field_bases['field_email'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_email',
    'indexes' => [],
    'locked' => 0,
    'module' => 'email',
    'settings' => [],
    'translatable' => 0,
    'type' => 'email',
  ];

  // Exported field_base: 'field_image'.
  $field_bases['field_image'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_image',
    'indexes' => [
      'fid' => [
        0 => 'fid',
      ],
    ],
    'locked' => 0,
    'module' => 'image',
    'settings' => [
      'default_image' => 0,
      'uri_scheme' => 'public',
    ],
    'translatable' => 0,
    'type' => 'image',
  ];

  // Exported field_base: 'field_lead_paragraph'.
  $field_bases['field_lead_paragraph'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_lead_paragraph',
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

  // Exported field_base: 'field_link'.
  $field_bases['field_link'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_link',
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

  // Exported field_base: 'field_location'.
  $field_bases['field_location'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_location',
    'indexes' => [
      'lid' => [
        0 => 'lid',
      ],
    ],
    'locked' => 0,
    'module' => 'location_cck',
    'settings' => [
      'gmap_macro' => '[gmap ]',
      'gmap_marker' => 'drupal',
      'location_settings' => [
        'display' => [
          'hide' => [
            'additional' => 0,
            'city' => 0,
            'coords' => 'coords',
            'country' => 0,
            'country_name' => 0,
            'locpick' => 'locpick',
            'map_link' => 0,
            'name' => 0,
            'postal_code' => 0,
            'province' => 0,
            'province_name' => 0,
            'street' => 0,
          ],
        ],
        'form' => [
          'fields' => [
            'additional' => [
              'collect' => 0,
              'default' => '',
              'weight' => 6,
            ],
            'city' => [
              'collect' => 1,
              'default' => '',
              'weight' => 8,
            ],
            'country' => [
              'collect' => 1,
              'default' => '',
              'weight' => 14,
            ],
            'locpick' => [
              'collect' => 1,
              'weight' => 20,
            ],
            'name' => [
              'collect' => 1,
              'default' => '',
              'weight' => 2,
            ],
            'postal_code' => [
              'collect' => 1,
              'default' => '',
              'weight' => 12,
            ],
            'province' => [
              'collect' => 0,
              'default' => '',
              'weight' => 10,
              'widget' => 'autocomplete',
            ],
            'street' => [
              'collect' => 1,
              'default' => '',
              'weight' => 4,
            ],
          ],
        ],
      ],
    ],
    'translatable' => 0,
    'type' => 'location',
  ];

  // Exported field_base: 'field_promoted'.
  $field_bases['field_promoted'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_promoted',
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

  // Exported field_base: 'field_publication_date'.
  $field_bases['field_publication_date'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_publication_date',
    'indexes' => [],
    'locked' => 0,
    'module' => 'date',
    'settings' => [
      'cache_count' => 4,
      'cache_enabled' => 0,
      'granularity' => [
        'day' => 'day',
        'hour' => 'hour',
        'minute' => 'minute',
        'month' => 'month',
        'second' => 'second',
        'year' => 'year',
      ],
      'timezone_db' => 'UTC',
      'todate' => '',
      'tz_handling' => 'site',
    ],
    'translatable' => 0,
    'type' => 'datetime',
  ];

  // Exported field_base: 'field_tags'.
  $field_bases['field_tags'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_tags',
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
          'vocabulary' => 'tags',
          'parent' => 0,
        ],
      ],
    ],
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  ];

  // Exported field_base: 'field_title_tag'.
  $field_bases['field_title_tag'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_title_tag',
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
