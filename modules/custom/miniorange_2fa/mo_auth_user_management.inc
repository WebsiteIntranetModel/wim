<?php
/**
 * @file
 * Contains support form for miniOrange 2FA Login Module.
 */

/**
 * Showing Support form info.
 */
function mo_auth_user_management($form, &$form_state){
  global $base_url;
  $register_url = $base_url . '/admin/config/people/mo_auth/';
  $disabled = FALSE;
  if ( !MoAuthUtilities::isCustomerRegistered() ) {
    $disabled=TRUE;
    $form['header'] = array(
      '#markup' => '<div class="mo2f_configure_message">You need to <a href="'.$register_url.'" >Register/Login</a> using miniOrange account before using this module.</div>',
    );
  }

  $form['header_top_style_1'] = array(
    '#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container"><div class="mo2f-setup-header">
                    <div class="mo2f-setup-header-top-left">User Management</div></div><div class="mo2f-info"></div>'
  );


  $form['markup_idp_login_note'] = array(
    '#markup' => '<div class="mo2f_highlight_background_note"><b>Note: </b>If you want to reset the 2FA for any user, you can do it from this section. 
                  <b>If you reset the 2FA for any user, than that user has to go through the inline registration process to setup the 2FA again.</b></div></br>',
  );

  $form['mo_auth_reset_2fa_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Enter Username'),
    '#attributes' => array('placeholder' => t('Enter Username')),
    '#disabled' => $disabled,
    '#description' => '<b>' . t(' Note: ') . '</b>' . t('Enter the username for which you want to reset the 2FA.'),
  );

  $form['mo_auth_reset_2fa_submit'] = array(
    '#type' => 'submit',
    '#disabled' => $disabled,
    '#value' => t('Reset 2FA'),
    '#suffix' => '</div>'
  );

  MoAuthUtilities::addSupportForm($form, $form_state);

  return $form;
}


function mo_auth_user_management_submit($form, &$form_state){
  $username = $form['mo_auth_reset_2fa_username']['#value'];
  $user = user_load_by_name($username);
  if ( $user === FALSE ) {
    drupal_set_message(t("User ") . "<strong>" . $username . "</strong>".t(" not found." ),'error');
    return;
  }

  $edit['configured_auth_methods']['und'] = array();
  $edit['miniorange_registered_email']['und'] = array();

  user_save($user, $edit);

  drupal_set_message(t("You have reset the 2FA for "). "<strong>". $username ."</strong>" . t(" successfully." ),'status');

}
