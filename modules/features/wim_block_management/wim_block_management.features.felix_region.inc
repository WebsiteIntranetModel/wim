<?php
/**
 * @file
 * wim_block_management.features.felix_region.inc
 */

/**
 * Implements hook_felix_default_regions().
 */
function wim_block_management_felix_default_regions() {
  $regions = array();
  $regions['content'] = array(
    'name' => 'content',
    'title' => 'Content',
    'region' => 'content',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['footer-first'] = array(
    'name' => 'footer-first',
    'title' => 'Footer First',
    'region' => 'footer_first',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['footer-second'] = array(
    'name' => 'footer-second',
    'title' => 'Footer Second',
    'region' => 'footer_second',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['footer-third'] = array(
    'name' => 'footer-third',
    'title' => 'Footer Third',
    'region' => 'footer_third',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['highlighted'] = array(
    'name' => 'highlighted',
    'title' => 'Highlighted',
    'region' => 'highlighted',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['primary'] = array(
    'name' => 'primary',
    'title' => 'Sidebar First',
    'region' => 'sidebar_first',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  $regions['secondary'] = array(
    'name' => 'secondary',
    'title' => 'Sidebar Second',
    'region' => 'sidebar_second',
    'weight' => 0,
    'context' => 'sidewide',
    'block_set' => 'default',
    'data' => array(
      'hash' => array(),
    ),
  );
  return $regions;
}
