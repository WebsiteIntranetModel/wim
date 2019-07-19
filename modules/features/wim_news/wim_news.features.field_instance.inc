<?php
/**
 * @file
 * wim_news.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_news_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'node-news-body'.
  $field_instances['node-news-body'] = [
    'bundle' => 'news',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 3,
      ],
      'search_result' => [
        'label' => 'hidden',
        'module' => 'smart_trim',
        'settings' => [
          'more_link' => 0,
          'more_text' => 'Read more',
          'summary_handler' => 'full',
          'trim_length' => 200,
          'trim_link' => 0,
          'trim_options' => [
            'text' => 0,
          ],
          'trim_preserve_tags' => '',
          'trim_suffix' => '',
          'trim_type' => 'chars',
        ],
        'type' => 'smart_trim_format',
        'weight' => 1,
      ],
      'short' => [
        'label' => 'hidden',
        'module' => 'smart_trim',
        'settings' => [
          'more_link' => 0,
          'more_text' => 'Read more',
          'summary_handler' => 'full',
          'trim_length' => 100,
          'trim_link' => 0,
          'trim_options' => [
            'text' => 0,
          ],
          'trim_preserve_tags' => '',
          'trim_suffix' => '',
          'trim_type' => 'chars',
        ],
        'type' => 'smart_trim_format',
        'weight' => 2,
      ],
      'teaser' => [
        'label' => 'hidden',
        'module' => 'smart_trim',
        'settings' => [
          'more_link' => 0,
          'more_text' => 'Read more',
          'summary_handler' => 'full',
          'trim_length' => 200,
          'trim_link' => 0,
          'trim_options' => [
            'text' => 0,
          ],
          'trim_preserve_tags' => '',
          'trim_suffix' => '',
          'trim_type' => 'chars',
        ],
        'type' => 'smart_trim_format',
        'weight' => 2,
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
      'weight' => 2,
    ],
  ];

  // Exported field_instance: 'node-news-field_attachment'.
  $field_instances['node-news-field_attachment'] = [
    'bundle' => 'news',
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'inline',
        'module' => 'file',
        'settings' => [],
        'type' => 'file_default',
        'weight' => 4,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 5,
      ],
      'short' => [
        'label' => 'inline',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 4,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_attachment',
    'label' => 'Attachment',
    'required' => 0,
    'settings' => [
      'description_field' => 0,
      'file_directory' => 'news/attachment',
      'file_extensions' => 'txt pdf doc docx ppt pptx mp3 mp4 avi',
      'max_filesize' => '',
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
          'audio' => 'audio',
          'document' => 'document',
          'image' => 0,
          'video' => 'video',
        ],
        'browser_plugins' => [
          'media_default--media_browser_1' => 'media_default--media_browser_1',
          'media_default--media_browser_my_files' => 'media_default--media_browser_my_files',
          'upload' => 'upload',
        ],
      ],
      'type' => 'media_generic',
      'weight' => 4,
    ],
  ];

  // Exported field_instance: 'node-news-field_image'.
  $field_instances['node-news-field_image'] = [
    'bundle' => 'news',
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
        'weight' => 1,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
      'short' => [
        'label' => 'hidden',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 1,
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
        'weight' => 1,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_image',
    'label' => 'Image',
    'required' => 0,
    'settings' => [
      'alt_field' => 1,
      'default_image' => 0,
      'file_directory' => 'news/images',
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
      'weight' => 3,
    ],
  ];

  // Exported field_instance: 'node-news-field_lead_paragraph'.
  $field_instances['node-news-field_lead_paragraph'] = [
    'bundle' => 'news',
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
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'short' => [
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
    'field_name' => 'field_lead_paragraph',
    'label' => 'Lead paragraph',
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
      'weight' => 16,
    ],
  ];

  // Exported field_instance: 'node-news-field_news_category'.
  $field_instances['node-news-field_news_category'] = [
    'bundle' => 'news',
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
      'short' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 4,
      ],
    ],
    'entity_type' => 'node',
    'field_name' => 'field_news_category',
    'label' => 'Category',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'options',
      'settings' => [
        'apply_chosen' => '',
      ],
      'type' => 'options_select',
      'weight' => 6,
    ],
  ];

  // Exported field_instance: 'node-news-field_promoted'.
  $field_instances['node-news-field_promoted'] = [
    'bundle' => 'news',
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
        'weight' => 9,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
      ],
      'short' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'inline',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
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
      'weight' => 7,
    ],
  ];

  // Exported field_instance: 'node-news-field_publication_date'.
  $field_instances['node-news-field_publication_date'] = [
    'bundle' => 'news',
    'deleted' => 0,
    'description' => 'You can use this field to display a custom publication date instead of the default creation date of the content item.',
    'display' => [
      'default' => [
        'label' => 'hidden',
        'module' => 'date',
        'settings' => [
          'format_type' => 'medium',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ],
        'type' => 'date_default',
        'weight' => 0,
      ],
      'search_result' => [
        'label' => 'hidden',
        'module' => 'date',
        'settings' => [
          'format_type' => 'medium',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ],
        'type' => 'date_default',
        'weight' => 0,
      ],
      'short' => [
        'label' => 'hidden',
        'module' => 'date',
        'settings' => [
          'format_type' => 'short',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ],
        'type' => 'date_default',
        'weight' => 0,
      ],
      'teaser' => [
        'label' => 'hidden',
        'module' => 'date',
        'settings' => [
          'format_type' => 'medium',
          'fromto' => 'both',
          'multiple_from' => '',
          'multiple_number' => '',
          'multiple_to' => '',
          'show_remaining_days' => 0,
        ],
        'type' => 'date_default',
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
      'weight' => 12,
    ],
  ];

  // Exported field_instance: 'node-news-field_tags'.
  $field_instances['node-news-field_tags'] = [
    'bundle' => 'news',
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
        'weight' => 2,
      ],
      'short' => [
        'label' => 'inline',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 3,
      ],
      'teaser' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 5,
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
      'weight' => 5,
    ],
  ];

  // Exported field_instance: 'node-news-field_weight'.
  $field_instances['node-news-field_weight'] = [
    'bundle' => 'news',
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
        'weight' => 5,
      ],
      'search_result' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
      'short' => [
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
  t('Attachment');
  t('Body');
  t('Category');
  t('Check if You want to stick this node on top of lists');
  t('Image');
  t('Lead paragraph');
  t('Promoted');
  t('Publication date');
  t('Tags');
  t('Weight');
  t('You can use this field to display a custom publication date instead of the default creation date of the content item.');

  return $field_instances;
}
