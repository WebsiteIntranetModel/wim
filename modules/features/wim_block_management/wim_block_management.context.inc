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
  $context->name = 'sidewide';
  $context->description = '';
  $context->tag = 'general';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~admin/*' => '~admin/*',
        '~felix-blocks/*' => '~felix-blocks/*',
      ),
    ),
    'sitewide' => array(
      'values' => array(
        1 => 1,
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
