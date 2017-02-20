<?php

/**
 * @file
 * Implementation of SDU Delta API.
 */

/**
 * Queue updated items for given collection.
 *
 * @param object $collection
 *   Collection object.
 *
 * @return object|FALSE
 *   Object containing added, changed, removed.
 */
function sduconnect_delta_import($collection) {
  $output = FALSE;
  try {
    $from_time = $collection->updated_till;

    $ids = sduconnect_delta_download($collection->type, $collection->external_id, $from_time);

    $queue = DrupalQueue::get('sduconnect');
    foreach (array('added', 'changed') as $type) {
      foreach ($ids->{$type} as $id) {
        $item = new stdClass();
        $item->cid = $collection->cid;
        $item->id = $id;
        $item->type = $type;
        $queue->createItem($item);
      }
    }

    // Removed items.
    if ($ids->removed) {
      $to_remove = sduconnect_load_nids($ids->removed);
      $not_found = '';
      foreach ($to_remove as $nid) {
        if ($title = sduconnect_load_title_by_nid($nid)) {
          $log = t('Processed item !id: %title', array(
            '!id' => $nid,
            '%title' => $title,
          ));
        }
        else {
          $log = t('Item %id is listed as removed, but was not found in Drupal.', array(
            '%id' => $nid,
          ));
          $not_found = '_not_found';
        }
        _sdu_log('removed' . $not_found, $collection, $log, $nid);
      }
      node_delete_multiple($to_remove);
    }

    $collection->updated_till = $ids->servertime;
    sduconnect_collection_save($collection);

    $output = new stdClass();
    $output->added = count($ids->added);
    $output->changed = count($ids->changed);
    $output->removed = count($ids->removed);
  }
  catch (Exception $e) {
    $log = t('Got code %code from %url', array(
      '%code' => $e->getCode(),
      '%url' => $e->getMessage(),
    ));
    _sdu_log('unreachable', $collection, $log, NULL);
  }
  return $output;
}

/**
 * Retreive added, changed and removed items from API.
 *
 * @param string $collection_type
 *   Collection type.
 * @param int $collection_id
 *   Collection ID.
 * @param int $from_date
 *   Timestamp.
 *
 * @return object
 *   Object containing items by type.
 *
 * @throws \Exception
 */
function sduconnect_delta_download($collection_type, $collection_id, $from_date) {
  $account_id = variable_get('sduconnect_account', '');
  $version = '1.1';
  if ($from_date < REQUEST_TIME - (86400 * 30)) {
    $url = "https://rest.sduconnect.nl/delta/$collection_type/$version/account/$account_id/collectie/$collection_id.xml";
  }
  else {
    $date = date('Ymd\\THis', $from_date);
    $url = "https://rest.sduconnect.nl/delta/$collection_type/$version/account/$account_id/collectie/$collection_id/startdatetime/$date.xml";
  }
  // The callback to get changed items can be slow. Use a timeout of 5 minutes.
  $options = array(
    'timeout' => 300,
  );
  $data = drupal_http_request($url, $options);
  if ($data->code != 200) {
    throw new Exception($url, (int) ($data->code));
  }
  $xml = new SimpleXMLElement($data->data);
  if (!empty($xml->error)) {
    throw new Exception($url, (int) ($xml->error->code));
  }
  $output = new stdClass();
  $output->servertime = strtotime($xml->servertime);
  foreach (array('added', 'changed', 'removed') as $type) {
    $output->{$type} = array();
    foreach ($xml->{$type . 'ids'}->itemid as $id) {
      $output->{$type}[] = (string) $id;
    }
  }
  return $output;
}

/**
 * Helper function to load node id's by external id.
 *
 * @param array $ids
 *    List of external id's.
 *
 * @return array
 *    List of node id's.
 */
function sduconnect_load_nids(array $ids) {
  $nids = db_select('sduconnect_item', 'i')
    ->fields('i', array('nid'))
    ->condition('i.external_id', $ids, 'IN')
    ->execute()
    ->fetchCol();

  return $nids;
}

/**
 * Helper function to load title by nid.
 *
 * @param string $nid
 *    Node id.
 *
 * @return string|FALSE
 *    Title.
 */
function sduconnect_load_title_by_nid($nid) {
  return db_select('node', 'n')
    ->fields('n', array('title'))
    ->condition('n.nid', $nid)
    ->execute()
    ->fetchField();
}
