<?php
/**
 * @file
 * wim_webform.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function wim_webform_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_send_attachments_with_emai'.
  $field_bases['field_send_attachments_with_emai'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_send_attachments_with_emai',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        0 => '',
        1 => '',
      ),
      'allowed_values_function' => '',
    ),
    'translatable' => 0,
    'type' => 'list_boolean',
  );

  return $field_bases;
}
