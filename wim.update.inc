<?php

/**
 * @file
 * Contains update tasks for the WIM distribution.
 */

/**
 * WIM-878 - Add CKEditor tab button.
 */
function wim_update_7000(&$sandbox) {
  // Reinstall profile.
  _wim_wysiwyg_profile_install();
  // Revert feature.
  features_revert(array('wim_text_formats'));
}

/**
 * WIM-627 - Add Lead Paragraph to content types.
 */
function wim_update_7001(&$sandbox) {
  // Revert features.
  features_revert(array(
    'wim_block_management',
    'wim_news',
    'wim_product',
    'wim_page',
    'wim_agenda',
  ));
}
