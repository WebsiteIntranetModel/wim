<?php
/**
 * @file
 * wim_agenda.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function wim_agenda_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'agenda';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Agenda';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Agenda';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'No results';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No results';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Promoted (field_promoted) */
  $handler->display->display_options['sorts']['field_promoted_value']['id'] = 'field_promoted_value';
  $handler->display->display_options['sorts']['field_promoted_value']['table'] = 'field_data_field_promoted';
  $handler->display->display_options['sorts']['field_promoted_value']['field'] = 'field_promoted_value';
  $handler->display->display_options['sorts']['field_promoted_value']['order'] = 'DESC';
  /* Sort criterion: Content: Date -  start date (field_agenda_date) */
  $handler->display->display_options['sorts']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['sorts']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['sorts']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  /* Filter criterion: Content: Published */
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
  $handler->display->display_options['filters']['type']['value'] = array(
    'agenda' => 'agenda',
  );
  /* Filter criterion: Content: Date - end date (field_agenda_date:value2) */
  $handler->display->display_options['filters']['field_agenda_date_value2']['id'] = 'field_agenda_date_value2';
  $handler->display->display_options['filters']['field_agenda_date_value2']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['filters']['field_agenda_date_value2']['field'] = 'field_agenda_date_value2';
  $handler->display->display_options['filters']['field_agenda_date_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_agenda_date_value2']['default_date'] = 'now';

  /* Display: Overview */
  $handler = $view->new_display('page', 'Overview', 'agenda_overview');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '5';
  $handler->display->display_options['path'] = 'agenda';

  /* Display: Upcoming Agenda */
  $handler = $view->new_display('block', 'Upcoming Agenda', 'upcoming_agenda');
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'Complete agenda';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'short';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['label'] = 'Add Agenda node';
  $handler->display->display_options['footer']['area_text_custom']['content'] = '<![CONTENT_IS_REPLACED_IN_CODE]!>';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Promoted (field_promoted) */
  $handler->display->display_options['sorts']['field_promoted_value']['id'] = 'field_promoted_value';
  $handler->display->display_options['sorts']['field_promoted_value']['table'] = 'field_data_field_promoted';
  $handler->display->display_options['sorts']['field_promoted_value']['field'] = 'field_promoted_value';
  $handler->display->display_options['sorts']['field_promoted_value']['order'] = 'DESC';
  /* Sort criterion: Content: Date -  start date (field_agenda_date) */
  $handler->display->display_options['sorts']['field_agenda_date_value']['id'] = 'field_agenda_date_value';
  $handler->display->display_options['sorts']['field_agenda_date_value']['table'] = 'field_data_field_agenda_date';
  $handler->display->display_options['sorts']['field_agenda_date_value']['field'] = 'field_agenda_date_value';
  $translatables['agenda'] = array(
    t('Master'),
    t('Agenda'),
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
    t('No results'),
    t('Overview'),
    t('Upcoming Agenda'),
    t('Complete agenda'),
    t('Add Agenda node'),
    t('<![CONTENT_IS_REPLACED_IN_CODE]!>'),
  );
  $export['agenda'] = $view;

  return $export;
}
