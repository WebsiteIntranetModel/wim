<?php
/**
 * @file
 * wim_core.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function wim_core_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-meta-menu.
  $menus['menu-meta-menu'] = array(
    'menu_name' => 'menu-meta-menu',
    'title' => 'Meta menu links',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Meta menu links');

  return $menus;
}
