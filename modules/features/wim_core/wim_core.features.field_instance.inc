<?php
/**
 * @file
 * wim_core.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function wim_core_field_default_field_instances() {
  $field_instances = [];

  // Exported field_instance: 'file-document-field_title_tag'.
  $field_instances['file-document-field_title_tag'] = [
    'bundle' => 'document',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => [
      'default' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 1,
      ],
      'preview' => [
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
      'wysiwyg' => [
        'label' => 'above',
        'settings' => [],
        'type' => 'hidden',
        'weight' => 0,
      ],
    ],
    'entity_type' => 'file',
    'field_name' => 'field_title_tag',
    'label' => 'Title tag',
    'required' => 0,
    'settings' => [
      'linkit' => [
        'button_text' => 'Search',
        'enable' => 0,
        'profile' => '',
      ],
      'text_processing' => 0,
      'user_register_form' => FALSE,
      'wysiwyg_override' => 0,
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

  // Translatables
  // Included for use with string extractors like potx.
  t('Title tag');

  return $field_instances;
}
