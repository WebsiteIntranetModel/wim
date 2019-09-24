<?php
/**
 * @file
 * wim_block_management.features.felix_block_set.inc
 */

/**
 * Implements hook_felix_default_block_sets().
 */
function wim_block_management_felix_default_block_sets() {
  $sets = [];
  $sets['default'] = [
    'name' => 'default',
    'title' => 'Default',
    'blocks' => [
      0 => [
        'module' => 'aggregator',
        'delta' => '*',
      ],
      1 => [
        'module' => 'bean',
        'delta' => '*',
      ],
      2 => [
        'module' => 'block',
        'delta' => '*',
      ],
      3 => [
        'module' => 'custom_lists',
        'delta' => '*',
      ],
      4 => [
        'module' => 'facetapi',
        'delta' => '*',
      ],
      5 => [
        'module' => 'menu',
        'delta' => '*',
      ],
      6 => [
        'module' => 'menu_block',
        'delta' => '*',
      ],
      7 => [
        'module' => 'views',
        'delta' => '*',
      ],
      8 => [
        'module' => 'wim_cvdr',
        'delta' => '*',
      ],
    ],
    'nodetypes' => [
      0 => [
        'nodetype' => 'page',
      ],
      1 => [
        'nodetype' => 'product',
      ],
      2 => [
        'nodetype' => 'webform',
      ],
    ],
    'viewmodes' => [
      0 => [
        'viewmode' => 'full',
      ],
      1 => [
        'viewmode' => 'introduction',
      ],
    ],
  ];
  return $sets;
}
