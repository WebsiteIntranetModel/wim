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
    'weight' => '9',
    'children' => array(
      0 => 'field_faq_more_information',
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
      5 => 'field_product_period',
      6 => 'field_product_procedure',
      7 => 'field_product_request',
      8 => 'field_product_particulars',
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
  $field_group->identifier = 'group_pdc|node|product|form';
  $field_group->group_name = 'group_pdc';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'PDC information',
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
        'classes' => 'group-pdc field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_pdc|node|product|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab1|node|product|default';
  $field_group->group_name = 'group_product_tab1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Description',
    'weight' => '17',
    'children' => array(
      0 => 'field_product_more_information',
      1 => 'field_product_related_laws',
      2 => 'field_related_faq',
      3 => 'field_related_product',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab1|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab2|node|product|default';
  $field_group->group_name = 'group_product_tab2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Conditions',
    'weight' => '18',
    'children' => array(
      0 => 'field_product_conditions',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab2|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab3|node|product|default';
  $field_group->group_name = 'group_product_tab3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Particulars',
    'weight' => '19',
    'children' => array(
      0 => 'field_product_forms',
      1 => 'field_product_request',
      2 => 'field_product_particulars',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab3|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab4|node|product|default';
  $field_group->group_name = 'group_product_tab4';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Period',
    'weight' => '20',
    'children' => array(
      0 => 'field_product_period',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab4|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab5|node|product|default';
  $field_group->group_name = 'group_product_tab5';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Objection',
    'weight' => '21',
    'children' => array(
      0 => 'field_product_objection',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab5|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab6|node|product|default';
  $field_group->group_name = 'group_product_tab6';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Costs',
    'weight' => '22',
    'children' => array(
      0 => 'field_product_costs',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab6|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab7|node|product|default';
  $field_group->group_name = 'group_product_tab7';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = array(
    'label' => 'Contact',
    'weight' => '24',
    'children' => array(
      0 => 'field_product_contact',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_product_tab7|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tabs|node|product|default';
  $field_group->group_name = 'group_product_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabs',
    'weight' => '2',
    'children' => array(
      0 => 'group_product_tab1',
      1 => 'group_product_tab2',
      2 => 'group_product_tab3',
      3 => 'group_product_tab4',
      4 => 'group_product_tab5',
      5 => 'group_product_tab6',
      6 => 'group_product_tab7',
    ),
    'format_type' => 'bootstrap_fieldgroup_nav',
    'format_settings' => array(
      'label' => 'Tabs',
      'instance_settings' => array(
        'bootstrap_nav_type' => 'tabs',
        'bootstrap_stacked' => '0',
        'bootstrap_orientation' => '0',
        'classes' => '',
        'required_fields' => 1,
      ),
      'formatter' => '',
    ),
  );
  $field_groups['group_product_tabs|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_relations|node|faq|form';
  $field_group->group_name = 'group_relations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'faq';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relations',
    'weight' => '8',
    'children' => array(
      0 => 'field_related_faq',
      1 => 'field_related_product',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-relations field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_relations|node|faq|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_relations|node|product|form';
  $field_group->group_name = 'group_relations';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Relations',
    'weight' => '6',
    'children' => array(
      0 => 'field_related_faq',
      1 => 'field_related_product',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-relations field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_relations|node|product|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Information');
  t('Conditions');
  t('Contact');
  t('Costs');
  t('Description');
  t('Objection');
  t('PDC information');
  t('Particulars');
  t('Period');
  t('Relations');
  t('Tabs');

  return $field_groups;
}
