<?php
/**
 * @file
 * wim_addition_faq_product_fields.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function wim_addition_faq_product_fields_field_group_info() {
  $field_groups = [];

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_additional_info|node|faq|form';
  $field_group->group_name = 'group_additional_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'faq';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = [
    'label' => 'Additional Information',
    'weight' => '9',
    'children' => [
      0 => 'field_faq_more_information',
      1 => 'field_faq_address',
    ],
    'format_type' => 'tab',
    'format_settings' => [
      'formatter' => 'closed',
      'instance_settings' => [
        'description' => '',
        'classes' => 'group-additional-info field-group-tab',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Additional Information',
    'weight' => '9',
    'children' => [
      0 => 'field_attachment',
      1 => 'field_product_attention',
      2 => 'field_product_conditions',
      3 => 'field_product_contact',
      4 => 'field_product_costs',
      5 => 'field_product_locations',
      6 => 'field_product_objection',
      7 => 'field_product_particulars',
      8 => 'field_product_period',
      9 => 'field_product_procedure',
      10 => 'field_product_request',
      11 => 'field_product_sdu_introduction',
    ],
    'format_type' => 'tab',
    'format_settings' => [
      'formatter' => 'closed',
      'instance_settings' => [
        'description' => '',
        'classes' => 'group-additional-info field-group-tab',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'PDC information',
    'weight' => '7',
    'children' => [
      0 => 'field_product_forms',
      1 => 'field_product_more_information',
      2 => 'field_product_related_laws',
      3 => 'field_product_request_online',
      4 => 'field_sc_audience',
      5 => 'field_product_address',
      6 => 'field_sc_ask_online',
    ],
    'format_type' => 'tab',
    'format_settings' => [
      'formatter' => 'closed',
      'instance_settings' => [
        'description' => '',
        'classes' => 'group-pdc field-group-tab',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Description',
    'weight' => '17',
    'children' => [
      0 => 'field_product_address',
      1 => 'field_product_more_information',
      2 => 'field_product_related_laws',
      3 => 'field_related_faq',
      4 => 'field_related_product',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Conditions',
    'weight' => '19',
    'children' => [
      0 => 'field_product_conditions',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Particulars',
    'weight' => '20',
    'children' => [
      0 => 'field_product_forms',
      1 => 'field_product_particulars',
      2 => 'field_product_request',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Period',
    'weight' => '21',
    'children' => [
      0 => 'field_product_period',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Objection',
    'weight' => '22',
    'children' => [
      0 => 'field_product_objection',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Costs',
    'weight' => '23',
    'children' => [
      0 => 'field_product_costs',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Contact',
    'weight' => '24',
    'children' => [
      0 => 'field_product_contact',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
  $field_groups['group_product_tab7|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tab8|node|product|default';
  $field_group->group_name = 'group_product_tab8';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_product_tabs';
  $field_group->data = [
    'label' => 'Locations',
    'weight' => '18',
    'children' => [
      0 => 'field_product_locations',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav_item',
    'format_settings' => [
      'formatter' => '',
      'instance_settings' => [
        'classes' => '',
        'required_fields' => 1,
      ],
    ],
  ];
  $field_groups['group_product_tab8|node|product|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_product_tabs|node|product|default';
  $field_group->group_name = 'group_product_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'product';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = [
    'label' => 'Tabs',
    'weight' => '1',
    'children' => [
      0 => 'group_product_tab1',
      1 => 'group_product_tab2',
      2 => 'group_product_tab3',
      3 => 'group_product_tab4',
      4 => 'group_product_tab5',
      5 => 'group_product_tab6',
      6 => 'group_product_tab7',
      7 => 'group_product_tab8',
    ],
    'format_type' => 'bootstrap_fieldgroup_nav',
    'format_settings' => [
      'label' => 'Tabs',
      'instance_settings' => [
        'bootstrap_nav_type' => 'tabs',
        'bootstrap_stacked' => '0',
        'bootstrap_orientation' => '0',
        'classes' => '',
        'required_fields' => 1,
      ],
      'formatter' => '',
    ],
  ];
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
  $field_group->data = [
    'label' => 'Relations',
    'weight' => '8',
    'children' => [
      0 => 'field_related_faq',
      1 => 'field_related_product',
    ],
    'format_type' => 'tab',
    'format_settings' => [
      'formatter' => 'closed',
      'instance_settings' => [
        'description' => '',
        'classes' => 'group-relations field-group-tab',
        'required_fields' => 1,
      ],
    ],
  ];
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
  $field_group->data = [
    'label' => 'Relations',
    'weight' => '5',
    'children' => [
      0 => 'field_related_faq',
      1 => 'field_related_product',
    ],
    'format_type' => 'tab',
    'format_settings' => [
      'formatter' => 'closed',
      'instance_settings' => [
        'description' => '',
        'classes' => 'group-relations field-group-tab',
        'required_fields' => 1,
      ],
    ],
  ];
  $field_groups['group_relations|node|product|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Additional Information');
  t('Conditions');
  t('Contact');
  t('Costs');
  t('Description');
  t('Locations');
  t('Objection');
  t('PDC information');
  t('Particulars');
  t('Period');
  t('Relations');
  t('Tabs');

  return $field_groups;
}
