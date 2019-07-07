<?php
/**
 * @file
 * wim_slider.bean.inc
 */

/**
 * Implements hook_bean_admin_ui_types().
 */
function wim_slider_bean_admin_ui_types() {
  $export = [];

  $bean_type = new stdClass();
  $bean_type->disabled = FALSE; /* Edit this to true to make a default bean_type disabled initially */
  $bean_type->api_version = 5;
  $bean_type->name = 'slider';
  $bean_type->label = 'Slider';
  $bean_type->options = '';
  $bean_type->description = '';
  $export['slider'] = $bean_type;

  return $export;
}
