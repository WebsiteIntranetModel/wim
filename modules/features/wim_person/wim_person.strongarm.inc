<?php
/**
 * @file
 * wim_person.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_person_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__person';
  $strongarm->value = [
    'view_modes' => [
      'teaser' => [
        'custom_settings' => TRUE,
      ],
      'search_result' => [
        'custom_settings' => TRUE,
      ],
      'full' => [
        'custom_settings' => FALSE,
      ],
      'rss' => [
        'custom_settings' => FALSE,
      ],
      'search_index' => [
        'custom_settings' => FALSE,
      ],
      'diff_standard' => [
        'custom_settings' => FALSE,
      ],
      'felix' => [
        'custom_settings' => FALSE,
      ],
      'token' => [
        'custom_settings' => FALSE,
      ],
      'short' => [
        'custom_settings' => FALSE,
      ],
      'introduction' => [
        'custom_settings' => FALSE,
      ],
    ],
    'extra_fields' => [
      'form' => [
        'locations' => [
          'weight' => '9',
        ],
        'metatags' => [
          'weight' => '10',
        ],
        'title' => [
          'weight' => '0',
        ],
        'redirect' => [
          'weight' => '8',
        ],
      ],
      'display' => [],
    ],
  ];
  $export['field_bundle_settings_node__person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_person';
  $strongarm->value = '0';
  $export['language_content_type_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_person';
  $strongarm->value = [];
  $export['menu_options_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_person';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_person';
  $strongarm->value = [
    0 => 'status',
  ];
  $export['node_options_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_person';
  $strongarm->value = '1';
  $export['node_preview_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_person';
  $strongarm->value = 0;
  $export['node_submitted_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_person';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_person';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_person';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_use_vertical_tabs_person';
  $strongarm->value = '1';
  $export['scheduler_use_vertical_tabs_person'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_person';
  $strongarm->value = [
    'status' => '1',
    'priority' => '0.5',
  ];
  $export['xmlsitemap_settings_node_person'] = $strongarm;

  return $export;
}
