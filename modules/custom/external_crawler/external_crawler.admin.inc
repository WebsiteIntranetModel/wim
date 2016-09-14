<?php

/**
 * Page callback for pages list.
 */
function external_crawler_page_list() {
  $base_acrions_url = 'admin/config/search/external_crawler/site/';
  $sites = _external_crawler_fetch_sites();
  $header = array(
    t('Name'),
    t('Check interval'),
    t('Depth'),
    t('Crawled pages'),
    t('Actions'),
  );

  $rows = array();
  foreach ($sites as $site) {
    $actions = l(t('Edit'), $base_acrions_url . $site->site_id . '/edit') . '/' . l(t('Delete'), $base_acrions_url . $site->site_id . '/delete');
    $rows[] = array(
      l($site->name, $site->url),
      format_interval($site->check_interval),
      $site->max_depth,
      _external_crawler_fetch_pages($site->site_id, NULL, TRUE),
      $actions,
    );
  }

  return array(
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('No sites defined yet.'),
    ),
  );
}

/**
 * Form for adding new site.
 */
function external_crawler_site_add_form() {

  $form = array();
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Site name'),
    '#required' => TRUE,
    '#description' => t('Site name'),
  );
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#required' => TRUE,
    '#description' => t('Site start page URL. Crawler will start index from this page.'),
  );

  $form['max_depth'] = array(
    '#type' => 'select',
    '#title' => t('Depth'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5)),
    '#default_value' => 1,
    '#description' => t('Depth of pages which crawler should index. If 1 is selected then only one page will be indexed(from URL set above).'),
  );
  $form['check_interval'] = array(
    '#type' => 'select',
    '#title' => t('Interval'),
    '#required' => TRUE,
    '#options' => array(
      2592000 => format_interval(2592000),
      604800 => format_interval(604800),
      86400 => format_interval(86400),
      7200 => format_interval(7200),
      3600 => format_interval(3600),
    ),
    '#default_value' => 86400,
    '#description' => t('Set interval of time after which pages will be reindexed for this site.'),
  );

  $form['max_run'] = array(
    '#type' => 'select',
    '#title' => t('Process limit'),
    '#required' => TRUE,
    '#options' => drupal_map_assoc(array(10, 20, 30, 50, 100)),
    '#default_value' => 1,
    '#description' => t('Amount of pages which should be fetched and processed by 1 cron job.'),
  );
  $form['url_exclude'] = array(
    '#type' => 'textarea',
    '#title' => t('Exluded paths'),
    '#description' => t('List of excluded URLs, one per line.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 * Submit handler for site adding form.
 */
function external_crawler_site_add_form_submit(&$form, &$form_state) {
  $values = $form_state['values'];
  $site = new stdClass();

  $site->name = $values['name'];
  $site->url = $values['url'];
  $site->check_interval = $values['check_interval'];
  $site->max_depth = $values['max_depth'];
  $site->max_run = $values['max_run'];
  $site->url_exclude = $values['url_exclude'];
//  $site->content_include = ''; $values['content_include'];
//  $site->content_exclude = ''; $values['content_exclude'];

  _external_crawler_site_save($site);
  $form_state['redirect'] = 'admin/config/search/external_crawler';
}

function external_crawler_site_edit_form($form, $form_state) {
  $form = array();
  $site = _external_crawler_fetch_sites($form_state['build_info']['args'][0]);

  if ($site && isset($site[0]) && is_object($site[0])) {
    $site = $site[0];
    drupal_set_title(t('Edit @site site.', array('@site' => $site->name)));

    $form['name'] = array(
      '#type' => 'textfield',
      '#title' => t('Site name'),
      '#required' => TRUE,
      '#description' => t('Site name'),
      '#default_value' => $site->name,
    );
    $form['url'] = array(
      '#type' => 'textfield',
      '#title' => t('URL'),
      '#required' => TRUE,
      '#description' => t('Site start page URL. Crawler will start index from this page.'),
      '#default_value' => $site->url,
    );

    $form['max_depth'] = array(
      '#type' => 'select',
      '#title' => t('Depth'),
      '#required' => TRUE,
      '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5)),
      '#default_value' => $site->max_depth,
      '#description' => t('Depth of pages which crawler should index. If 1 is selected then only one page will be indexed(from URL set above).'),
    );

    $form['check_interval'] = array(
      '#type' => 'select',
      '#title' => t('Interval'),
      '#required' => TRUE,
      '#options' => array(
        2592000 => format_interval(2592000),
        604800 => format_interval(604800),
        86400 => format_interval(86400),
        7200 => format_interval(7200),
        3600 => format_interval(3600),
      ),
      '#default_value' => $site->check_interval,
      '#description' => t('Set interval of time after which pages will be reindexed for this site.'),
    );

    $form['max_run'] = array(
      '#type' => 'select',
      '#title' => t('Process limit'),
      '#required' => TRUE,
      '#options' => drupal_map_assoc(array(10, 20, 30, 50, 100)),
      '#default_value' => $site->max_run,
      '#description' => t('Amount of pages which should be fetched and processed by 1 cron job.'),
    );
    $form['url_exclude'] = array(
      '#type' => 'textarea',
      '#title' => t('Exluded paths'),
      '#description' => t('List of excluded URLs, one per line.'),
      '#default_value' => $site->url_exclude,
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['cancel'] = array(
      '#markup' => l(t('Cancel'), 'admin/config/search/external_crawler', array('attributes' => array('id' => 'edit-cancel'))),
    );
  }
  else {
    $form['empty'] = array(
      '#markup' => t('Site does not exist.'),
    );
  }


  return $form;
}

function external_crawler_site_edit_form_submit(&$form, &$form_state){
  dpm($form_state);
}

function external_crawler_site_edit_form_delete(&$form, &$form_state) {
  dpm($form_state);
}
