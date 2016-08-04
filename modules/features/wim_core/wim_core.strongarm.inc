<?php
/**
 * @file
 * wim_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function wim_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_icons_default_icon';
  $strongarm->value = 'sites/all/modules/contrib/menu_icons/images/default_icon.png';
  $export['menu_icons_default_icon'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_icons_hide_titles';
  $strongarm->value = 0;
  $export['menu_icons_hide_titles'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_icons_image_style_default';
  $strongarm->value = 'icon';
  $export['menu_icons_image_style_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_icons_position';
  $strongarm->value = 'left';
  $export['menu_icons_position'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_icons_use_css';
  $strongarm->value = 0;
  $export['menu_icons_use_css'] = $strongarm;

  return $export;
}
