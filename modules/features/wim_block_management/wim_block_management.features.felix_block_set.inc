<?php
/**
 * @file
 * wim_block_management.features.felix_block_set.inc
 */

/**
 * Implements hook_felix_default_block_sets().
 */
function wim_block_management_felix_default_block_sets() {
  $sets = array();
  $sets['default'] = array(
    'name' => 'default',
    'title' => 'Default',
    'blocks' => array(
      0 => array(
        'module' => 'block',
        'delta' => '*',
      ),
      1 => array(
        'module' => 'custom_lists',
        'delta' => '*',
      ),
      2 => array(
        'module' => 'menu',
        'delta' => '*',
      ),
      3 => array(
        'module' => 'menu_block',
        'delta' => '*',
      ),
      4 => array(
        'module' => 'user',
        'delta' => 'login',
      ),
      5 => array(
        'module' => 'views',
        'delta' => '*',
      ),
    ),
    'nodetypes' => array(),
    'viewmodes' => array(),
  );
  return $sets;
}
