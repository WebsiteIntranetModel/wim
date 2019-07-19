<?php
/**
 * @file
 * wim_faq.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_faq_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'node-faq-body'.
  $field_instances['node-faq-body'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 0,
      ],
      'search_result' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [
          'trim_length' => 200,
        ],
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [
          'trim_length' => 600,
        ],
        'type' => 'text_summary_or_trimmed',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'body',
    'label' => 'Answer',
    'required' => 0,
    'settings' => [
      'display_summary' => 0,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'text',
      'settings' => [
        'rows' => 20,
        'summary_rows' => 5,
      ],
      'type' => 'text_textarea_with_summary',
      'weight' => 1,
    ],
  ];

  // Exported field_instance: 'node-faq-field_faq_additional_information'.
  $field_instances['node-faq-field_faq_additional_information'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 1,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 5,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_faq_additional_information',
    'label' => 'Additional information',
    'required' => 0,
    'settings' => [
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'text',
      'settings' => [
        'rows' => 5,
      ],
      'type' => 'text_textarea',
      'weight' => 2,
    ],
  ];

  // Exported field_instance: 'node-faq-field_faq_category'.
  $field_instances['node-faq-field_faq_category'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 8,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 4,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_faq_category',
    'label' => 'Category',
    'required' => 1,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'options',
      'settings' => [],
      'type' => 'options_select',
      'weight' => 4,
    ],
  ];

  // Exported field_instance: 'node-faq-field_show_on_overview'.
  $field_instances['node-faq-field_show_on_overview'] = [
    'bundle' => 'faq',
    'default_value' => [
      0 => [
        'value' => 1,
      ],
    ],
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 9,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_show_on_overview',
    'label' => 'Show this FAQ in the FAQ overview',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'options',
      'settings' => [
        'display_label' => 1,
      ],
      'type' => 'options_onoff',
      'weight' => 5,
    ],
  ];

  // Exported field_instance: 'node-faq-field_tags'.
  $field_instances['node-faq-field_tags'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 1,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_tags',
    'label' => 'Tags',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 0,
      'module' => 'taxonomy',
      'settings' => [
        'autocomplete_path' => 'taxonomy/autocomplete',
        'size' => 60,
      ],
      'type' => 'taxonomy_autocomplete',
      'weight' => 6,
    ],
  ];

  // Exported field_instance: 'node-faq-field_weight'.
  $field_instances['node-faq-field_weight'] = [
    'bundle' => 'faq',
    'default_value' => [
      0 => [
        'value' => 0,
      ],
    ],
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 7,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 2,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_weight',
    'label' => 'Weight',
    'required' => 0,
    'settings' => [
      'range' => 20,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'weight',
      'settings' => [
        'range' => 20,
      ],
      'type' => 'weight_selector',
      'weight' => 8,
    ],
  ];

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional information');
  t('Answer');
  t('Category');
  t('Show this FAQ in the FAQ overview');
  t('Tags');
  t('Weight');

  return $field_instances;
}
