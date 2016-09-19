<?php

/**
 * @file
 * Helper functions for External Crawler.
 */

/**
 * Helper function for retrieving the page data.
 */
function _external_crawler_get_pagedata($pagekey, $new_data = array()) {
  $pagedata = db_select('external_crawler_page', 's')
    ->fields('s')
    ->condition('pagekey', $pagekey)
    ->execute()
    ->fetchAssoc();

  if (!$pagedata) {
    $pagedata = $new_data + array(
      'pagekey' => $pagekey,
      'site_id' => NULL,
      'url' => NULL,
      'date' => NULL,
      'depth' => 1,
      'title' => NULL,
    );
  }
  return $pagedata;
}

/**
 * Helper function for loading the vendor code.
 */
function external_crawler_load_vendor() {
  static $loaded = FALSE;

  if (!$loaded) {
    include_once drupal_get_path('module', 'external_crawler') . '/vendor/autoload.php';
    $loaded = TRUE;
  }
}

/**
 * Helper function for retrieving the page key.
 */
function _external_crawler_generate_pagekey($site, $url) {
  return 'crawler/' . $site->name . '/' . md5($url);
}

/**
 * Delete page from Solr index.
 */
function external_crawler_delete_page($pagekey) {
  $env_id = variable_get('external_crawler_solr_env', 'solr');
  $solr = apachesolr_get_solr($env_id);
  $solr->deleteById(apachesolr_document_id($pagekey, 'external_crawler'));

  db_delete('external_crawler_page')
    ->condition('pagekey', $pagekey)
    ->execute();
}

/**
 * Delete site and indexed pages.
 */
function external_crawler_delete_site($site_id) {
  db_delete('external_crawler_site')
    ->condition('site_id', $site_id)
    ->execute();

  $total_limit = _external_crawler_fetch_pages($site_id, NULL, TRUE);
  $batch = array(
    'operations' => array(
      array(
        'external_crawler_batch_delete_pages',
        array(
          $site_id,
          $total_limit,
        ),
      ),
    ),
    'finished' => 'external_crawler_batch_delete_pages_finished',
    'title' => t('Removing'),
    'init_message' => t('Preparing to delete pages content from Solr...'),
    'progress_message' => t('Removing external pages from Solr...'),
    'error_message' => t('Removing external pages has encountered an error.'),
    'file' => drupal_get_path('module', 'external_crawler') . '/external_crawler.functions.inc',
  );

  batch_set($batch);
}

/**
 * Batch operation to remove pages.
 */
function external_crawler_batch_delete_pages($site_id, $total_limit, &$context) {
  if (empty($context['sandbox'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['deleted'] = 0;

    $context['sandbox']['max'] = $total_limit;
  }
  $limit = 10;

  // Reduce the limit for our final batch
  // if we would be processing more than had been requested.
  if ($limit + $context['sandbox']['progress'] > $context['sandbox']['max']) {
    $limit = $context['sandbox']['max'] - $context['sandbox']['progress'];
  }

  if ($context['sandbox']['max'] >= $context['sandbox']['progress'] + $limit) {
    $context['sandbox']['progress'] += $limit;
  }
  else {
    $context['sandbox']['progress'] = $context['sandbox']['max'];
  }

  $pages = _external_crawler_fetch_pages($site_id, $limit);
  if ($pages) {
    foreach ($pages as $page) {
      external_crawler_delete_page($page->pagekey);
    }
    $context['sandbox']['deleted'] += $limit;
  }
  else {
    $context['finished'] = TRUE;
  }

  $arguments = array(
    '@current' => $context['sandbox']['progress'],
    '@total' => $context['sandbox']['max'],
    '@deleted' => $context['sandbox']['deleted'],
  );

  $context['message'] = t('Inspected @current of @total pages. Deleted @deleted documents from Solr', $arguments);

  $context['finished'] = empty($context['sandbox']['max']) ? 1 : $context['sandbox']['progress'] / $context['sandbox']['max'];

  if ($context['finished']) {
    $context['results']['count'] = $context['sandbox']['progress'];
    $context['results']['deleted'] = $context['sandbox']['deleted'];
    $context['results']['env_id'] = $site_id;
  }
}

/**
 * Finish batch callback.
 */
function external_crawler_batch_delete_pages_finished($success, array $results, array $operations) {
  $message = '';
  if (isset($results['count'])) {
    $message .= format_plural($results['count'], '1 item processed successfully. ', '@count items successfully processed.');
  }

  drupal_set_message($message);
}

/**
 * Save page in Solr index.
 */
function external_crawler_save_page($pagedata, $document) {
  module_load_include('inc', 'external_crawler');

  $env_id = variable_get('external_crawler_solr_env', 'solr');

  $documents = array();
  $documents[] = external_crawler_build_document($pagedata['pagekey'], $document['url'], $document['title'], $document['body']);

  $solr = apachesolr_get_solr($env_id);
  $solr->addDocuments($documents);

  db_merge('external_crawler_page')
    ->key(array('pagekey' => $pagedata['pagekey']))
    ->fields($pagedata)
    ->execute();
}

/**
 * Save site data.
 */
function external_crawler_save_site($fields) {
  $site = new stdClass();
  $site->site_id = isset($fields['site_id']) ? $fields['site_id'] : NULL;

  $site->name = $fields['name'];
  $site->url = $fields['url'];
  $site->check_interval = $fields['check_interval'];
  $site->max_depth = $fields['max_depth'];
  $site->max_run = $fields['max_run'];
  $site->url_exclude = $fields['url_exclude'];
  $site->content_exclude = 'script';
  $site->content_include = '';

  drupal_write_record('external_crawler_site', $site, !empty($site->site_id) ? array('site_id') : array());
}

/**
 * Fetch all sites.
 */
function _external_crawler_fetch_sites($site_id = NULL) {

  $query = db_select('external_crawler_site', 's')
    ->fields('s');

  if ($site_id) {
    $query->condition('s.site_id', $site_id);
  }

  $sites = $query->execute()->fetchAll();

  return $sites;
}

/**
 * Fetch indexed pages.
 */
function _external_crawler_fetch_pages($site_id = NULL, $limit = NULL, $only_count = FALSE) {
  $query = db_select('external_crawler_page', 'p')
    ->fields('p');

  if ($site_id) {
    $query->condition('p.site_id', $site_id);
  }

  if ($limit) {
    $query->range(0, $limit);
  }

  if ($only_count) {
    return $query->execute()->rowCount();
  }

  $pages = $query->execute()->fetchAll();

  return $pages;
}
