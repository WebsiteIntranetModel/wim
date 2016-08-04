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
    '8' => t('2/3 of page'),
    '6' => t('1/2 of page'),
    '4' => t('1/3 of page'),
    '3' => t('1/4 of page'),
  );

  // Allow alter options.
  drupal_alter('wim_block_management_columns_options', $options);
  return $options;
}
