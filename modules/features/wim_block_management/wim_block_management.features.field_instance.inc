<?php
/**
 * @file
 * wim_block_management.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_block_management_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'bean-editorial-field_aria_label'.
  $field_instances['bean-editorial-field_aria_label'] = [
    'bundle' => 'editorial',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 4,
      ],
      'link_title' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'bean',
    'field_name' => 'field_aria_label',
    'label' => 'Aria label',
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
      'weight' => 1,
    ],
  ];

  // Exported field_instance: 'bean-editorial-field_body'.
  $field_instances['bean-editorial-field_body'] = [
    'bundle' => 'editorial',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 2,
      ],
      'link_title' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'bean',
    'field_name' => 'field_body',
    'label' => 'Body',
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
      'weight' => 4,
    ],
  ];

  // Exported field_instance: 'bean-editorial-field_image'.
  $field_instances['bean-editorial-field_image'] = [
    'bundle' => 'editorial',
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'image',
        'settings' => [
          'image_link' => '',
          'image_style' => 'pictogram',
        ],
        'type' => 'image',
        'weight' => 1,
      ],
      'link_title' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'bean',
    'field_name' => 'field_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => [
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => 'editorial/images',
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
          'image' => 'image',
        ],
        'browser_plugins' => [],
        'preview_image_style' => 'thumbnail',
        'progress_indicator' => 'throbber',
      ],
      'type' => 'media_generic',
      'weight' => 3,
    ],
  ];

  // Exported field_instance: 'bean-editorial-field_link'.
  $field_instances['bean-editorial-field_link'] = [
    'bundle' => 'editorial',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
      ],
      'link_title' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'bean',
    'field_name' => 'field_link',
    'label' => 'Link',
    'required' => 0,
    'settings' => [
      'absolute_url' => 1,
      'attributes' => [
        'class' => '',
        'configurable_class' => 0,
        'configurable_title' => 0,
        'rel' => '',
        'target' => 'default',
        'title' => '',
      ],
      'display' => [
        'url_cutoff' => 80,
      ],
      'enable_tokens' => 1,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_label_use_field_label' => 0,
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => FALSE,
      'validate_url' => 1,
    ],
    'widget' => [
      'active' => 0,
      'module' => 'link',
      'settings' => [],
      'type' => 'link_field',
      'weight' => 5,
    ],
  ];

  // Translatables
  // Included for use with string extractors like potx.
  t('Aria label');
  t('Body');
  t('Image');
  t('Link');

  return $field_instances;
}
