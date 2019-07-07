<?php
/**
 * @file
 * wim_person.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_person_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'node-person-body'.
  $field_instances['node-person-body'] = [
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 5,
      ],
      'search_result' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [
          'trim_length' => 200,
        ],
        'type' => 'text_summary_or_trimmed',
        'weight' => 1,
      ],
      'teaser' => [
        'label' => 'hidden',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 4,
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
      'weight' => 6,
    ],
  ];

  // Exported field_instance: 'node-person-field_email'.
  $field_instances['node-person-field_email'] = [
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'module' => 'email',
        'settings' => [],
        'type' => 'email_default',
        'weight' => 2,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 7,
      ],
      'teaser' => [
        'label' => 'inline',
        'module' => 'email',
        'settings' => [],
        'type' => 'email_default',
        'weight' => 2,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_email',
    'label' => 'Email',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'email',
      'settings' => [
        'size' => 60,
      ],
      'type' => 'email_textfield',
      'weight' => 4,
    ],
  ];

  // Exported field_instance: 'node-person-field_image'.
  $field_instances['node-person-field_image'] = [
    'bundle' => 'person',
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'image',
        'settings' => [
          'image_link' => '',
          'image_style' => 'large',
        ],
        'type' => 'image',
        'weight' => 0,
      ],
      'search_result' => [
        'label' => 'hidden',
        'module' => 'picture',
        'settings' => [
          'colorbox_settings' => [
            'colorbox_caption' => 'auto',
            'colorbox_caption_custom' => '',
            'colorbox_gallery' => 'post',
            'colorbox_gallery_custom' => '',
            'colorbox_group' => '',
            'colorbox_multivalue_index' => NULL,
          ],
          'fallback_image_style' => '',
          'image_link' => 'content',
          'lazyload' => 0,
          'lazyload_aspect_ratio' => 0,
          'picture_mapping' => 'teaser_responsive',
        ],
        'type' => 'picture',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'hidden',
        'module' => 'picture',
        'settings' => [
          'colorbox_settings' => [
            'colorbox_caption' => 'auto',
            'colorbox_caption_custom' => '',
            'colorbox_gallery' => 'post',
            'colorbox_gallery_custom' => '',
            'colorbox_group' => '',
            'colorbox_multivalue_index' => NULL,
          ],
          'fallback_image_style' => 'teaser',
          'image_link' => 'content',
          'lazyload' => 0,
          'lazyload_aspect_ratio' => 0,
          'picture_mapping' => 'teaser_responsive',
        ],
        'type' => 'picture',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => [
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => 'images/person',
      'file_extensions' => 'png gif jpg jpeg',
      'max_filesize' => '',
      'max_resolution' => '',
      'min_resolution' => '',
      'title_field' => 0,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'media',
      'settings' => [
        'allowed_schemes' => [
          'public' => 'public',
        ],
        'allowed_types' => [
          'audio' => 0,
          'document' => 0,
          'image' => 'image',
          'video' => 0,
        ],
        'browser_plugins' => [
          'media_default--media_browser_1' => 'media_default--media_browser_1',
          'media_default--media_browser_my_files' => 'media_default--media_browser_my_files',
          'upload' => 'upload',
        ],
      ],
      'type' => 'media_generic',
      'weight' => 1,
    ],
  ];

  // Exported field_instance: 'node-person-field_person_address'.
  $field_instances['node-person-field_person_address'] = [
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 4,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_person_address',
    'label' => 'Address',
    'required' => 0,
    'settings' => [
      'linkit' => [
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ],
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
      'weight' => 5,
    ],
  ];

  // Exported field_instance: 'node-person-field_person_phone'.
  $field_instances['node-person-field_person_phone'] = [
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 3,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 5,
      ],
      'teaser' => [
        'label' => 'inline',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 3,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_person_phone',
    'label' => 'Phone',
    'required' => 0,
    'settings' => [
      'linkit' => [
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ],
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'text',
      'settings' => [
        'size' => 60,
      ],
      'type' => 'text_textfield',
      'weight' => 3,
    ],
  ];

  // Exported field_instance: 'node-person-field_person_roles'.
  $field_instances['node-person-field_person_roles'] = [
    'bundle' => 'person',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 1,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 2,
      ],
      'teaser' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 1,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_person_roles',
    'label' => 'Role',
    'required' => 0,
    'settings' => [
      'linkit' => [
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ],
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'text',
      'settings' => [
        'size' => 60,
      ],
      'type' => 'text_textfield',
      'weight' => 2,
    ],
  ];

  // Exported field_instance: 'node-person-field_tags'.
  $field_instances['node-person-field_tags'] = [
    'bundle' => 'person',
    'default_value' => NULL,
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
        'weight' => 4,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 7,
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
      'weight' => 7,
    ],
  ];

  // Exported field_instance: 'node-person-field_weight'.
  $field_instances['node-person-field_weight'] = [
    'bundle' => 'person',
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
        'weight' => 6,
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
      'weight' => 44,
    ],
  ];

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Body');
  t('Email');
  t('Image');
  t('Phone');
  t('Role');
  t('Tags');
  t('Weight');

  return $field_instances;
}
