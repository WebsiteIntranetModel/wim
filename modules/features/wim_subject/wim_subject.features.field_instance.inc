<?php
/**
 * @file
 * wim_subject.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_subject_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'node-subject_page-body'.
  $field_instances['node-subject_page-body'] = [
    'bundle' => 'subject_page',
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
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
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
    'label' => 'Body',
    'required' => FALSE,
    'settings' => [
      'display_summary' => TRUE,
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'module' => 'text',
      'settings' => [
        'rows' => 20,
        'summary_rows' => 5,
      ],
      'type' => 'text_textarea_with_summary',
      'weight' => 31,
    ],
  ];

  // Exported field_instance: 'node-subject_page-field_promoted'.
  $field_instances['node-subject_page-field_promoted'] = [
    'bundle' => 'subject_page',
    'default_value' => [
      0 => [
        'value' => 0,
      ],
    ],
    'deleted' => 0,
    'description' => 'Check if You want to stick this node on top of lists',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_promoted',
    'label' => 'Promoted',
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
      'weight' => 35,
    ],
  ];

  // Exported field_instance: 'node-subject_page-field_publication_date'.
  $field_instances['node-subject_page-field_publication_date'] = [
    'bundle' => 'subject_page',
    'deleted' => 0,
    'description' => 'You can use this field to display a custom publication date instead of the default creation date of the content item.',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 2,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_publication_date',
    'label' => 'Publication date',
    'required' => 0,
    'settings' => [
      'default_value' => 'now',
      'default_value2' => 'same',
      'default_value_code' => '',
      'default_value_code2' => '',
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'date',
      'settings' => [
        'increment' => 15,
        'input_format' => 'd/m/Y - H:i:s',
        'input_format_custom' => '',
        'label_position' => 'above',
        'no_fieldset' => 0,
        'text_parts' => [],
        'year_range' => '-3:+3',
      ],
      'type' => 'date_popup',
      'weight' => 100,
    ],
  ];

  // Exported field_instance: 'node-subject_page-field_weight'.
  $field_instances['node-subject_page-field_weight'] = [
    'bundle' => 'subject_page',
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
      'weight' => 102,
    ],
  ];

  // Translatables
  // Included for use with string extractors like potx.
  t('Body');
  t('Check if You want to stick this node on top of lists');
  t('Promoted');
  t('Publication date');
  t('Weight');
  t('You can use this field to display a custom publication date instead of the default creation date of the content item.');

  return $field_instances;
}
