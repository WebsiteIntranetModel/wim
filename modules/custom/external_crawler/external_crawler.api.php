<?php

/**
 * Implements hook_external_crawler_document_alter().
 * 
 * Alter a document before indexing.
 * 
 * @param ApacheSolrDocument $document
 */
function hook_external_crawler_document_alter(ApacheSolrDocument &$document) {
  $document->addField('foo', 'bar');
}
