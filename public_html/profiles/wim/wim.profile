<?php
/**
 * @file
 * Enables modules and site configuration for the WIM site installation.
 */

/**
 * Implements hook_form_FORM_ID_alter() for install_configure_form().
 *
 * Allows the profile to alter the site configuration form.
 */
function wim_form_install_configure_form_alter(&$form, $form_state) {
  // Add a placeholder as example that one can choose an arbitrary site name.
  $form['site_information']['site_name']['#attributes']['placeholder'] = t('A WIM website');
}
