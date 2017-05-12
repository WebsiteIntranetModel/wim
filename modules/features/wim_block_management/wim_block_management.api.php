<?php
/**
 * @file
 * Hooks provided by WIM Block Management.
 */

/**
 * Alter bootstrap columns options for thr Felix blocks.
 *
 * @param array $options
 *    Array of options.
 *    Key is a bootstrap col class and value is a label on the form.
 */
function hook_wim_block_management_columns_options_alter(&$options) {
  $options['new_option'] = t('1/6 of region');
}
