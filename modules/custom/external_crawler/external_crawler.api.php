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
