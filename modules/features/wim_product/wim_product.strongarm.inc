<?php
/**
 * @file
 * wim_product.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_product_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'apachesolr_exclude_node_enable_product';
  $strongarm->value = 1;
  $export['apachesolr_exclude_node_enable_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__product';
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
        'custom_settings' => FALSE,
      ],
      'search_index' => [
        'custom_settings' => FALSE,
      ],
      'search_result' => [
        'custom_settings' => TRUE,
      ],
      'felix' => [
        'custom_settings' => FALSE,
      ],
      'token' => [
        'custom_settings' => FALSE,
      ],
      'introduction' => [
        'custom_settings' => TRUE,
      ],
    ],
    'extra_fields' => [
      'form' => [
        'title' => [
          'weight' => '0',
        ],
        'locations' => [
          'weight' => '6',
        ],
        'metatags' => [
          'weight' => '13',
        ],
        'redirect' => [
          'weight' => '10',
        ],
        'path' => [
          'weight' => '9',
        ],
        'xmlsitemap' => [
          'weight' => '15',
        ],
      ],
      'display' => [],
    ],
  ];
  $export['field_bundle_settings_node__product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_product';
  $strongarm->value = '0';
  $export['language_content_type_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_product';
  $strongarm->value = [];
  $export['menu_options_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_product';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_product';
  $strongarm->value = [
    0 => 'status',
  ];
  $export['node_options_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_product';
  $strongarm->value = '0';
  $export['node_preview_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_product';
  $strongarm->value = 0;
  $export['node_submitted_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_enable_product';
  $strongarm->value = 1;
  $export['scheduler_publish_enable_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_publish_touch_product';
  $strongarm->value = 1;
  $export['scheduler_publish_touch_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_unpublish_enable_product';
  $strongarm->value = 1;
  $export['scheduler_unpublish_enable_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scheduler_use_vertical_tabs_product';
  $strongarm->value = '1';
  $export['scheduler_use_vertical_tabs_product'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_product';
  $strongarm->value = [
    'status' => '1',
    'priority' => '0.6',
  ];
  $export['xmlsitemap_settings_node_product'] = $strongarm;

  return $export;
}
