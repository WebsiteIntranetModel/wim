<?php

/**
 * @file
 * API for External Crawler module.
 */

/**
 * Implements hook_external_crawler_document_alter().
 *
 * Alter a document before indexing.
 */
function hook_external_crawler_document_alter(ApacheSolrDocument &$document) {
  $document->addField('foo', 'bar');
}

/**
 * Implements hook_external_crawler_save_site_alter().
 *
 * Alter site before save.
 */
function hook_external_crawler_save_site_alter(&$site, $fields) {
  $site->new_field = isset($fields['new_field']) ? $fields['new_field'] : NULL;
}
