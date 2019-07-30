<?php
/**
 * @file
 * wim_addition_faq_product_fields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_addition_faq_product_fields_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'node-faq-field_faq_address'.
  $field_instances['node-faq-field_faq_address'] = [
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
        'weight' => 0,
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
    'field_name' => 'field_faq_address',
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
      'weight' => 13,
    ],
  ];

  // Exported field_instance: 'node-faq-field_faq_more_information'.
  $field_instances['node-faq-field_faq_more_information'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'module' => 'link',
        'settings' => [],
        'type' => 'link_default',
        'weight' => 5,
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
    'field_name' => 'field_faq_more_information',
    'label' => 'More information',
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
      'title' => 'optional',
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
      'weight' => 12,
    ],
  ];

  // Exported field_instance: 'node-faq-field_related_faq'.
  $field_instances['node-faq-field_related_faq'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => [
          'link' => 1,
        ],
        'type' => 'entityreference_label',
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
    'field_name' => 'field_related_faq',
    'label' => 'Related FAQ items',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'entityreference',
      'settings' => [
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ],
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 9,
    ],
  ];

  // Exported field_instance: 'node-faq-field_related_product'.
  $field_instances['node-faq-field_related_product'] = [
    'bundle' => 'faq',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => [
          'link' => 1,
        ],
        'type' => 'entityreference_label',
        'weight' => 4,
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
    'field_name' => 'field_related_product',
    'label' => 'Related Product items',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'entityreference',
      'settings' => [
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ],
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 10,
    ],
  ];

  // Exported field_instance: 'node-product-field_attachment'.
  $field_instances['node-product-field_attachment'] = [
    'bundle' => 'product',
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'file',
        'settings' => [],
        'type' => 'file_default',
        'weight' => 4,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_attachment',
    'label' => 'Attachment',
    'required' => 0,
    'settings' => [
      'description_field' => 0,
      'file_directory' => 'product/attachments',
      'file_extensions' => 'txt doc docx xls xlsx pdf ppt pptx pps ppsx odt ods odp mp3 mov mp4 m4a m4v mpeg avi ogg oga ogv weba webp webm',
      'max_filesize' => '',
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'file',
      'settings' => [
        'progress_indicator' => 'throbber',
      ],
      'type' => 'file_generic',
      'weight' => 51,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_address'.
  $field_instances['node-product-field_product_address'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 6,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_address',
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
      'weight' => 14,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_attention'.
  $field_instances['node-product-field_product_attention'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'This field will be used for Let op field that comes from SDU connect import. It can be placed before or after body.',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 5,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_attention',
    'label' => 'Attention',
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
        'rows' => 3,
      ],
      'type' => 'text_textarea',
      'weight' => 41,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_conditions'.
  $field_instances['node-product-field_product_conditions'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 7,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_conditions',
    'label' => 'Conditions',
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
      'weight' => 49,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_contact'.
  $field_instances['node-product-field_product_contact'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 15,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_contact',
    'label' => 'Contact',
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
      'weight' => 43,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_costs'.
  $field_instances['node-product-field_product_costs'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 5,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_costs',
    'label' => 'Costs',
    'required' => 0,
    'settings' => [
      'text_processing' => 1,
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'text',
      'settings' => [
        'rows' => 20,
      ],
      'type' => 'text_textarea',
      'weight' => 45,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_forms'.
  $field_instances['node-product-field_product_forms'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'link',
        'settings' => [],
        'type' => 'link_default',
        'weight' => 5,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_forms',
    'label' => 'Forms',
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
      'title' => 'optional',
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
      'weight' => 12,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_locations'.
  $field_instances['node-product-field_product_locations'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 6,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_locations',
    'label' => 'Locations',
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
      'weight' => 50,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_more_information'.
  $field_instances['node-product-field_product_more_information'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'link',
        'settings' => [],
        'type' => 'link_default',
        'weight' => 5,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_more_information',
    'label' => 'More information',
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
      'title' => 'optional',
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
      'weight' => 13,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_objection'.
  $field_instances['node-product-field_product_objection'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 13,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_objection',
    'label' => 'Objection',
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
      'weight' => 44,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_particulars'.
  $field_instances['node-product-field_product_particulars'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 4,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_particulars',
    'label' => 'Particulars',
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
      'weight' => 46,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_period'.
  $field_instances['node-product-field_product_period'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 12,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_period',
    'label' => 'Period',
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
      'weight' => 48,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_procedure'.
  $field_instances['node-product-field_product_procedure'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 2,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_procedure',
    'label' => 'Procedure',
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
      'weight' => 47,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_related_laws'.
  $field_instances['node-product-field_product_related_laws'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'link',
        'settings' => [],
        'type' => 'link_default',
        'weight' => 7,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_related_laws',
    'label' => 'Related laws',
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
      'title' => 'optional',
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
      'weight' => 10,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_request'.
  $field_instances['node-product-field_product_request'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'text',
        'settings' => [],
        'type' => 'text_default',
        'weight' => 7,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_request',
    'label' => 'Request',
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
      'weight' => 42,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_request_online'.
  $field_instances['node-product-field_product_request_online'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'link',
        'settings' => [],
        'type' => 'link_default',
        'weight' => 3,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_request_online',
    'label' => 'Request online',
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
      'title' => 'optional',
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
      'weight' => 11,
    ],
  ];

  // Exported field_instance: 'node-product-field_product_sdu_introduction'.
  $field_instances['node-product-field_product_sdu_introduction'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 6,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_product_sdu_introduction',
    'label' => 'SDU introduction',
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
      'weight' => 40,
    ],
  ];

  // Exported field_instance: 'node-product-field_related_faq'.
  $field_instances['node-product-field_related_faq'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'entityreference',
        'settings' => [
          'link' => 1,
        ],
        'type' => 'entityreference_label',
        'weight' => 3,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_related_faq',
    'label' => 'Related FAQ items',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'entityreference',
      'settings' => [
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ],
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 37,
    ],
  ];

  // Exported field_instance: 'node-product-field_related_product'.
  $field_instances['node-product-field_related_product'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'abovec',
        'module' => 'entityreference',
        'settings' => [
          'link' => FALSE,
        ],
        'type' => 'entityreference_label',
        'weight' => 4,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_related_product',
    'label' => 'Related Product items',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'entityreference',
      'settings' => [
        'match_operator' => 'CONTAINS',
        'path' => '',
        'size' => 60,
      ],
      'type' => 'entityreference_autocomplete_tags',
      'weight' => 38,
    ],
  ];

  // Exported field_instance: 'node-product-field_sc_audience'.
  $field_instances['node-product-field_sc_audience'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 9,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_sc_audience',
    'label' => 'Target audience co-operating catalog',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'options',
      'settings' => [],
      'type' => 'options_buttons',
      'weight' => 15,
    ],
  ];

  // Exported field_instance: 'node-product-field_sc_ask_online'.
  $field_instances['node-product-field_sc_ask_online'] = [
    'bundle' => 'product',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 16,
      ],
      'introduction' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
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
    'field_name' => 'field_sc_ask_online',
    'label' => 'Ask online',
    'required' => 0,
    'settings' => [
      'user_register_form' => FALSE,
    ],
    'widget' => [
      'active' => 1,
      'module' => 'options',
      'settings' => [],
      'type' => 'options_buttons',
      'weight' => 16,
    ],
  ];

  // Translatables
  // Included for use with string extractors like potx.
  t('Address');
  t('Attachment');
  t('Attention');
  t('Conditions');
  t('Contact');
  t('Costs');
  t('Forms');
  t('Locations');
  t('More information');
  t('Objection');
  t('Particulars');
  t('Period');
  t('Procedure');
  t('Related FAQ items');
  t('Related Product items');
  t('Related laws');
  t('Request');
  t('Request online');
  t('SDU introduction');
  t('Target audience co-operating catalog');
  t('This field will be used for Let op field that comes from SDU connect import. It can be placed before or after body.');

  return $field_instances;
}
