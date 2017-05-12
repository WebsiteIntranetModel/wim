<?php
/**
 * @file
 * wim_block_management.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function wim_block_management_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'search';
  $context->description = '';
  $context->tag = 'general';
  $context->conditions = array(
    'apachesolr_page' => array(
      'values' => array(
        'core_search' => 'core_search',
      ),
    ),
  );
  $context->reactions = array();
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
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
    'theme' => array(
      'values' => array(
        'wim' => 'wim',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('general');
  $export['sidewide'] = $context;

  return $export;
}
