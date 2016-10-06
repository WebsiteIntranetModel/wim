<?php
/**
 * @file
 * wim_block_management.bean.inc
 */

/**
 * Implements hook_bean_admin_ui_types().
 */
function wim_block_management_bean_admin_ui_types() {
  $export = array();

  $bean_type = new stdClass();
  $bean_type->disabled = FALSE; /* Edit this to true to make a default bean_type disabled initially */
  $bean_type->api_version = 5;
  $bean_type->name = 'editorial';
  $bean_type->label = 'Editorial';
  $bean_type->options = '';
  $bean_type->description = '';
  $export['editorial'] = $bean_type;

  return $export;
}
