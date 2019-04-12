<?php

/**
 * @file
 * Implementation of SDU Single item API.
 */

/**
 * Import single item.
 *
 * @param object $collection
 *   Collection object.
 * @param string $id
 *   Item external id.
 * @param string $type
 *   Type [added, changed, removed].
 */
function sduconnect_single_import($collection, $id, $type) {
  module_load_include('inc', 'sduconnect', 'sduconnect.content');
  $nid = 0;
  $not_found = '';
  try {
    $node = sduconnect_load_node($collection, $id);
    if (empty($node->nid)) {
      $not_found = '_not_found';
    }
    if ($type === 'removed') {
      if (empty($node->nid)) {
        throw new Exception(t('Item %id is listed as removed, but was not found in Drupal.', array(
          '%id' => $id,
        )));
      }
      node_delete($node->nid);
    }
    else {
      $content = sduconnect_single_download($collection->type, $collection->external_id, $id);

      $content_function = "sduconnect_set_{$collection->type}_content";
      $content_function($content, $node, (bool) $collection->import_private);
      if (module_exists('domains')) {
        sduconnect_set_domains($collection, $node);
      }
      sduconnect_save_node($collection, $id, $node);
    }

    $nid = $node->nid;
    $log = t('Processed item !id: %title', array(
      '!id' => $id,
      '%title' => $node->title,
    ));
  }
  catch (Exception $e) {
    if ($e->getCode() == 404) {
      $not_found = '_not_found';
    }
    if ($e->getCode()) {
      $log = t('Got code !code when importing !type !id from !url', array(
        '!code' => $e->getCode(),
        '!type' => $type,
        '!id' => $id,
        '!url' => $e->getMessage(),
      ));
    }
    else {
      $log = $e->getMessage();
    }
  }

  _sdu_log($type . $not_found, $collection, $log, $nid);
}

/**
 * Retreive single item from API.
 *
 * @param string $collection_type
 *   Collection type.
 * @param int $collection_id
 *   Collection ID.
 * @param string $id
 *   External item ID.
 *
 * @return object
 *   xPath object.
 *
 * @throws \Exception
 */
function sduconnect_single_download($collection_type, $collection_id, $id) {
  $account_id = variable_get('sduconnect_account', '');
  $sduconnect_version = sduconnect_get_version($collection_type);
  $url = sprintf("https://rest.sduconnect.nl/single/%s/%s/account/%d/collectie/%d/item/%s.xml",
    $collection_type, $sduconnect_version, $account_id, $collection_id, $id);

  $data = drupal_http_request($url);
  if ($data->code != 200) {
    throw new Exception($url, (int) $data->code);
  }
  $dom = new DOMDocument();
  $dom->preserveWhiteSpace = FALSE;
  $dom->loadXML($data->data);
  $xpath = new DOMXPath($dom);
  if ($xpath->query('//response/error')->length) {
    $code = $xpath->query('//response/error/code')->item(0)->nodeValue;
    throw new Exception($url, (int) $code);
  }

  return $xpath;
}

/**
 * Load node from collection.
 *
 * @param object $collection
 *   Collection object.
 * @param string $id
 *   External id.
 *
 * @return object
 *   A loaded node object or new one.
 */
function sduconnect_load_node($collection, $id) {
  $nid = db_select('sduconnect_item', 'i')
    ->fields('i', array('nid'))
    ->condition('cid', $collection->cid)
    ->condition('external_id', $id)
    ->execute()
    ->fetchField();
  if ($nid) {
    $node = node_load($nid);
  }
  else {
    $node = new stdClass();
    $node->uid = 1;
    $node->status = 1;
    $node->language = language_default()->language;
  }
  return $node;
}

/**
 * Save node.
 *
 * @param object $collection
 *   Collection object.
 * @param string $id
 *   External item ID.
 * @param object $node
 *   Node.
 */
function sduconnect_save_node($collection, $id, $node) {
  $new = empty($node->nid);
  node_submit($node);
  node_save($node);
  if ($new) {
    db_insert('sduconnect_item')->fields(array(
      'nid' => $node->nid,
      'cid' => $collection->cid,
      'external_id' => $id,
      'internal_id' => $collection->type . '-' . $id,
    ))->execute();
    db_update('sduconnect_collection')
      ->expression('items', 'items + 1')
      ->condition('cid', $collection->cid)
      ->execute();
  }
}

/**
 * Set publication domains.
 *
 * @param object $collection
 *   Collection object.
 * @param object $node
 *   Node object.
 */
function sduconnect_set_domains($collection, $node) {
  if (module_exists('domain')) {
    $node->domains = drupal_map_assoc($collection->domains);
  }
}
