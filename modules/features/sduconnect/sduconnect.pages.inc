<?php

/**
 * @file
 * Page callbacks.
 */

/**
 * Page callback for admin overview page.
 */
function sduconnect_admin_page() {
  $page = array();

  $query = db_select('queue', 'q')
    ->condition('q.name', 'sduconnect');
  $query->addExpression('COUNT(*)');
  $queue_items = $query->execute()->fetchField();
  $page['info'] = array(
    '#markup' => '<p>' . t('There are currently <strong>@count item(s)</strong> in the queue.', array('@count' => $queue_items)) . '</p>',
  );

  $collections = db_select('sduconnect_collection', 'sc')
    ->fields('sc')
    ->orderBy('sc.name')
    ->execute()
    ->fetchAll();
  $rows = array();
  foreach ($collections as $collection) {
    $rows[] = array(
      $collection->type,
      $collection->name,
      $collection->updated_till ? format_date($collection->updated_till, 'short') : '<em>' . t('never ran') . '</em>',
      $collection->items,
      format_interval($collection->frequency, 1),
      array(
        'data' => array(
          '#theme' => 'links__ctools_dropbutton',
          '#links' => array(
            array(
              'title' => t('Edit'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/edit",
            ),
            array(
              'title' => t('Start import'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/import",
            ),
            array(
              'title' => t('Delete'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/delete",
            ),
          ),
        ),
      ),
    );
  }

  $page['collections'] = array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(
      array('data' => t('Type'), 'width' => 53),
      array('data' => t('Title')),
      array('data' => t('Updated till'), 'width' => 140),
      array('data' => t('Items'), 'width' => 53),
      array('data' => t('Frequency'), 'width' => 87),
      array('width' => 140, 'data' => t('Actions'))
    ),
    '#empty' => t('There are no collections created yet.'),
  );


  return $page;
}

/**
 * Page callback for the log tab.
 */
function sduconnect_log_page() {
  $page = array();

  $interval = variable_get('sduconnect_delete_logs_after', 86400 * 30);
  $page['info'] = array(
    '#markup' => '<p>' . t('Log entries will be deleted after @interval.', array(
      '@interval' => format_interval($interval)
    )) . '</p>',
  );

  $types = array(
    1 => t('API unreachable'),
    2 => t('New'),
    3 => t('New (not found)'),
    4 => t('Updated'),
    5 => t('Updated (not found)'),
    6 => t('Deleted'),
    7 => t('Deleted (not found)'),
  );

  $logs = db_select('sduconnect_log', 'l')
    ->fields('l')
    ->orderBy('l.date', 'desc')
    ->extend('PagerDefault')
    ->limit(20)
    ->execute()
    ->fetchAll();
  $rows = array();
  foreach ($logs as $log) {
    $actions = array();
    if ($log->nid) {
      // Add links, but not for deleted types (6 and 7).
      if ($log->type < 6) {
        $actions[] = array(
          'title' => t('View node'),
          'href' => 'node/' . $log->nid,
        );
        $actions[] = array(
          'title' => t('View XML'),
          'href' => 'node/' . $log->nid . '/sduconnect-xml',
        );
      }
    }
    $row = array(
      format_date($log->date, 'short'),
      $types[$log->type],
      $log->title,
      array(
        'data' => array(
          '#theme' => 'links__ctools_dropbutton',
          '#links' => $actions,
        ),
      ),
    );
    $rows[] = $row;
  }

  $page['logs'] = array(
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => array(
      array('data' => t('Date'), 'width' => 140),
      array('data' => t('Type'), 'width' => 140),
      array('data' => t('Message')),
      array('width' => 140, 'data' => t('Actions'))
    ),
    '#empty' => t('No log messages found.'),
  );
  $page['pager'] = array(
    '#theme' => 'pager',
  );

  return $page;
}

/**
 * Page callback for node/%/sduconnect-xml.
 */
function sduconnect_page_xml($node) {
  $item = db_select('sduconnect_item', 'i')
    ->fields('i', array('cid', 'external_id'))
    ->condition('i.nid', $node->nid)
    ->execute()
    ->fetchObject();
  if (!$item) {
    return MENU_NOT_FOUND;
  }
  $collection = sduconnect_collection_load($item->cid);
  $account_id = variable_get('sduconnect_account', '');
  $version = $collection->type == 'pdc' ? '1.2' : '1.1';
  $url = "https://rest.sduconnect.nl/single/{$collection->type}/$version/account/$account_id/collectie/{$collection->external_id}/item/{$item->external_id}.xml";
  $data = drupal_http_request($url);
  if ($data->code != 200) {
    return MENU_NOT_FOUND;
  }
  drupal_add_http_header('Content-Type', 'text/xml');
  print $data->data;
}
