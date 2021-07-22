<?php
/**
 * @file
 * Contains Setup Two-Factor page for miniOrange 2FA Login Module.
 */

/**
 * Showing Setup Two-Factor page.
 */
function mo_auth_setup_twofactor($form, &$form_state) {

  global $base_url;
  $register_url = $base_url . '/admin/config/people/mo_auth/';

  drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/mo_hardwareToken.js', 'file');

  $disabled = FALSE;
  if (! MoAuthUtilities::isCustomerRegistered()) {
    $disabled = TRUE;
    $form['header'] = array(
      '#markup' => '<div class="mo2f_configure_message">You need to <a href="'.$register_url.'" >Register/Login</a> using miniOrange account before using this module.</div>'
    );
    #return $form;
  }
  global $user, $base_url;
  $user = user_load($user->uid);

  if(!is_null($user->miniorange_registered_email) && !empty($user->miniorange_registered_email))
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  else
    $user_email = NULL;

  $customer = new MiniorangeCustomerProfile();
  $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, '', '', '');
  $response = $user_api_handler->get($miniorange_user);

  $configured_methods = mo_auth_get_configured_methods($user->uid);

  $users_active_method = NULL;
  if( is_object( $response ) && isset( $response->authType ) && $response->authType != 'GOOGLE AUTHENTICATOR' ) {
    $users_active_method = AuthenticationType::getAuthType( $response->authType );
  }else {
    if ( in_array( 'GOOGLE AUTHENTICATOR', $configured_methods ) ) {
      $users_active_method = AuthenticationType::getAuthType( 'GOOGLE AUTHENTICATOR' );
    } elseif ( in_array( 'MICROSOFT AUTHENTICATOR', $configured_methods ) ) {
      $users_active_method = AuthenticationType::getAuthType( 'MICROSOFT AUTHENTICATOR' );
    } elseif ( in_array( 'AUTHY AUTHENTICATOR', $configured_methods ) ) {
      $users_active_method = AuthenticationType::getAuthType( 'AUTHY AUTHENTICATOR' );
    } elseif ( in_array( 'LASTPASS AUTHENTICATOR', $configured_methods ) ) {
      $users_active_method = AuthenticationType::getAuthType( 'LASTPASS AUTHENTICATOR' );
    }
  }


  $form['header_top']['#markup'] = '<div class="mo2f-setup-header">
      <span class="mo2f-setup-header-top-left">Setup Two-Factor</span>
      <span class="mo2f-setup-header-top-center">Active Method - <b>' . drupal_strtoupper($users_active_method['name']) . '</b></span>
      <span class="mo2f-setup-header-top-right">' . l(t('Need Support?'), 'admin/config/people/mo_auth/support') . '</span>
    </div>
    <div style="width:80%;display:inline-block"><div class="mo2f-info" style="padding:15px 0px;"><b>Select any Two-Factor of your choice below and complete its setup.</b></div></div><div style="width:20%;display:inline-block;text-align: right;"></div>';


  $form['header_methods']['#markup'] = '<div class="mo2f-setup-methods-info-wrap">
        <div class="mo2f-setup-methods-info-left"><span class="mo2f-color-icon mo2f-active-method"></span>- Active Method</div>
        <div class="mo2f-setup-methods-info-center"><span class="mo2f-color-icon mo2f-configured-method"></span>- Configured Method</div>
        <div class="mo2f-setup-methods-info-right"><span class="mo2f-color-icon mo2f-unconfigured-method"></span>- Unconfigured Method</div>
      </div>';

  $emailVerificationOption            = mo_auth_create_auth_type($user, AuthenticationType::$EMAIL_VERIFICATION, $configured_methods, $users_active_method['code'], FALSE, $base_url);
  $kbaAuth                            = mo_auth_create_auth_type($user, AuthenticationType::$KBA, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $googleAuthenticatorOption          = mo_auth_create_auth_type($user, AuthenticationType::$GOOGLE_AUTHENTICATOR, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $qrCodeAuthenticatorOption          = mo_auth_create_auth_type($user, AuthenticationType::$QR_CODE, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $softTokenOption                    = mo_auth_create_auth_type($user, AuthenticationType::$SOFT_TOKEN, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $pushNotificationsOption            = mo_auth_create_auth_type($user, AuthenticationType::$PUSH_NOTIFICATIONS, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $OTPOverSMSOption                   = mo_auth_create_auth_type($user, AuthenticationType::$SMS, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $OTPOverEMAILOption                 = mo_auth_create_auth_type($user, AuthenticationType::$OTP_OVER_EMAIL, $configured_methods, $users_active_method['code'], TRUE, $base_url );
  $OTPOverSMSandEMAILOption           = mo_auth_create_auth_type($user, AuthenticationType::$SMS_AND_EMAIL, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $OTPOverPHONEOption                 = mo_auth_create_auth_type($user, AuthenticationType::$OTP_OVER_PHONE, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $HardwareTokenOption                = mo_auth_create_auth_type($user, AuthenticationType::$HARDWARE_TOKEN, $configured_methods, $users_active_method['code'], FALSE, $base_url);
  $microsoftAuthenticationOption      = mo_auth_create_auth_type($user,AuthenticationType::$MICROSOFT_AUTHENTICATOR, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $authyAuthenticationOption          = mo_auth_create_auth_type($user,AuthenticationType::$AUTHY_AUTHENTICATOR, $configured_methods, $users_active_method['code'], TRUE, $base_url);
  $lastPassAuthenticationOption       = mo_auth_create_auth_type($user,AuthenticationType::$LASTPASS_AUTHENTICATOR, $configured_methods, $users_active_method['code'], TRUE, $base_url);

  $options = array(
    AuthenticationType::$EMAIL_VERIFICATION['code']       => $emailVerificationOption,
    AuthenticationType::$GOOGLE_AUTHENTICATOR['code']     => $googleAuthenticatorOption,
    AuthenticationType::$MICROSOFT_AUTHENTICATOR['code']  => $microsoftAuthenticationOption,
    AuthenticationType::$AUTHY_AUTHENTICATOR['code']      => $authyAuthenticationOption,
    AuthenticationType::$LASTPASS_AUTHENTICATOR['code']   => $lastPassAuthenticationOption,
    AuthenticationType::$KBA['code']                      => $kbaAuth,
    AuthenticationType::$OTP_OVER_EMAIL['code']           => $OTPOverEMAILOption,
    AuthenticationType::$SMS['code']                      => $OTPOverSMSOption,
    AuthenticationType::$SMS_AND_EMAIL['code']            => $OTPOverSMSandEMAILOption,
    AuthenticationType::$OTP_OVER_PHONE['code']           => $OTPOverPHONEOption,
    AuthenticationType::$QR_CODE['code']                  => $qrCodeAuthenticatorOption,
    AuthenticationType::$PUSH_NOTIFICATIONS['code']       => $pushNotificationsOption,
    AuthenticationType::$SOFT_TOKEN['code']               => $softTokenOption,
    AuthenticationType::$HARDWARE_TOKEN['code']           => $HardwareTokenOption,
  );

  $form['mo_auth_method'] = array(
    '#type' => 'radios',
    '#default_value' => $users_active_method['code'],
    '#options' => $options,
    '#required' => TRUE,
    '#disabled'=>$disabled,
  );

  $path = ($disabled) ? $register_url : $base_url . '/?q=admin/config/people/mo_auth/setup/user/' . $user->uid . '/configure/';

  $form['#attached']['js'][] = array(
    'data' => array(
      'mo_settings' => array(
        'path' => $path,
      ),
    ),
    'type' => 'setting',
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit_bottom'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('style' => 'display:inline-block;'),
    '#disabled'=>$disabled,
  );
  return $form;
}

function mo_auth_setup_twofactor_submit($form, &$form_state) {
  global $base_url, $user;
  $form_state['rebuild'] = TRUE;
  $authType = $form_state['input']['mo_auth_method'];
  $configured_methods = mo_auth_get_configured_methods($user->uid);
  if (in_array($authType, $configured_methods)) {
    $user = user_load($user->uid);
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, $authType);
    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $user_api_handler->update($miniorange_user);
    if ($response->status == 'SUCCESS') {
      drupal_set_message(t('Authentication method updated successfully.'), 'status');
      drupal_goto('admin/config/people/mo_auth/setup');
    } else {
      drupal_set_message(t('An error occured while updating the authentication type. Please try again.'), 'error');
      drupal_goto('admin/config/people/mo_auth/setup');
    }
  } else {
    drupal_set_message(t('Please configure this authentication method first to enable it.'), 'error');
    drupal_goto('admin/config/people/mo_auth/setup');
  }
}

function mo_auth_create_auth_type($user, $authType, $configuredMethods, $active_method, $reconfigure_allowed, $base_url) {

  $disable=FALSE;
  if (! MoAuthUtilities::isCustomerRegistered()) {
    $disable=TRUE;
  }

  $register_url = $base_url . '/admin/config/people/mo_auth/';

  $label_title = 'Supported in ' . implode(', ', $authType['supported-for']);;
  $supported_for_icon_class = '';
  if (in_array('Landline', $authType['supported-for'])) {
    $supported_for_icon_class = 'mo2f-landline';
  } elseif (in_array('Feature Phones', $authType['supported-for'])) {
    $supported_for_icon_class = 'mo2f-smartphone-feature-phone';
  } elseif (in_array('Laptops', $authType['supported-for'])) {
    $supported_for_icon_class = 'mo2f-laptop';
  } elseif (in_array('Smartphones', $authType['supported-for'])) {
    $supported_for_icon_class = 'mo2f-smartphone';
  } elseif (in_array('hardware-token', $authType['supported-for'])) {
    $supported_for_icon_class = 'mo2f-hardware-token';
  }
  $config_type_class = 'mo2f-unconfigured-method';
  if ($authType['code'] == $active_method) {
    $config_type_class = 'mo2f-active-method';
  } elseif (in_array($authType['code'], $configuredMethods)) {
    $config_type_class = 'mo2f-configured-method';
  }

  $configured = 'false';
  $classes = $supported_for_icon_class . ' ' . $config_type_class;
  if ($disable) {
    $test = '<a href="'.$register_url.'">Configure</a>';
    if (! empty($configuredMethods) && in_array($authType['code'], $configuredMethods)) {
      $test = '<a href="'.$register_url.'">Test</a>';
      if ($reconfigure_allowed === TRUE) {
        $test .= ' | <a href="'.$register_url.'">Re-configure</a>';
      }
    }
  }
  else{
    if($authType == AuthenticationType::$HARDWARE_TOKEN){
      $test = '<a href="https://www.miniorange.com/contact" target="_blank">Contact Us</a>';
    }else
      $test = '<a href="' . $base_url . '/?q=admin/config/people/mo_auth/setup/user/' . $user->uid . '/configure/' . $authType['id'] . '">Configure</a>';
    if (! empty($configuredMethods) && in_array($authType['code'], $configuredMethods)) {
      $test = '<a href="' . $base_url . '/?q=admin/config/people/mo_auth/setup/user/' . $user->uid . '/test/' . $authType['id'] .'">Test</a>';
      if ($reconfigure_allowed === TRUE) {
        $test .= ' | <a href="' . $base_url . '/?q=admin/config/people/mo_auth/setup/user/' . $user->uid . '/configure/' . $authType['id'] .'">Re-configure</a>';
      }
      $configured = 'true';
    }
  }
  $html = '<div>
        <div class="mo2f-method" data-id="' . $authType['id'] . '" data-configured="'. $configured .'">' . $authType['name'] . '</div>
        <p>' . $authType['description'] . '</p>
        <div class="' . $classes . '" title="' . $label_title . '">'
    . $test . '</div>
      </div>';

  return $html;
}
