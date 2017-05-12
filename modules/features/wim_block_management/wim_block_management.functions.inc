<?php
/**
 * @file
 * Helper functions for WIM Block Management.
 */

/**
 * Gets columns options.
 *
 * @return array options
 *   Array of bootstrap columns.
 */
function _wim_block_management_get_columns_options() {
  $options = array(
    WIM_BLOCK_MANAGEMENT_BOOTSTRAP_FULL_WIDTH => t('Full-width'),
    '8' => t('2/3 of region'),
    '6' => t('1/2 of region'),
    '4' => t('1/3 of region'),
    '3' => t('1/4 of region'),
  );

  // Allow alter options.
  drupal_alter('wim_block_management_columns_options', $options);
  return $options;
}

/**
 * Add block to the Felix region.
 */
function _wim_block_management_add_felix_block($region_name, $path, $module, $delta, $detail_path = NULL, $data = array()) {
  if (!$region = _felix_region_by_name($region_name)) {
    return FALSE;
  }

  if ($module === 'node' && is_numeric($delta) && module_exists('translation')) {
    // Add the source translation.
    $tnid = db_select('node', 'n')
      ->fields('n', array('tnid'))
      ->condition('n.nid', $delta)
      ->execute()
      ->fetchField();
    $delta = $tnid ? $tnid : $delta;
    $detail_path = "node/$delta";
  }

  $hash = _felix_get_hash($region, $path);

  $block = new stdClass();
  $block->region = $region->name;
  $block->weight = _felix_new_block_weight($region->name);
  $block->hash = $hash->hash;
  $block->module = $module;
  $block->delta = $delta;
  $block->detail_path = $detail_path;
  $block->data = $data;
  $block->hash_parts = $hash->parts;
  $block->exclude = serialize(array());

  foreach (module_implements('felix_block_insert') as $module) {
    $hook = "{$module}_felix_block_insert";
    $hook($block, $path);
  }

  $block->data = serialize($block->data);
  $block->hash_parts = serialize($block->hash_parts);

  drupal_write_record('felix_block', $block);

  return TRUE;
}
