<?php

/**
 * @file
 * Contains install tasks for the WIM distribution.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 */
function wim_form_install_configure_form_alter(&$form, $form_state) {
  // Add a placeholder as example that one can choose an arbitrary site name.
  $form['site_information']['site_name']['#attributes']['placeholder'] = t('A WIM website');
}
