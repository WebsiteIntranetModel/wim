<?php

/**
 * @file
 * Page callbacks.
 */

/**
 * Page callback for admin overview page.
 */
function sduconnect_admin_page() {
  $page = [];

  $query = db_select('queue', 'q')->condition('q.name', 'sduconnect');
  $query->addExpression('COUNT(*)');
  $queue_items = $query->execute()->fetchField();
  $page['info'] = [
    '#markup' => '<p>' . t('There are currently <strong>@count item(s)</strong> in the queue.', ['@count' => $queue_items]) . '</p>',
  ];

  $collections = db_select('sduconnect_collection', 'sc')
    ->fields('sc')
    ->orderBy('sc.name')
    ->execute()
    ->fetchAll();
  $rows = [];
  foreach ($collections as $collection) {
    $rows[] = [
      $collection->type,
      $collection->name,
      $collection->updated_till ? format_date($collection->updated_till, 'short') : '<em>' . t('never ran') . '</em>',
      $collection->items,
      format_interval($collection->frequency, 1),
      [
        'data' => [
          '#theme' => 'links__ctools_dropbutton',
          '#links' => [
            [
              'title' => t('Edit'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/edit",
            ],
            [
              'title' => t('Start import'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/import",
            ],
            [
              'title' => t('Delete'),
              'href' => "admin/config/content/sduconnect/collections/{$collection->cid}/delete",
            ],
          ],
        ],
      ],
    ];
  }

  $page['collections'] = [
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => [
      ['data' => t('Type'), 'width' => 53],
      ['data' => t('Title')],
      ['data' => t('Updated till'), 'width' => 140],
      ['data' => t('Items'), 'width' => 53],
      ['data' => t('Frequency'), 'width' => 87],
      ['width' => 140, 'data' => t('Actions')],
    ],
    '#empty' => t('There are no collections created yet.'),
  ];

  return $page;
}

/**
 * Page callback for the log tab.
 */
function sduconnect_log_page() {
  $page = [];

  $interval = variable_get('sduconnect_delete_logs_after', 86400 * 30);
  $page['info'] = [
    '#markup' => '<p>' . t('Log entries will be deleted after @interval.', [
      '@interval' => format_interval($interval),
      ]) . '</p>',
  ];

  $types = [
    1 => t('API unreachable'),
    2 => t('New'),
    3 => t('New (not found)'),
    4 => t('Updated'),
    5 => t('Updated (not found)'),
    6 => t('Deleted'),
    7 => t('Deleted (not found)'),
  ];

  $logs = db_select('sduconnect_log', 'l')
    ->fields('l')
    ->orderBy('l.date', 'desc')
    ->extend('PagerDefault')
    ->limit(20)
    ->execute()
    ->fetchAll();
  $rows = [];
  foreach ($logs as $log) {
    $actions = [];
    if ($log->nid) {
      // Add links, but not for deleted types (6 and 7).
      if ($log->type < 6) {
        $actions[] = [
          'title' => t('View node'),
          'href' => 'node/' . $log->nid,
        ];
        $actions[] = [
          'title' => t('View XML'),
          'href' => 'node/' . $log->nid . '/sduconnect-xml',
        ];
      }
    }
    $row = [
      format_date($log->date, 'custom', 'd-m-Y H:i:s'),
      $types[$log->type],
      $log->title,
      [
        'data' => [
          '#theme' => 'links__ctools_dropbutton',
          '#links' => $actions,
        ],
      ],
    ];
    $rows[] = $row;
  }

  $page['logs'] = [
    '#theme' => 'table',
    '#rows' => $rows,
    '#header' => [
      ['data' => t('Date'), 'width' => 140],
      ['data' => t('Type'), 'width' => 140],
      ['data' => t('Message')],
      ['width' => 140, 'data' => t('Actions')],
    ],
    '#empty' => t('No log messages found.'),
  ];
  $page['pager'] = [
    '#theme' => 'pager',
  ];

  return $page;
}

/**
 * Page callback for node/%/sduconnect-xml.
 */
function sduconnect_page_xml($node) {
  $item = db_select('sduconnect_item', 'i')->fields('i', [
    'cid',
    'external_id',
  ])->condition('i.nid', $node->nid)->execute()->fetchObject();
  if (!$item) {
    return MENU_NOT_FOUND;
  }
  $collection = sduconnect_collection_load($item->cid);
  $sduconnect_version = sduconnect_get_version($collection->type);
  $account_id = variable_get('sduconnect_account', '');
  $url = sprintf("https://rest.sduconnect.nl/single/%s/%s/account/%d/collectie/%d/item/%s.xml",
    $collection->type, $sduconnect_version, $account_id, $collection->external_id, $item->external_id);

  $data = drupal_http_request($url);
  if ($data->code != 200) {
    return MENU_NOT_FOUND;
  }
  drupal_add_http_header('Content-Type', 'text/xml');
  print $data->data;
}
