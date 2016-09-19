<?php
/**
 * @file
 * wim_product.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function wim_product_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_reminder|node|product|form';
  $field_group->group_name = 'group_reminder';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reminder',
    'weight' => '43',
    'children' => array(
      0 => 'field_reminder_email',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Reminder',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => 'Reminder options',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_reminder|node|product|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Reminder');

  return $field_groups;
}
