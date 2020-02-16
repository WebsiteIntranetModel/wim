<?php

/**
 * @file
 * wim_linked_keywords.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_linked_keywords_strongarm() {
  $export = [];

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_linked_keywords';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_linked_keywords';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_linked_keywords';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__linked_keywords';
  $strongarm->value = [
    'view_modes' => [],
    'extra_fields' => [
      'form' => [
        'locations' => [
          'weight' => '1',
        ],
        'metatags' => [
          'weight' => '40',
        ],
        'title' => [
          'weight' => '0',
        ],
        'path' => [
          'weight' => '2',
        ],
        'redirect' => [
          'weight' => '3',
        ],
        'xmlsitemap' => [
          'weight' => '4',
        ],
      ],
      'display' => [],
    ],
  ];
  $export['field_bundle_settings_node__linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_linked_keywords';
  $strongarm->value = '0';
  $export['language_content_type_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_linked_keywords';
  $strongarm->value = [];
  $export['menu_options_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_linked_keywords';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'metatag_enable_node__linked_keywords';
  $strongarm->value = 0;
  $export['metatag_enable_node__linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_linked_keywords';
  $strongarm->value = [
    0 => 'status',
  ];
  $export['node_options_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_linked_keywords';
  $strongarm->value = '0';
  $export['node_preview_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_linked_keywords';
  $strongarm->value = 0;
  $export['node_submitted_linked_keywords'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'pathauto_node_linked_keywords_pattern';
  $strongarm->value = '';
  $export['pathauto_node_linked_keywords_pattern'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'xmlsitemap_settings_node_linked_keywords';
  $strongarm->value = [
    'status' => '0',
    'priority' => '0.5',
  ];
  $export['xmlsitemap_settings_node_linked_keywords'] = $strongarm;

  return $export;
}
