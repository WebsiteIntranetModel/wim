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
 *
 * WIM-1208 - Remove certain options from Linkit.
 *
 * WIM-1245 - Changed widget type for Attachments.
 *
 * WIM-1193 - Fixed permissions for roles.
 */
function wim_update_7003(&$sandbox) {
  if (!module_exists('chosen')) {
    module_enable(array('chosen'));
  }

  if (module_exists('chosen')) {
    variable_set('chosen_jquery_selector', 'select.chosen-enable');
    variable_set('chosen_include', 0);
  }

  // Revert features.
  features_revert(array(
    'wim_text_formats',
    'wim_news',
  ));

  $role = user_role_load_by_name('administrator');
  user_role_grant_permissions($role->rid, array('change own role'));
}

/**
 * Enable the i18n modules to make fields translatable.
 */
function wim_update_7004(&$sandbox) {
  if (!module_exists('i18n')) {
    module_enable(array('i18n', 'i18n_field'));
  }
}

/**
 * Enable wimbase theme.
 */
function wim_update_7005(&$sandbox) {
  $theme_name = 'wimbase';
  $themes = list_themes();

  if (isset($themes[$theme_name]) && $themes[$theme_name]->status == 0) {
    theme_enable(array($theme_name));
  }
}

/**
 * Set correct metatags for Front Page.
 */
function wim_update_7006(&$sandbox) {

  $front_metatags = (object) array(
    'cid' => NULL,
    'instance' => 'global:frontpage',
    'config' => array(
      'title' => array('value' => '[site:name]'),
      'canonical' => array('value' => '[site:url]'),
      'shortlink' => array('value' => '[site:url]'),
    ),
  );

  metatag_config_save($front_metatags);
}

/**
 * Override all node alias patterns to use Hansel paths.
 */
function wim_update_7007(&$sandbox) {
  $types = node_type_get_types();

  $default_mapping = array(
    'agenda' => '[node:hansel-path]',
    'faq' => '[node:hansel-path]',
    'news' => '[node:hansel-path]',
    'page' => '[node:hansel-path]',
    'person' => '[node:hansel-path]',
    'product' => '[node:hansel-path]',
    'subject_page' => '[node:hansel-path]',
    'webform' => '[node:hansel-path]',
  );

  foreach ($types as $type) {
    if (!empty($default_mapping[$type->type])) {
      variable_set('pathauto_node_' . $type->type . '_pattern', $default_mapping[$type->type]);
    }
  }
}

/**
 * Give webmasters the ability to assign roles.
 */
function wim_update_7008(&$sandbox) {
  // Enable the module.
  if (!module_exists('roleassign')) {
    module_enable(array('roleassign'));
  }

  // Get webmaster role.
  if ($role = user_role_load_by_name('webmaster')) {
    // Get role id.
    $rid = $role->rid;

    // Assign the assign roles permission.
    user_role_grant_permissions($rid, array('assign roles'));

    // Get all the users roles and set variable to assign these for webmasters.
    $roles = user_roles();
    $role_assign = array();
    foreach ($roles as $key => $value) {
      if ($value !== 'anonymous user' && $value !== 'authenticated user') {
        $role_assign[] = $key;
      }
    }
    variable_set('roleassign_roles', $role_assign);

    return "Role assign added to webmaster";
  }
  else {
    return "Could not find role";
  }
}

/**
 * Add permissions for URL aliases to roles.
 */
function wim_update_7009(&$sandbox) {
  $permissions = array(
    'webmaster' => array('create url aliases', 'administer url aliases'),
    'content manager' => array('create url aliases', 'administer url aliases'),
    'content editor' => array('create url aliases'),
  );

  foreach ($permissions as $role_name => $permission) {
    $role = user_role_load_by_name($role_name);
    user_role_grant_permissions($role->rid, $permission);
  }
}

/**
 * Update WIM 2.0 default password policy to use punctuation in password.
 */
function wim_update_7010() {
  $policy = password_policy_policy_load(1);
  $policy['policy']['punctuation'] = '1';
  db_update('password_policy')->fields(array(
    'name' => $policy['name'],
    'description' => $policy['description'],
    'enabled' => $policy['enabled'],
    'policy' => serialize($policy['policy']),
    'expiration' => $policy['expiration'],
    'warning' => $policy['warning'],
  ))->condition('pid', 1)->execute();
}

/**
 * Assign roles fix & exclude administrator as assignable role.
 */
function wim_update_7011(&$sandbox) {
  // Get webmaster role.
  if ($role = user_role_load_by_name('webmaster')) {
    // Get role id.
    $rid = $role->rid;

    // Assign the assign roles permission.
    user_role_grant_permissions($rid, array('assign roles'));

    // Get all the users roles and set variable to assign these for webmasters.
    $roles = user_roles();

    $role_assign = array();
    foreach ($roles as $key => $value) {
      if ($value !== 'anonymous user' && $value !== 'authenticated user') {
        if ($value == 'administrator') {
          $role_assign[$key] = 0;
        }
        else {
          $role_assign[$key] = $key;
        }
      }
    }
    variable_set('roleassign_roles', $role_assign);

    return "Role assign added to webmaster";
  }
  else {
    return "Could not find role";
  }
}

/**
 * Add permissions for module: Revisioning.
 */
function wim_update_7012(&$sandbox) {
  // Enable the module.
  if (!module_exists('revisioning')) {
    module_enable(array('revisioning'));
  }

  $permissions = array(
    'webmaster' => array(
      'view revision status messages',
      'edit revisions',
      'publish revisions',
      'unpublish current revision',
    ),
    'content manager' => array(
      'view revision status messages',
      'edit revisions',
      'publish revisions',
      'unpublish current revision',
    ),
    'content editor' => array(
      'view revision status messages',
      'edit revisions',
      'publish revisions',
      'unpublish current revision',
    ),
  );

  foreach ($permissions as $role_name => $permission) {
    $role = user_role_load_by_name($role_name);
    user_role_grant_permissions($role->rid, $permission);
  }
}

/**
 * Add permissions for module: Diff.
 */
function wim_update_7013(&$sandbox) {
  // Enable the module.
  if (!module_exists('diff')) {
    module_enable(array('diff'));
  }

  $permissions = array(
    'webmaster' => array('diff view changes'),
    'content manager' => array('diff view changes'),
    'content editor' => array('diff view changes'),
  );

  foreach ($permissions as $role_name => $permission) {
    $role = user_role_load_by_name($role_name);
    user_role_grant_permissions($role->rid, $permission);
  }
}

/**
 * Enable set send attachment per emailadress.
 */
function wim_update_7014(&$sandbox) {
  if (module_exists('mimemail')) {
    variable_set('webform_email_html_capable', TRUE);
  }
}

/**
 * Set metatag settings.
 */
function wim_update_7015() {
  if (module_exists('metatag')) {
    variable_set('metatag_enable_user__user', FALSE);
    variable_set('metatag_enable_user', FALSE);
  }
}
