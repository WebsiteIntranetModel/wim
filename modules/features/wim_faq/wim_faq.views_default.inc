<?php

/**
 * @file
 * wim_faq.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wim_faq_views_default_views() {
  $export = [];

  $view = new view();
  $view->name = 'faq';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'FAQ';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'FAQ';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_bootstrap_accordion_plugin_style';
  $handler->display->display_options['style_options']['title_field'] = 'title';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No FAQ added yet';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = [
    'faq' => 'faq',
  ];
  /* Filter criterion: Content: Show this FAQ in the FAQ overview (field_show_on_overview) */
  $handler->display->display_options['filters']['field_show_on_overview_value']['id'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['table'] = 'field_data_field_show_on_overview';
  $handler->display->display_options['filters']['field_show_on_overview_value']['field'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['value'] = [
    1 => '1',
  ];

  /* Display: FAQ Overview */
  $handler = $view->new_display('page', 'FAQ Overview', 'faq_overview');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '[description]';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Category (field_faq_category) */
  $handler->display->display_options['relationships']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['relationships']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['relationships']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['relationships']['field_faq_category_tid']['label'] = 'field_faq_category';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['relationship'] = 'field_faq_category_tid';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value']['id'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value']['field'] = 'field_weight_value';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Category (field_faq_category) */
  $handler->display->display_options['arguments']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['arguments']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['arguments']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['arguments']['field_faq_category_tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_faq_category_tid']['exception']['value'] = 'all-categories';
  $handler->display->display_options['arguments']['field_faq_category_tid']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['field_faq_category_tid']['default_argument_options']['term_page'] = FALSE;
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_faq_category_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate_options']['vocabularies'] = [
    'faq_categories' => 'faq_categories',
  ];
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate_options']['type'] = 'convert';
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate_options']['transform'] = TRUE;
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate']['fail'] = 'empty';
  $handler->display->display_options['path'] = 'faq/%';

  /* Display: Categories Overview */
  $handler = $view->new_display('page', 'Categories Overview', 'categories_overview');
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['css_class'] = 'categories-overview';
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['pure_distinct'] = TRUE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Select a category.';
  $handler->display->display_options['header']['area']['content'] = 'Select a category.';
  $handler->display->display_options['header']['area']['format'] = 'plain_text';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Category (field_faq_category) */
  $handler->display->display_options['relationships']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['relationships']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['relationships']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'field_faq_category_tid';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path'] = 'faq/[name]';
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Taxonomy term: Name */
  $handler->display->display_options['sorts']['name']['id'] = 'name';
  $handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['name']['field'] = 'name';
  $handler->display->display_options['sorts']['name']['relationship'] = 'field_faq_category_tid';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['relationship'] = 'field_faq_category_tid';
  $handler->display->display_options['filters']['machine_name']['value'] = [
    'faq_categories' => 'faq_categories',
  ];
  $handler->display->display_options['path'] = 'faq';

  /* Display: Admin FAQ */
  $handler = $view->new_display('page', 'Admin FAQ', 'admin_faq');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Administer FAQ';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = [
    'title' => 'title',
    'field_weight_selector' => 'field_weight_selector',
    'body' => 'body',
    'field_weight' => 'field_weight',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
  ];
  $handler->display->display_options['style_options']['default'] = 'field_weight';
  $handler->display->display_options['style_options']['info'] = [
    'title' => [
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ],
    'field_weight_selector' => [
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ],
    'body' => [
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ],
    'field_weight' => [
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ],
    'edit_node' => [
      'align' => '',
      'separator' => '/',
      'empty_column' => 0,
    ],
    'view_node' => [
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ],
  ];
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  $handler->display->display_options['header']['result']['content'] = '@total item found';
  $handler->display->display_options['header']['result']['format_plural'] = TRUE;
  $handler->display->display_options['header']['result']['format_plural_plural'] = '@total items found';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Question';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Weight Selector */
  $handler->display->display_options['fields']['field_weight_selector']['id'] = 'field_weight_selector';
  $handler->display->display_options['fields']['field_weight_selector']['table'] = 'field_data_field_weight';
  $handler->display->display_options['fields']['field_weight_selector']['field'] = 'field_weight_selector';
  $handler->display->display_options['fields']['field_weight_selector']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_weight_selector']['weight_range'] = '20';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Answer';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = [
    'trim_length' => '200',
  ];
  /* Field: Content: Weight */
  $handler->display->display_options['fields']['field_weight']['id'] = 'field_weight';
  $handler->display->display_options['fields']['field_weight']['table'] = 'field_data_field_weight';
  $handler->display->display_options['fields']['field_weight']['field'] = 'field_weight';
  $handler->display->display_options['fields']['field_weight']['type'] = 'weight_integer';
  /* Field: Content: Link to edit content */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit';
  /* Field: Content: Link to content */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Weight (field_weight) */
  $handler->display->display_options['sorts']['field_weight_value']['id'] = 'field_weight_value';
  $handler->display->display_options['sorts']['field_weight_value']['table'] = 'field_data_field_weight';
  $handler->display->display_options['sorts']['field_weight_value']['field'] = 'field_weight_value';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['required'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = [
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  ];
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = [
    'faq' => 'faq',
  ];
  /* Filter criterion: Content: Category (field_faq_category) */
  $handler->display->display_options['filters']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['filters']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['filters']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['filters']['field_faq_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_faq_category_tid']['expose']['operator_id'] = 'field_faq_category_tid_op';
  $handler->display->display_options['filters']['field_faq_category_tid']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_faq_category_tid']['expose']['operator'] = 'field_faq_category_tid_op';
  $handler->display->display_options['filters']['field_faq_category_tid']['expose']['identifier'] = 'field_faq_category_tid';
  $handler->display->display_options['filters']['field_faq_category_tid']['expose']['remember_roles'] = [
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  ];
  $handler->display->display_options['filters']['field_faq_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_faq_category_tid']['vocabulary'] = 'faq_categories';
  /* Filter criterion: Content: Show this FAQ in the FAQ overview (field_show_on_overview) */
  $handler->display->display_options['filters']['field_show_on_overview_value']['id'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['table'] = 'field_data_field_show_on_overview';
  $handler->display->display_options['filters']['field_show_on_overview_value']['field'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['value'] = [
    1 => '1',
  ];
  $handler->display->display_options['filters']['field_show_on_overview_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_show_on_overview_value']['expose']['operator_id'] = 'field_show_on_overview_value_op';
  $handler->display->display_options['filters']['field_show_on_overview_value']['expose']['label'] = 'Show on overview';
  $handler->display->display_options['filters']['field_show_on_overview_value']['expose']['operator'] = 'field_show_on_overview_value_op';
  $handler->display->display_options['filters']['field_show_on_overview_value']['expose']['identifier'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['expose']['remember_roles'] = [
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
  ];
  $handler->display->display_options['filters']['field_show_on_overview_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_show_on_overview_value']['group_info']['label'] = 'Show on overview';
  $handler->display->display_options['filters']['field_show_on_overview_value']['group_info']['identifier'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['field_show_on_overview_value']['group_info']['group_items'] = [
    1 => [
      'title' => 'Yes',
      'operator' => 'or',
      'value' => [
        1 => '1',
      ],
    ],
    2 => [
      'title' => 'No',
      'operator' => 'or',
      'value' => [
        0 => '0',
      ],
    ],
  ];
  $handler->display->display_options['path'] = 'admin/content/faq';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'FAQ Content';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: FAQ Overview Block */
  $handler = $view->new_display('block', 'FAQ Overview Block', 'faq_overview_block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '[description]';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Category (field_faq_category) */
  $handler->display->display_options['relationships']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['relationships']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['relationships']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['relationships']['field_faq_category_tid']['label'] = 'field_faq_category';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Taxonomy term: Term description */
  $handler->display->display_options['fields']['description']['id'] = 'description';
  $handler->display->display_options['fields']['description']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['description']['field'] = 'description';
  $handler->display->display_options['fields']['description']['relationship'] = 'field_faq_category_tid';
  $handler->display->display_options['fields']['description']['label'] = '';
  $handler->display->display_options['fields']['description']['exclude'] = TRUE;
  $handler->display->display_options['fields']['description']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Category (field_faq_category) */
  $handler->display->display_options['arguments']['field_faq_category_tid']['id'] = 'field_faq_category_tid';
  $handler->display->display_options['arguments']['field_faq_category_tid']['table'] = 'field_data_field_faq_category';
  $handler->display->display_options['arguments']['field_faq_category_tid']['field'] = 'field_faq_category_tid';
  $handler->display->display_options['arguments']['field_faq_category_tid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_faq_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_faq_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_faq_category_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate_options']['vocabularies'] = [
    'faq_categories' => 'faq_categories',
  ];
  $handler->display->display_options['arguments']['field_faq_category_tid']['validate']['fail'] = 'empty';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = [
    'faq' => 'faq',
  ];
  /* Filter criterion: Content: Show this FAQ in the FAQ overview (field_show_on_overview) */
  $handler->display->display_options['filters']['field_show_on_overview_value']['id'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['table'] = 'field_data_field_show_on_overview';
  $handler->display->display_options['filters']['field_show_on_overview_value']['field'] = 'field_show_on_overview_value';
  $handler->display->display_options['filters']['field_show_on_overview_value']['value'] = [
    1 => '1',
  ];
  $translatables['faq'] = [
    t('Master'),
    t('FAQ'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('No results'),
    t('No FAQ added yet'),
    t('FAQ Overview'),
    t('[description]'),
    t('field_faq_category'),
    t('All'),
    t('Categories Overview'),
    t('Select a category.'),
    t('term from field_faq_category'),
    t('Admin FAQ'),
    t('Administer FAQ'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('@total item found'),
    t('@total items found'),
    t('Question'),
    t('Weight Selector'),
    t('Answer'),
    t('Weight'),
    t('Actions'),
    t('edit'),
    t('view'),
    t('Published'),
    t('Category'),
    t('Show on overview'),
    t('FAQ Overview Block'),
  ];
  $export['faq'] = $view;

  return $export;
}
