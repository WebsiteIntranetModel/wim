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

/**
 * WIM-1186 - Can not add a link to an image in ckeditor.
 *
 * WIM-1072 - Sitemap XML support.
 */
function wim_update_7002(&$sandbox) {
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
    'wim_addition_faq_product_fields',
    'wim_text_formats',
    'wim_block_management',
  ));

  // Exclude some basic page nodes.
  $nodes = array(
    'node_403' => variable_get('site_403'),
    'node_404' => variable_get('site_404'),
    'node_frontpage' => variable_get('site_frontpage'),
  );

  // Exclude this nodes from sitemap.xml.
  if (module_exists('xmlsitemap')) {
    foreach ($nodes as $path) {
      $node = menu_get_object('node', 1, $path);
      $link = xmlsitemap_node_create_link($node);
      $link['status'] = 0;
      $link['status_override'] = 1;
      xmlsitemap_link_save($link, array($link['type'] => $node));
    }
    // On next cron run items will be removed.
    variable_set('xmlsitemap_rebuild_needed', TRUE);

    $role = user_role_load_by_name('webmaster');
    user_role_grant_permissions($role->rid, array('administer xmlsitemap'));
    user_role_grant_permissions($role->rid, array('create files'));
    $role = user_role_load_by_name('content manager');
    user_role_grant_permissions($role->rid, array('create files'));
    $role = user_role_load_by_name('content editor');
    user_role_grant_permissions($role->rid, array('create files'));
  }

}

/**
 * Enable Chosen module.
 */
function wim_update_7003(&$sandbox) {
  if (!module_exists('chosen')) {
    module_enable('chosen');
  }
}

/**
 * WIM-1208 - Remove certain options from Linkit.
 */
function wim_update_7004(&$sandbox) {
  // Revert features.
  features_revert(array(
    'wim_text_formats',
    'wim_news',
  ));
}
