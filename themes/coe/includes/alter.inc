<?php
/**
 * @file
 * The file for overriding theme functions for the WIM STARTERKIT theme.
 */

/**
 * Implements hook_form_FORMID_alter
 */
function coe_form_search_block_form_alter(&$form, &$form_state) {
  unset($form['actions']['submit']['#value']); // It doesn't unset:(
}
