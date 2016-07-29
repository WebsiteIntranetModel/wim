<?php
/**
 * @file
 * wim_addition_faq_product_fields.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function wim_addition_faq_product_fields_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_info|node|faq|form';
  $field_group->group_name = 'group_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'faq';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional Information',
    'weight' => '13',
    'children' => array(
      0 => 'field_location',
      1 => 'field_related_faq',
      2 => 'field_related_product',
      3 => 'field_faq_more_information',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-additional-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_additional_info|node|faq|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_info|node|product|form';
  $field_group->group_name = 'group_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Additional Information',
    'weight' => '8',
    'children' => array(
      0 => 'field_attachment',
      1 => 'field_product_conditions',
      2 => 'field_product_contact',
      3 => 'field_product_costs',
      4 => 'field_product_objection',
      5 => 'field_product_particulars',
      6 => 'field_product_period',
      7 => 'field_product_request',
      8 => 'field_related_faq',
      9 => 'field_related_product',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-additional-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_additional_info|node|product|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pcd|node|product|form';
  $field_group->group_name = 'group_pcd';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PCD information',
    'weight' => '7',
    'children' => array(
      0 => 'field_product_forms',
      1 => 'field_product_more_information',
      2 => 'field_product_related_laws',
      3 => 'field_product_request_online',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-pcd field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_pcd|node|product|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Information');
  t('PCD information');

  return $field_groups;
}