<?php

/**
 * Page callback for pages list.
 */
function external_crawler_page_list() {
  $query = db_select('external_crawler_site', 's')
    ->fields('s', array('name', 'check_interval'))
    ->orderBy('s.name')
    ->extend('PagerDefault')
    ->limit(10);
  $sites = $query->execute()->fetchAll();
  $header = array(t('Name'), t('Check interval'));
  $rows = array();
  foreach ($sites as $site) {
    $rows[] = array(
      check_plain($site->name),
      format_interval($site->check_interval),
    );
  }
  return array(
    'table' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows,
      '#empty' => t('No sites defined yet.'),
    ),
    'pager' => array('#theme' => 'pager'),
  );
}
