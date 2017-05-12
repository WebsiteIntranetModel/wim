<?php
/**
 * @file
 * Admin settings form.
 */

/**
 * Implements hook_form().
 *
 * Page callback for admin/config/cookie-consent.
 */
function cookie_consent_admin_form() {
  $form = array();

  $cookie_consent_link_title = variable_get('cookie_consent_link_title', t('More information'));

  $form['cookie_consent_link'] = array(
    '#type' => 'textfield',
    '#title' => t('More information Link'),
    '#description' => t("Appends ':link_title' to the bottom of the Cookie Consent banner and privacy tabs. Provide full or internal url like node/[nid]o or alias. Leave empty to omit this behaviour.", array(
      ':link_title' => $cookie_consent_link_title,
    )),
    '#default_value' => variable_get('cookie_consent_link', ''),
  );

  $form['cookie_consent_link_title'] = array(
    '#type' => 'textfield',
    '#title' => t('More information Link Title'),
    '#description' => t('Override the title for the link.'),
    '#default_value' => $cookie_consent_link_title,
  );

  $roles = user_roles();
  $form['cookie_consent_roles'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Roles'),
    '#options' => $roles,
    '#size' => max(5, count($roles)),
    '#description' => t('Determine which roles see the cookie consent banner by default.'),
    '#default_value' => variable_get('cookie_consent_roles', array()),
  );

  $form['cookie_consent_pages'] = array(
    '#title' => t('Exclude Cookie Consent'),
    '#type' => 'textarea',
    '#description' => t('Cookie Consent will be excluded on the following pages. Fill in one path per line.'),
    '#default_value' => variable_get('cookie_consent_pages', ''),
  );

  if (module_exists('domain')) {
    foreach (domain_domains() as $domain) {
      $domain_options[$domain['domain_id']] = $domain['sitename'];
    }

    $form['cookie_consent_domains'] = array(
      '#type' => 'select',
      '#multiple' => TRUE,
      '#title' => t('Exclude Domains'),
      '#options' => $domain_options,
      '#default_value' => variable_get('cookie_consent_domains', array()),
      '#description' => t('Determine on which domains the cookie consent should not be shown.'),
      '#size' => max(5, count($domain_options)),
    );
  }

  $form['cookie_consent_style'] = array(
    '#type' => 'select',
    '#options' => array(
      'dark' => t('Dark'),
      'light' => t('Light'),
      'monochrome' => t('Monochrome'),
      'custom' => t('Custom'),
    ),
    '#default_value' => variable_get('cookie_consent_style', 'custom'),
    '#title' => t('Cookie Consent Style'),
    '#description' => t('Select the desired style for the Cookie Consent feature. If you choose custom, you have to implement your own style.'),
  );

  $form['cookie_consent_privacy'] = array(
    '#type' => 'checkbox',
    '#title' => t('Hide the Privacy Tab'),
    '#description' => t('Whether the privacy settings tab should be hidden after the user has given consent.'),
    '#default_value' => variable_get('cookie_consent_privacy', 1),
  );

  $form['cookie_consent_tag_position'] = array(
    '#title' => t('Privacy Tab Position'),
    '#type' => 'select',
    '#options' => array(
      'bottom-right' => t('Bottom Right'),
      'bottom-left' => t('Bottom Left'),
      'vertical-left' => t('Vertical Left'),
      'vertical-right' => t('Vertical Right'),
    ),
    '#default_value' => variable_get('cookie_consent_tag_position', 'vertical-right'),
    '#description' => t('If the privacy tab is enabled above, you can determine where it will be displayed on the page.'),
  );

  $form['cookie_consent_banner_position'] = array(
    '#type' => 'select',
    '#title' => t('Banner position'),
    '#options' => array(
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    '#default_value' => variable_get('cookie_consent_banner_position', 'bottom'),
    '#description' => t('Determine the position of the Cookie Consent banner on the page.'),
  );

  $form['cookie_consent_refresh_on_consent'] = array(
    '#type' => 'checkbox',
    '#title' => t('Refresh on consent'),
    '#description' => t('Whether the browser window should refresh after consent is given.'),
    '#default_value' => variable_get('cookie_consent_refresh_on_consent', 0),
  );

  $form['cookie_consent_filter_iframe'] = array(
    '#type' => 'checkbox',
    '#title' => t('Filter Iframe tags'),
    '#description' => t('Select this if you want to filter out iframes as well. Deselect if you want to filter only on script tags.'),
    '#default_value' => variable_get('cookie_consent_filter_iframe', FALSE),
  );

  foreach (module_invoke_all('cookie_consent_categories') as $category => $info) {
    $form['cookie_consent_' . $category] = array(
      '#type' => 'textarea',
      '#title' => t('@category Scripts', array('@category' => $info['title'])),
      '#description' => check_plain($info['description']),
      '#default_value' => variable_get('cookie_consent_' . $category, ''),
    );
  }

  return system_settings_form($form);
}
