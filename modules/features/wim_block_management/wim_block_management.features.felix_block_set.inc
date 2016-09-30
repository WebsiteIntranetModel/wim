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
        'module' => 'aggregator',
        'delta' => '*',
      ),
      1 => array(
        'module' => 'bean',
        'delta' => '*',
      ),
      2 => array(
        'module' => 'block',
        'delta' => '*',
      ),
      3 => array(
        'module' => 'custom_lists',
        'delta' => '*',
      ),
      4 => array(
        'module' => 'facetapi',
        'delta' => '*',
      ),
      5 => array(
        'module' => 'menu',
        'delta' => '*',
      ),
      6 => array(
        'module' => 'menu_block',
        'delta' => '*',
      ),
      7 => array(
        'module' => 'user',
        'delta' => 'login',
      ),
      8 => array(
        'module' => 'views',
        'delta' => '*',
      ),
    ),
    'nodetypes' => array(
      0 => array(
        'nodetype' => 'webform',
      ),
    ),
    'viewmodes' => array(
      0 => array(
        'viewmode' => 'full',
      ),
    ),
  );
  return $sets;
}
