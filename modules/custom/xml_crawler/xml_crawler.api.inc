<?php
/**
 * @file
 * Exposed Hooks in 7.x.
 */

/**
 * Lets modules alter pages before index.
 *
 * @param array $pages
 *    Pages which will go to index.
 * @param DOMDocument $dom
 *    XML document which we parsed.
 * @param object $site
 *    Site object.
 */
function hook_xml_crawler_pages_alter(&$pages, DOMDocument $dom, $site) {
  $new_pages = array();
  // Process new dom type.
  if ($site->xml_type === 'custom_xml') {
    $pages[] = $new_pages;
  }
}

/**
 * Allow modules to add new XML types.
 *
 * @return array types
 *    New types array.
 */
function hook_xml_crawler_xml_types() {
  return array('new' => t('New type'));
}
