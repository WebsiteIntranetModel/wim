<?php
/**
 * @file
 * wim_block_management.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wim_block_management_context_default_contexts() {
  $export = [];

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'search';
  $context->description = '';
  $context->tag = 'general';
  $context->conditions = [
    'apachesolr_page' => [
      'values' => [
        'core_search' => 'core_search',
      ],
    ],
  ];
  $context->reactions = [];
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('general');
  $export['search'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'sidewide';
  $context->description = '';
  $context->tag = 'general';
  $context->conditions = [
    'sitewide' => [
      'values' => [
        1 => 1,
      ],
    ],
    'theme' => [
      'values' => [
        'wim' => 'wim',
      ],
    ],
  ];
  $context->reactions = [];
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('general');
  $export['sidewide'] = $context;

  return $export;
}
