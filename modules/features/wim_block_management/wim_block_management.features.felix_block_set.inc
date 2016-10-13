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
        'module' => 'bean',
        'delta' => '*',
      ),
      1 => array(
        'module' => 'block',
        'delta' => '*',
      ),
      2 => array(
        'module' => 'custom_lists',
        'delta' => '*',
      ),
      3 => array(
        'module' => 'facetapi',
        'delta' => '*',
      ),
      4 => array(
        'module' => 'menu',
        'delta' => '*',
      ),
      5 => array(
        'module' => 'menu_block',
        'delta' => '*',
      ),
      6 => array(
        'module' => 'views',
        'delta' => '*',
      ),
    ),
    'nodetypes' => array(
      0 => array(
        'nodetype' => 'page',
      ),
      1 => array(
        'nodetype' => 'product',
      ),
      2 => array(
        'nodetype' => 'webform',
      ),
    ),
    'viewmodes' => array(
      0 => array(
        'viewmode' => 'full',
      ),
      1 => array(
        'viewmode' => 'introduction',
      ),
    ),
  );
  return $sets;
}
