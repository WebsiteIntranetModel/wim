<?php
/**
 * @file
 * wim_linked_keywords.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wim_linked_keywords_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'administration_linked_keywords';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Administration: Linked Keywords';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Linked Keywords';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_referenced_content' => 'field_referenced_content',
    'edit_node' => 'edit_node',
    'view_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_referenced_content' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '/',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  $handler->display->display_options['header']['result']['content'] = '@total item found';
  $handler->display->display_options['header']['result']['format_plural'] = TRUE;
  $handler->display->display_options['header']['result']['format_plural_plural'] = '@total items found';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = 'No content available.';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'skip_permission_check' => 0,
      'override_label' => 1,
      'label' => 'Delete',
      'settings' => array(
        'log' => 0,
      ),
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'skip_permission_check' => 0,
      'override_label' => 1,
      'label' => 'Publish',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'skip_permission_check' => 0,
      'override_label' => 1,
      'label' => 'Unpublish',
    ),
  );
  /* Field: Content: Referenced Content */
  $handler->display->display_options['fields']['field_referenced_content_1']['id'] = 'field_referenced_content_1';
  $handler->display->display_options['fields']['field_referenced_content_1']['table'] = 'field_data_field_referenced_content';
  $handler->display->display_options['fields']['field_referenced_content_1']['field'] = 'field_referenced_content';
  $handler->display->display_options['fields']['field_referenced_content_1']['label'] = 'Linked Keyword';
  $handler->display->display_options['fields']['field_referenced_content_1']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_referenced_content_1']['type'] = 'link_title_plain';
  /* Field: Content: Referenced Content */
  $handler->display->display_options['fields']['field_referenced_content']['id'] = 'field_referenced_content';
  $handler->display->display_options['fields']['field_referenced_content']['table'] = 'field_data_field_referenced_content';
  $handler->display->display_options['fields']['field_referenced_content']['field'] = 'field_referenced_content';
  $handler->display->display_options['fields']['field_referenced_content']['label'] = 'Linked Content';
  $handler->display->display_options['fields']['field_referenced_content']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_referenced_content']['type'] = 'link_url';
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Actions';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'view';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 'All';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Published';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'linked_keywords' => 'linked_keywords',
  );
  /* Filter criterion: Content: Referenced Content (field_referenced_content:title) */
  $handler->display->display_options['filters']['field_referenced_content_title']['id'] = 'field_referenced_content_title';
  $handler->display->display_options['filters']['field_referenced_content_title']['table'] = 'field_data_field_referenced_content';
  $handler->display->display_options['filters']['field_referenced_content_title']['field'] = 'field_referenced_content_title';
  $handler->display->display_options['filters']['field_referenced_content_title']['operator'] = 'word';
  $handler->display->display_options['filters']['field_referenced_content_title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_referenced_content_title']['expose']['operator_id'] = 'field_referenced_content_title_op';
  $handler->display->display_options['filters']['field_referenced_content_title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['field_referenced_content_title']['expose']['operator'] = 'field_referenced_content_title_op';
  $handler->display->display_options['filters']['field_referenced_content_title']['expose']['identifier'] = 'field_referenced_content_title';
  $handler->display->display_options['filters']['field_referenced_content_title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
  );

  /* Display: System */
  $handler = $view->new_display('page', 'System', 'page');
  $handler->display->display_options['path'] = 'admin/content/linked-keywords';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Linked Keywords';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['administration_linked_keywords'] = array(
    t('Master'),
    t('Linked Keywords'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('@total item found'),
    t('@total items found'),
    t('No content available.'),
    t('- Choose an operation -'),
    t('Delete'),
    t('Publish'),
    t('Unpublish'),
    t('Linked Keyword'),
    t('Linked Content'),
    t('Published'),
    t('Actions'),
    t('view'),
    t('Title'),
    t('System'),
  );
  $export['administration_linked_keywords'] = $view;

  return $export;
}
