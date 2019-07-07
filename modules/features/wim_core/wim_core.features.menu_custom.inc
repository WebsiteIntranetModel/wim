<?php
/**
 * @file
 * wim_core.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function wim_core_menu_default_menu_custom() {
  $menus = [];

  // Exported menu: menu-meta-menu.
  $menus['menu-meta-menu'] = [
    'menu_name' => 'menu-meta-menu',
    'title' => 'Meta menu links',
    'description' => '',
  ];
  // Exported menu: menu-social-media.
  $menus['menu-social-media'] = [
    'menu_name' => 'menu-social-media',
    'title' => 'Social media',
    'description' => '',
  ];
  // Exported menu: menu-top-tasks.
  $menus['menu-top-tasks'] = [
    'menu_name' => 'menu-top-tasks',
    'title' => 'Top tasks',
    'description' => '',
  ];
  // Translatables
  // Included for use with string extractors like potx.
  t('Meta menu links');
  t('Social media');
  t('Top tasks');

  return $menus;
}
