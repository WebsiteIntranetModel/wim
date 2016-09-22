<?php

/**
 * @file
 * Administration pages.
 */

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

  $form['content_exclude'] = array(
    '#type' => 'textfield',
    '#title' => t('Content exclude'),
    '#access' => user_access('access content include/exclude'),
    '#default_value' => 'script',
    '#description' => t('CSS selector to exclude elements from index.(e.g "script, a.myclass")'),
  );

  $form['content_include'] = array(
    '#type' => 'textfield',
    '#title' => t('Content include'),
    '#access' => user_access('access content include/exclude'),
    '#description' => t('CSS selector to include elements to index.(e.g "body > p")'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  $form['#validate'][] = 'external_crawler_site_form_validate';

  return $form;
}

/**
 * Validation function for form.
 */
function external_crawler_site_form_validate(&$form, &$form_state) {
  $values = $form_state['values'];
  if (!url_is_external($values['url'])) {
    form_set_error('url', t('Incorrect format of site URL.'));
  }
}

/**
 * Submit handler for site adding form.
 */
function external_crawler_site_add_form_submit(&$form, &$form_state) {
  $values = $form_state['values'];

  external_crawler_save_site($values);
  $form_state['redirect'] = 'admin/config/search/external_crawler';
}

/**
 * Site edit form.
 */
function external_crawler_site_edit_form($form, &$form_state) {
  $form = array();
  $site = _external_crawler_fetch_sites($form_state['build_info']['args'][0]);

  if ($site && isset($site[0]) && is_object($site[0])) {
    $site = $site[0];
    drupal_set_title(t('Edit @site site.', array('@site' => $site->name)));

    $form['site_id'] = array(
      '#type' => 'value',
      '#value' => $site->site_id,
    );

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

    $form['content_exclude'] = array(
      '#type' => 'textfield',
      '#title' => t('Content exclude'),
      '#access' => user_access('access content include/exclude'),
      '#default_value' => $site->content_exclude,
      '#description' => t('CSS selector to exclude elements from index, separated by comma.(e.g "script, a.myclass")'),
    );

    $form['content_include'] = array(
      '#type' => 'textfield',
      '#title' => t('Content include'),
      '#access' => user_access('access content include/exclude'),
      '#default_value' => $site->content_include,
      '#description' => t('CSS selector to specify which element on page should be added to index.(e.g "body > p")'),
    );

    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );

    $form['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#submit' => array('external_crawler_site_edit_form_delete'),
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

  $form['#validate'][] = 'external_crawler_site_form_validate';

  return $form;
}

/**
 * Update site configurations.
 */
function external_crawler_site_edit_form_submit(&$form, &$form_state) {
  $values = $form_state['values'];

  if (isset($values['site_id'])) {
    external_crawler_save_site($values);
  }

  $form_state['redirect'] = 'admin/config/search/external_crawler';
}

/**
 * Delete submit for edit form.
 */
function external_crawler_site_edit_form_delete(&$form, &$form_state) {
  if (isset($form_state['values']['site_id'])) {
    $form_state['redirect'] = 'admin/config/search/external_crawler/site/' . $form_state['values']['site_id'] . '/delete';
  }
}

/**
 * Delete site confirmation form.
 */
function external_crawler_site_delete_confirm($form, &$form_state, $site_id) {
  $form['site_id'] = array('#type' => 'value', '#value' => $site_id);
  $message = t('Are you sure you want to delete the %site?', array('%site' => $site_id));
  $caption = '<p>' . t('This action cannot be undone.') . '</p>';

  return confirm_form($form, $message, 'admin/config/search/external_crawler', $caption, t('Delete'));
}

/**
 * Submit handler for delete action.
 */
function external_crawler_site_delete_confirm_submit($form, &$form_state) {
  $values = $form_state['values'];

  if (isset($values['site_id']) && $sites = _external_crawler_fetch_sites($values['site_id'])) {
    external_crawler_delete_site($values['site_id']);
  }

  $form_state['redirect'] = 'admin/config/search/external_crawler';
}
