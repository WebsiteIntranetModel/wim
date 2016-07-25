<?php

/**
 * @file
 * Implementation of SDU Single item API.
 */

/**
 * Import single item.
 *
 * @param object $collection
 * @param string $id
 * @param string $type
 */
function sduconnect_single_import($collection, $id, $type, $queue_references = TRUE) {
  module_load_include('inc', 'sduconnect', 'sduconnect.content');
  $nid = 0;
  $not_found = FALSE;
  try {
    $node = sduconnect_load_node($collection, $id);
    if (empty($node->nid)) {
      $not_found = TRUE;
    }
    if ($type == 'removed') {
      if (empty($node->nid)) {
        throw new Exception(t('Item %id is listed as removed, but was not found in Drupal.', array(
          '%id' => $id
        )));
      }
      node_delete($node->nid);
    }
    else {
      $content = sduconnect_single_download($collection->type, $collection->external_id, $id);
      $references_function = "sduconnect_get_{$collection->type}_references";
      $references = $references_function($content);
      sduconnect_save_references($collection->type, $id, $references);
      // Wait 25ms for database lag.
      usleep(25000);
      $content_function = "sduconnect_set_{$collection->type}_content";
      $references = sduconnect_get_references($collection->type, $id);
      $content_function($content, $node, (bool) $collection->import_private, $references);
      sduconnect_set_domains($collection, $node);
      sduconnect_save_node($collection, $id, $node);

      // Queue references.
      if ($queue_references) {
        $references = sduconnect_get_referenced_by($collection->type, $id);
        sduconnect_queue_referenced_items($references);
      }
    }
    $nid = $node->nid;
    $log = t('Processed item %id: %title', array('%id' => $id, '%title' => $node->title));
  }
  catch (Exception $e) {
    if ($e->getCode() == 404) {
      $not_found = TRUE;
    }
    if ($e->getCode()) {
      $log = t('Got code %code when importing %type %id from %url', array(
        '%code' => $e->getCode(),
        '%type' => $type,
        '%id' => $id,
        '%url' => $e->getMessage(),
      ));
    }
    else {
      $log = $e->getMessage();
    }
  }
  $type_codes = array(
    'added' => 2,
    'changed' => 4,
    'removed' => 6,
  );
  if (!isset($type_codes[$type])) {
    $type = 'changed';
  }
  if ($collection->cid) {
    db_insert('sduconnect_log')->fields(array(
      'date' => REQUEST_TIME,
      'type' => $type_codes[$type] + ((int) $not_found),
      'cid' => $collection->cid,
      'title' => substr($log, 0, 255),
      'nid' => $nid,
    ))->execute();
  }
}

/**
 * Save references to database.
 *
 * @param string $type
 * @param string $external_id
 * @param array $references
 */
function sduconnect_save_references($type, $external_id, $references) {
  db_delete('sduconnect_related')
    ->condition('type_a', $type)
    ->condition('external_id_a', $external_id)
    ->execute();
  foreach ($references as $reference) {
    db_insert('sduconnect_related')->fields(array(
      'type_a' => $type,
      'external_id_a' => $external_id,
      'type_b' => $reference->type,
      'external_id_b' => $reference->id,
    ))->execute();
  }
}

/**
 * Get references for item.
 *
 * @param string $type
 * @param string $external_id
 */
function sduconnect_get_references($type, $external_id) {
  $sql = 'SELECT c.cid, i.external_id, c.type, i.nid, n.title
  FROM sduconnect_related r
  JOIN sduconnect_item i ON r.external_id_b = i.external_id
  JOIN sduconnect_collection c ON r.type_b = c.type AND i.cid = c.cid
  JOIN node n ON i.nid = n.nid
  WHERE r.type_a = :type AND r.external_id_a = :external_id';
  return db_query($sql, array(
    ':type' => $type,
    ':external_id' => $external_id,
  ))->fetchAll();
}

/**
 * Get items refererencing this item.
 *
 * @param string $type
 * @param string $external_id
 */
function sduconnect_get_referenced_by($type, $external_id) {
  $sql = 'SELECT c.cid, i.external_id, c.type, i.nid, n.title
  FROM sduconnect_related r
  JOIN sduconnect_item i ON r.external_id_a = i.external_id
  JOIN sduconnect_collection c ON r.type_a = c.type AND i.cid = c.cid
  JOIN node n ON i.nid = n.nid
  WHERE r.type_b = :type AND r.external_id_b = :external_id';
  return db_query($sql, array(
    ':type' => $type,
    ':external_id' => $external_id,
  ))->fetchAll();
}

/**
 * Add referenced items to queue.
 *
 * VAC's have references to products, which should be displayed on the product
 * page. Therefore, when a reference is found on a VAC, the product must be
 * updated to add the reference.
 *
 * @param array $references
 */
function sduconnect_queue_referenced_items($references) {
  $queue = DrupalQueue::get('sduconnect');
  foreach ($references as $item) {
    $job = new stdClass();
    $job->cid = $item->cid;
    $job->id = $item->external_id;
    $job->type = 'changed';
    $job->queue_references = FALSE;
    $queue->createItem($job);
  }
}

/**
 * Retreive single item from API.
 *
 * @param string $collection_type
 * @param int $collection_id
 * @param string $id
 * @return stdClass
 */
function sduconnect_single_download($collection_type, $collection_id, $id) {
  $account_id = variable_get('sduconnect_account', '');
  $url = "https://rest.sduconnect.nl/single/$collection_type/2.0/account/$account_id/collectie/$collection_id/item/$id.xml";
  $data = drupal_http_request($url);
  if ($data->code != 200) {
    throw new Exception($url, intval($data->code));
  }
  $dom = new DOMDocument();
  $dom->preserveWhiteSpace = FALSE;
  $dom->loadXML($data->data);
  $xpath = new DOMXPath($dom);
  if ($xpath->query('//response/error')->length) {
    $code = $xpath->query('//response/error/code')->item(0)->nodeValue;
    throw new Exception($url, intval($xml->error->code));
  }
  return $xpath;
}

/**
 * Load node from collection.
 *
 * @param object $collection
 * @param string $id
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
 * @param string $id
 * @param object $node
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
 * @param object $node
 */
function sduconnect_set_domains($collection, $node) {
  if (module_exists('domain')) {
    $node->domains = drupal_map_assoc($collection->domains);
  }
}
