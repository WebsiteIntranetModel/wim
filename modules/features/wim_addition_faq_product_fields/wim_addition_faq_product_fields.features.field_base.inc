<?php
/**
 * @file
 * wim_addition_faq_product_fields.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_addition_faq_product_fields_field_default_field_bases() {
  $field_bases = [];

  // Exported field_base: 'field_faq_address'.
  $field_bases['field_faq_address'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_faq_address',
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

  // Exported field_base: 'field_faq_more_information'.
  $field_bases['field_faq_more_information'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_faq_more_information',
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

  // Exported field_base: 'field_product_address'.
  $field_bases['field_product_address'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_address',
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

  // Exported field_base: 'field_product_attention'.
  $field_bases['field_product_attention'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_attention',
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

  // Exported field_base: 'field_product_conditions'.
  $field_bases['field_product_conditions'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_conditions',
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

  // Exported field_base: 'field_product_contact'.
  $field_bases['field_product_contact'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_contact',
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

  // Exported field_base: 'field_product_costs'.
  $field_bases['field_product_costs'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_costs',
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

  // Exported field_base: 'field_product_forms'.
  $field_bases['field_product_forms'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_forms',
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

  // Exported field_base: 'field_product_locations'.
  $field_bases['field_product_locations'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_locations',
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

  // Exported field_base: 'field_product_more_information'.
  $field_bases['field_product_more_information'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_more_information',
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

  // Exported field_base: 'field_product_objection'.
  $field_bases['field_product_objection'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_objection',
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

  // Exported field_base: 'field_product_particulars'.
  $field_bases['field_product_particulars'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_particulars',
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

  // Exported field_base: 'field_product_period'.
  $field_bases['field_product_period'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_period',
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

  // Exported field_base: 'field_product_procedure'.
  $field_bases['field_product_procedure'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_procedure',
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

  // Exported field_base: 'field_product_related_laws'.
  $field_bases['field_product_related_laws'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_related_laws',
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

  // Exported field_base: 'field_product_request'.
  $field_bases['field_product_request'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_request',
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

  // Exported field_base: 'field_product_request_online'.
  $field_bases['field_product_request_online'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_request_online',
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

  // Exported field_base: 'field_product_sdu_introduction'.
  $field_bases['field_product_sdu_introduction'] = [
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_product_sdu_introduction',
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

  // Exported field_base: 'field_related_faq'.
  $field_bases['field_related_faq'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_related_faq',
    'indexes' => [
      'target_id' => [
        0 => 'target_id',
      ],
    ],
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => [
      'handler' => 'base',
      'handler_settings' => [
        'behaviors' => [
          'atos_behavior' => [
            'status' => 1,
          ],
          'sdu_behavior' => [
            'status' => 1,
          ],
          'views-select-list' => [
            'status' => 0,
          ],
        ],
        'sort' => [
          'type' => 'none',
        ],
        'target_bundles' => [
          'faq' => 'faq',
        ],
      ],
      'target_type' => 'node',
    ],
    'translatable' => 0,
    'type' => 'entityreference',
  ];

  // Exported field_base: 'field_related_product'.
  $field_bases['field_related_product'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_related_product',
    'indexes' => [
      'target_id' => [
        0 => 'target_id',
      ],
    ],
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => [
      'handler' => 'base',
      'handler_settings' => [
        'behaviors' => [
          'atos_behavior' => [
            'status' => 1,
          ],
          'sdu_behavior' => [
            'status' => 1,
          ],
          'views-select-list' => [
            'status' => 0,
          ],
        ],
        'sort' => [
          'type' => 'none',
        ],
        'target_bundles' => [
          'product' => 'product',
        ],
      ],
      'target_type' => 'node',
    ],
    'translatable' => 0,
    'type' => 'entityreference',
  ];

  // Exported field_base: 'field_sc_audience'.
  $field_bases['field_sc_audience'] = [
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => [],
    'field_name' => 'field_sc_audience',
    'indexes' => [
      'value' => [
        0 => 'value',
      ],
    ],
    'locked' => 0,
    'module' => 'list',
    'settings' => [
      'allowed_values' => [
        'particulier' => 'particulier',
        'ondernemer' => 'ondernemer',
      ],
      'allowed_values_function' => '',
    ],
    'translatable' => 0,
    'type' => 'list_text',
  ];

  return $field_bases;
}
