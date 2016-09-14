<?php
/**
 * @file
 * wim_agenda.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function wim_agenda_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_reminder|node|agenda|form';
  $field_group->group_name = 'group_reminder';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'agenda';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Reminder',
    'weight' => '44',
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
  $field_groups['group_reminder|node|agenda|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Reminder');

  return $field_groups;
}
