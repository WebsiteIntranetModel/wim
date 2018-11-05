<?php

/**
 * @file
 * Admin page callbacks for the wim_block_management module.
 */

/**
 * Block Usage page callback.
 *
 * @return string
 *   Render the block usage table.
 *
 * @throws \Exception
 */
function block_usage_page() {

  module_load_include('inc', 'wim_block_management', 'includes/block_usage.forms');
  $block_usage_filters = drupal_get_form('block_usage_filters');

  $filters = drupal_get_query_parameters();

  $rows = [];

  $header = [
    t('Title'),
    t('Info'),
    t('Delta'),
    t('Module'),
    t('Usage Paths'),
  ];

  // Add any recognized books to the table list.
  foreach (_get_all_blocks() as $block) {

    $bean_block = '';
    if ($block['module'] == 'bean') {
      $bean_block = bean_load_delta($block['delta']);
    }

    $block_title = !empty($bean_block->title) ? $bean_block->title : $block['title'];

    // Apply filters.
    if (!empty($filters['type']) && !in_array($block['module'], explode(',', $filters['type']))) {
      continue;
    }
    if (!empty($filters['title']) && strpos($block_title, $filters['title']) === FALSE) {
      continue;
    }
    if (!empty($filters['delta']) && strpos($block['delta'], $filters['delta']) === FALSE) {
      continue;
    }

    // Check if block type is in allowed list.
    if (!in_array($block['module'], variable_get('block_usage_results_type', get_modules_usage_blocks()))) {
      continue;
    }

    // Get felix usage paths.
    $links = [];
    foreach (_get_felix_blocks_by_delta($block['delta']) as $usage_link) {
      $links[] = l($usage_link, $usage_link);
    }

    $rows[] = [
      $block_title,
      $block['info'],
      $block['delta'],
      $block['module'],
      theme('item_list', ['items' => $links]),
    ];
  }

  // Set up pager variables.
  $per_page = variable_get('block_usage_results_per_page', 30);
  $current_pager = pager_default_initialize(count($rows), $per_page);
  $chunks = array_chunk($rows, $per_page, TRUE);

  // Attach filters form.
  $output = drupal_render($block_usage_filters);

  $output .= theme('table', [
    'header' => $header,
    'rows' => $chunks[$current_pager],
  ]);

  $output .= theme('pager', ['quantity', count($rows)]);

  return $output;
}

/**
 * Get a list of available block for WIM theme.
 *
 * @param string $theme
 *   Theme name.
 *
 * @return array
 *   List of available block.
 */
function _get_all_blocks($theme = 'wim') {

  module_load_include('inc', 'block', 'block.admin');
  $block = block_admin_display_prepare_blocks($theme);

  return $block;
}

/**
 * Get felix blocks by delta.
 *
 * @param string $delta
 *   Block delta.
 *
 * @return array
 *   Paths of page where that block usage.
 */
function _get_felix_blocks_by_delta($delta) {

  $results = db_select('felix_block', 'cb')
    ->fields('cb', [
      'hash_parts',
    ])
    ->condition('cb.delta', $delta)
    ->execute();

  $paths = [];
  if (!empty($results)) {
    foreach ($results as $result) {
      $el = unserialize($result->hash_parts);
      if (!empty($el['path'])) {
        $paths[] = $el['path'];
      }
    }
  }

  return $paths;
}
