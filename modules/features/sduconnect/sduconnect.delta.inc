<?php

/**
 * @file
 * Implementation of SDU Delta API.
 */

/**
 * Queue updated items for given collection.
 *
 * @param object $collection
 * @return object
 */
function sduconnect_delta_import($collection) {
  $output = FALSE;
  try {
    $from_time = $collection->updated_till;

    // If the last import was on saturday, and it is sunday now, then we should
    // compare the whole list of id's, to ensure we haven't missed anything
    // during the regular updates.
    $last_was_saturday = format_date($from_time, 'custom', 'w') == 6;
    $on_sunday = format_date(REQUEST_TIME, 'custom', 'w') == 0;
    if ($last_was_saturday && $on_sunday) {
      // @todo
    }

    $ids = sduconnect_delta_download($collection->type, $collection->external_id, $from_time);
    $queue = DrupalQueue::get('sduconnect');
    foreach (array('added', 'changed', 'removed') as $type) {
      foreach ($ids->{$type} as $id) {
        $item = new stdClass();
        $item->cid = $collection->cid;
        $item->id = $id;
        $item->type = $type;
        $queue->createItem($item);
      }
    }

    $collection->updated_till = $ids->servertime;
    sduconnect_collection_save($collection);

    $output = new stdClass();
    $output->added = count($ids->added);
    $output->changed = count($ids->changed);
    $output->removed = count($ids->removed);
  }
  catch (Exception $e) {
    db_insert('sduconnect_log')->fields(array(
      'date' => REQUEST_TIME,
      'type' => 1,
      'cid' => $collection->cid,
      'title' => t('Got code %code from %url', array(
        '%code' => $e->getCode(),
        '%url' => $e->getMessage(),
      )),
    ))->execute();
  }
  return $output;
}

/**
 * Retreive added, changed and removed items from API.
 *
 * @param string $collection_type
 * @param int $collection_id
 * @param int $from_date
 * @return stdClass
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
    'timeout' => 300
  );
  $data = drupal_http_request($url, $options);
  if ($data->code != 200) {
    throw new Exception($url, intval($data->code));
  }
  $xml = new SimpleXMLElement($data->data);
  if (!empty($xml->error)) {
    throw new Exception($url, intval($xml->error->code));
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
