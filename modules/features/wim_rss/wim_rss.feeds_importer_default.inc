<?php
/**
 * @file
 * wim_rss.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function wim_rss_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'rss_nos';
  $feeds_importer->config = array(
    'name' => 'RSS',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsHTTPFetcher',
      'config' => array(
        'auto_detect_feeds' => FALSE,
        'use_pubsubhubbub' => FALSE,
        'designated_hub' => '',
        'request_timeout' => NULL,
        'auto_scheme' => 'http',
        'accept_invalid_cert' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsSyndicationParser',
      'config' => array(),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsNodeProcessor',
      'config' => array(
        'expire' => '-1',
        'author' => '1',
        'authorize' => 1,
        'mappings' => array(
          0 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
            'language' => 'und',
          ),
          1 => array(
            'source' => 'description',
            'target' => 'body',
            'unique' => FALSE,
            'language' => 'und',
          ),
          2 => array(
            'source' => 'guid',
            'target' => 'guid',
            'unique' => 1,
            'language' => 'und',
          ),
          3 => array(
            'source' => 'timestamp',
            'target' => 'created',
            'unique' => FALSE,
            'language' => 'und',
          ),
          4 => array(
            'source' => 'url',
            'target' => 'field_link:url',
            'unique' => FALSE,
            'language' => 'und',
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'full_html',
        'skip_hash_check' => 0,
        'bundle' => 'rss',
        'insert_new' => 1,
        'update_non_existent' => 'skip',
        'language' => 'und',
      ),
    ),
    'content_type' => 'rss_source',
    'update' => 0,
    'import_period' => '3600',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['rss_nos'] = $feeds_importer;

  return $export;
}
