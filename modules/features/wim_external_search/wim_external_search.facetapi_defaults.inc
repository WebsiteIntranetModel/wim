<?php
/**
 * @file
 * wim_external_search.facetapi_defaults.inc
 */

/**
 * Implements hook_facetapi_default_facet_settings().
 */
function wim_external_search_facetapi_default_facet_settings() {
  $export = [];

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@solr::external_source';
  $facet->searcher = 'apachesolr@solr';
  $facet->realm = '';
  $facet->facet = 'external_source';
  $facet->enabled = FALSE;
  $facet->settings = [
    'operator' => 'or',
    'hard_limit' => '50',
    'dependencies' => [],
    'facet_mincount' => 1,
    'facet_missing' => 0,
    'flatten' => 0,
    'individual_parent' => 0,
    'query_type' => 'term',
    'limit_active_items' => 0,
  ];
  $export['apachesolr@solr::external_source'] = $facet;

  $facet = new stdClass();
  $facet->disabled = FALSE; /* Edit this to true to make a default facet disabled initially */
  $facet->api_version = 1;
  $facet->name = 'apachesolr@solr:block:external_source';
  $facet->searcher = 'apachesolr@solr';
  $facet->realm = 'block';
  $facet->facet = 'external_source';
  $facet->enabled = TRUE;
  $facet->settings = [
    'weight' => 0,
    'widget' => 'facetapi_links',
    'filters' => [],
    'active_sorts' => [
      'indexed' => 0,
      'display' => 0,
      'count' => 0,
      'active' => 0,
    ],
    'sort_weight' => [
      'indexed' => '0',
      'display' => '0',
      'count' => '0',
      'active' => '0',
    ],
    'sort_order' => [
      'indexed' => '4',
      'display' => '4',
      'count' => '4',
      'active' => '4',
    ],
    'empty_behavior' => 'text',
    'facet_more_text' => 'Show more',
    'facet_fewer_text' => 'Show fewer',
    'soft_limit' => '5',
    'nofollow' => 1,
    'show_expanded' => 0,
    'ranges' => [
      'past_hour' => [
        'label' => 'Past hour',
        'machine_name' => 'past_hour',
        'date_range_start_op' => '-',
        'date_range_start_amount' => '1',
        'date_range_start_unit' => 'HOUR',
        'date_range_end_op' => 'NOW',
        'date_range_end_amount' => '',
        'date_range_end_unit' => 'HOUR',
        'weight' => '0',
        'delete' => 0,
      ],
      'past_24_hours' => [
        'label' => 'Past 24 hours',
        'machine_name' => 'past_24_hours',
        'date_range_start_op' => '-',
        'date_range_start_amount' => '24',
        'date_range_start_unit' => 'HOUR',
        'date_range_end_op' => 'NOW',
        'date_range_end_amount' => '',
        'date_range_end_unit' => 'HOUR',
        'weight' => '1',
        'delete' => 0,
      ],
      'past_week' => [
        'label' => 'Past week',
        'machine_name' => 'past_week',
        'date_range_start_op' => '-',
        'date_range_start_amount' => '7',
        'date_range_start_unit' => 'DAY',
        'date_range_end_op' => 'NOW',
        'date_range_end_amount' => '',
        'date_range_end_unit' => 'HOUR',
        'weight' => '2',
        'delete' => 0,
      ],
      'past_month' => [
        'label' => 'Past month',
        'machine_name' => 'past_month',
        'date_range_start_op' => '-',
        'date_range_start_amount' => '1',
        'date_range_start_unit' => 'MONTH',
        'date_range_end_op' => 'NOW',
        'date_range_end_amount' => '',
        'date_range_end_unit' => 'HOUR',
        'weight' => '3',
        'delete' => 0,
      ],
      'past_year' => [
        'label' => 'Past year',
        'machine_name' => 'past_year',
        'date_range_start_op' => '-',
        'date_range_start_amount' => '1',
        'date_range_start_unit' => 'YEAR',
        'date_range_end_op' => 'NOW',
        'date_range_end_amount' => '',
        'date_range_end_unit' => 'HOUR',
        'weight' => '4',
        'delete' => 0,
      ],
    ],
    'date_ranges' => [
      'add_range' => 'Add a new date range',
    ],
    'empty_text' => [
      'value' => '<p>No matches for this filter.</p>',
      'format' => 'full_html',
    ],
  ];
  $export['apachesolr@solr:block:external_source'] = $facet;

  return $export;
}
