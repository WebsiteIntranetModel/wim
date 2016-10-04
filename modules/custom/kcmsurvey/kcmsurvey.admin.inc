<?php
/**
 * @file
 * Administration pages code.
 */

/**
 * Admin settings form.
 */
function kcmsurvey_admin_form($form, &$form_state) {

  $form['kcmsurvey_script_url'] = array(
    '#type' => 'textfield',
    '#title' => t('KCM Survey script url'),
    '#default_value' => variable_get('kcmsurvey_script_url'),
    '#description' => t('Script provided by https://www.kcmsurvey.nl/ service.'),
  );

  $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array(
    '%blog' => 'blog',
    '%blog-wildcard' => 'blog/*',
    '%front' => '<front>',
  ));
  $title = t('Pages');

  /** @var array $pages */
  $pages = variable_get('kcmsurvey', array());
  $form['kcmsurvey']['visibility'] = array(
    '#type' => 'radios',
    '#title' => t('Pages where the script should be active'),
    '#options' => array(
      BLOCK_VISIBILITY_NOTLISTED => t('All pages except those listed'),
      BLOCK_VISIBILITY_LISTED => t('Only the listed pages'),
    ),
    '#default_value' => isset($pages['visibility']) ? $pages['visibility'] : BLOCK_VISIBILITY_NOTLISTED,
  );
  $form['kcmsurvey']['pages'] = array(
    '#type' => 'textarea',
    '#title' => '<span class="element-invisible">' . $title . '</span>',
    '#default_value' => isset($pages['pages']) ? $pages['pages'] : '',
    '#description' => $description,
  );

  $form['#tree'] = TRUE;
  return system_settings_form($form);
}
