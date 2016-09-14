<?php

/**
 * @file
 *  Helper functions for External Crawler.
 */

/**
 * Helper function for retrieving the page data.
 *
 * @param $pagekey
 * @return array
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
 *
 * @param $site
 * @param $url
 * @return string
 */
function _external_crawler_generate_pagekey($site, $url) {
  return 'crawler/' . $site->name . '/' . md5($url);
}

/**
 * Delete page from Solr index.
 *
 * @param string $pagekey
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
 * Save page in Solr index.
 *
 * @param string $pagekey
 * @param string $url
 * @param string $title
 * @param string $body
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
function _external_crawler_site_save(stdClass $site) {
  drupal_write_record('external_crawler_site', $site, isset($site->site_id) && !empty($site->site_id) ? array('site_id') : array());
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