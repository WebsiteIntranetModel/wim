<?php
/**
 * @file
 * wim_agenda.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_agenda_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_exclude_node_enable_agenda';
  $strongarm->value = 1;
  $export['apachesolr_exclude_node_enable_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__agenda';
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
      'short' => [
        'custom_settings' => TRUE,
      ],
      'felix' => [
        'custom_settings' => FALSE,
      ],
      'search_index' => [
        'custom_settings' => FALSE,
      ],
      'search_result' => [
        'custom_settings' => TRUE,
      ],
      'token' => [
        'custom_settings' => FALSE,
      ],
    ],
    'extra_fields' => [
      'form' => [
        'title' => [
          'weight' => '0',
        ],
        'locations' => [
          'weight' => '5',
        ],
        'redirect' => [
          'weight' => '9',
        ],
        'metatags' => [
          'weight' => '10',
        ],
        'path' => [
          'weight' => '11',
        ],
      ],
      'display' => [],
    ],
  ];
  $export['field_bundle_settings_node__agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_agenda';
  $strongarm->value = '0';
  $export['language_content_type_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_agenda';
  $strongarm->value = [];
  $export['menu_options_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_agenda';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_agenda';
  $strongarm->value = [
    0 => 'status',
  ];
  $export['node_options_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_agenda';
  $strongarm->value = '1';
  $export['node_preview_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_agenda';
  $strongarm->value = 0;
  $export['node_submitted_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_agenda';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_agenda';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_agenda';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_use_vertical_tabs_agenda';
  $strongarm->value = '1';
  $export['scheduler_use_vertical_tabs_agenda'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_agenda';
  $strongarm->value = [
    'status' => '1',
    'priority' => '0.5',
  ];
  $export['xmlsitemap_settings_node_agenda'] = $strongarm;

  return $export;
}
