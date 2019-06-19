<?php
/**
 * @file
 * wim_subject.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_subject_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_exclude_node_enable_subject_page';
  $strongarm->value = 0;
  $export['apachesolr_exclude_node_enable_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__subject_page';
  $strongarm->value = [
    'view_modes' => [
      'teaser' => [
        'custom_settings' => TRUE,
      ],
      'full' => [
        'custom_settings' => FALSE,
      ],
      'rss' => [
        'custom_settings' => FALSE,
      ],
      'diff_standard' => [
        'custom_settings' => FALSE,
      ],
      'felix' => [
        'custom_settings' => FALSE,
      ],
      'short' => [
        'custom_settings' => FALSE,
      ],
      'search_index' => [
        'custom_settings' => FALSE,
      ],
      'search_result' => [
        'custom_settings' => FALSE,
      ],
      'token' => [
        'custom_settings' => FALSE,
      ],
    ],
    'extra_fields' => [
      'form' => [
        'locations' => [
          'weight' => '30',
        ],
        'title' => [
          'weight' => '-5',
        ],
        'metatags' => [
          'weight' => '40',
        ],
        'redirect' => [
          'weight' => '30',
        ],
      ],
      'display' => [],
    ],
  ];
  $export['field_bundle_settings_node__subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_subject_page';
  $strongarm->value = '0';
  $export['language_content_type_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_subject_page';
  $strongarm->value = [];
  $export['menu_options_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_subject_page';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_subject_page';
  $strongarm->value = [
    0 => 'status',
  ];
  $export['node_options_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_subject_page';
  $strongarm->value = '1';
  $export['node_preview_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_subject_page';
  $strongarm->value = 0;
  $export['node_submitted_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_subject_page';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_subject_page';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_subject_page';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_use_vertical_tabs_subject_page';
  $strongarm->value = '1';
  $export['scheduler_use_vertical_tabs_subject_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_subject_page';
  $strongarm->value = [
    'status' => '1',
    'priority' => '0.5',
  ];
  $export['xmlsitemap_settings_node_subject_page'] = $strongarm;

  return $export;
}
