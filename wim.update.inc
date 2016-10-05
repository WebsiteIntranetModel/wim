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
 * WIM-1186 - Can not add a link to an image in ckeditor.
 * WIM-1072 - Sitemap XML support.
 */
function wim_update_7001(&$sandbox) {
  // Change media render.
  variable_set('media_wysiwyg_default_render', 'field_attach');

  // Revert features.
  features_revert(array(
    'wim_core',
    'wim_agenda',
    'wim_faq',
    'wim_news',
    'wim_page',
    'wim_person',
    'wim_product',
    'wim_subject',
    'wim_webform',
  ));
}
