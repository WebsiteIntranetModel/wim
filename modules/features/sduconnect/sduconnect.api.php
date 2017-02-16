<?php

/**
 * @file
 * API for SDU connect module.
 */

/**
 * Implements hook_external_crawler_save_site_alter().
 *
 * Alter field content before save in node. Clear something or change.
 *
 *   Name of field that is going to be save.
 */
function hook_sduconnect_prepare_content_alter(&$field, $field_name) {
  $field = str_replace(PHP_EOL, '', $field);
}
