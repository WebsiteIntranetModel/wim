<?php



function mo_auth_configure_google_authenticator($form, &$form_state) {
  global $base_url, $user;
  $user = user_load($user->uid);
  /**
   * To check which method (Google Authenticator, Microsoft Authenticator, Authy Authenticator') is being configured by user
   */
  $url_parts   = MoAuthUtilities::mo_auth_get_url_parts();
  if ( in_array("google-authenticator", $url_parts ) ) {
    $App_Name = 'Google';
    $method_to_configure = AuthenticationType::$GOOGLE_AUTHENTICATOR['code'];
  } elseif ( in_array("microsoft-authenticator", $url_parts ) ) {
    $App_Name = 'Microsoft';
    $method_to_configure = AuthenticationType::$MICROSOFT_AUTHENTICATOR['code'];
  } elseif ( in_array("authy-authenticator", $url_parts ) ) {
    $App_Name = 'Authy';
    $method_to_configure = AuthenticationType::$AUTHY_AUTHENTICATOR['code'];
  } elseif ( in_array("lastpass-authenticator", $url_parts ) ) {
    $App_Name = 'LastPass';
    $method_to_configure = AuthenticationType::$LASTPASS_AUTHENTICATOR['code'];
  }
  if (array_key_exists('secret', $form_state['input']) === FALSE) {
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->getGoogleAuthSecret($miniorange_user);
    $qrCode = $response->qrCodeData;
    $secret = $response->secret;
  } else {
    $secret = $form_state['input']['secret'];
    $qrCode = $form_state['input']['qrCode'];
  }
  $form['header']['#markup'] = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Configure '.$App_Name.' Authenticator</div></div>' . mo_auth_create_form($base_url, $qrCode, $secret,$App_Name);

  $form['mo_auth_googleauth_token'] = array (
    '#type' => 'textfield',
    '#attributes' => array (
      'placeholder' => t('Enter  passcode.'),
      'class' => array (
        'mo2f-textbox',
        'mo2f-textbox-otp'
      ),
      'style' => 'width:200px',
      'autofocus' => 'true'
    ),
  );
  $form['secret'] = array (
    '#type' => 'hidden',
    '#value' => $secret
  );
  $form['mo_scan_qr_code_google_authenticator']['methodToConfigure'] = array(
    '#type' => 'hidden',
    '#value' => $method_to_configure
  );
  $form['qrCode'] = array (
    '#type' => 'hidden',
    '#value' => $qrCode
  );
  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Verify and Save')
  );
  $form['actions']['cancel'] = array (
    '#markup' => l(t('Cancel'), 'admin/config/people/mo_auth/setup')
  )
  // '#suffix' => '</div>',
  ;
  return $form;
}
function mo_auth_configure_google_authenticator_submit($form, &$form_state) {

  $form_state['rebuild'] = TRUE;
  $secret = $form_state['input']['secret'];
  $methodToConfigure = $form_state['input']['methodToConfigure'];
  global $base_url, $user;
  $user = user_load($user->uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  $otpToken = $form_state['input']['mo_auth_googleauth_token'];

  if (empty($otpToken)) {
    drupal_set_message(t('The passcode field is required. Please try again.'), 'warning');
    return;
  }

  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$GOOGLE_AUTHENTICATOR['code'], $secret, $otpToken, NULL);

  // Clear all the messages
  drupal_get_messages();
  // read API response
  if ($response->status == 'SUCCESS') {
    drupal_set_message(t(''), 'status');
    $configured_methods = mo_auth_get_configured_methods($user->uid);
    /**
     * Delete all the configured TOTP methods as only one can be used at a time
     */
    $configured_methods = array_values( array_diff( $configured_methods, array( 'MICROSOFT AUTHENTICATOR', 'GOOGLE AUTHENTICATOR', 'AUTHY AUTHENTICATOR', 'LASTPASS AUTHENTICATOR' ) ) );
    array_push($configured_methods, $methodToConfigure );
    $user->configured_auth_methods[LANGUAGE_NONE] = array();
    foreach ($configured_methods as $value){
      array_push($user->configured_auth_methods[LANGUAGE_NONE], array (
        'value' => $value
      ));
    }



    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $user_api_handler->update($miniorange_user);

    if ($response->status == 'SUCCESS') {
      user_save($user);
	  drupal_set_message(t($methodToConfigure.' configured successfully.'), 'status');
      drupal_goto('admin/config/people/mo_auth/setup');
    }
  } elseif ($response->status == 'FAILED') {
    form_set_error('form', t('The passcode you have entered is incorrect. Please try again.'));
    // $form_state['redirect'] = FALSE;
    // drupal_goto('admin/config/people/mo_auth/setup-twofactor');
  } else {
    form_set_error('form', t('An error occured while processing your request. Please try again.'));
    // drupal_goto('admin/config/people/mo_auth/setup-twofactor');
  }
}
function mo_auth_create_form($base_url, $qrCode, $secret,$appName) {

  $androidAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-google-authenticator-app-link.png');
  $iPhoneAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-google-authenticator-app-link.png');
  $androidAppQR = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-google-authenticator-app-qr.jpg');
  $iPhoneAppQR = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-google-authenticator-app-qr.jpg');

  $step1 = '<div>
        <div class="mo2f_googleauth-steps"><b>Step 1:</b> Download & Install the '.$appName.' Authenticator app.</div>
        <div style="margin-bottom:20px;">
        <div style="width:50%;float:left;min-width:450px;">
          <div class="mo2f_googleauth-download-manual">
            <div class="mo2f_googleauth-download-header">Manual Installation</div>
            <div>
              <div style="font-size:1.1em;padding:10px;">iPhone Users</div>
              <div>
              <div style="width:60%;float:left">
                <ul>
                  <li>Go to App Store.</li>
                  <li>Search for '.$appName.' Authenticator.</li>
                  <li>Download and install the App.</li>
                </ul>
              </div>
              <div style="width:40%;float:left;">
                <a target="_blank" href="https://itunes.apple.com/in/app/google-authenticator/id388497605?mt=8"><img src="' . $iPhoneAppLink . '"></a>
              </div>
              </div>
              <br><br><br><br>
              <div style="font-size:1.1em;padding:10px;">Android Users</div>
              <div>
              <div style="width:60%;float:left;">
                <ul>
                  <li>Go to Google Play Store.</li>
                  <li>Search for '.$appName.' Authenticator.</li>
                  <li>Download and install the App.</li>
                </ul>
              </div>
              <div style="width:40%;float:left;">
                <a target="_blank" href="https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2"><img src="' . $androidAppLink . '"></a>
              </div>
              </div>
            </div>
          </div>
        </div>
        <div style="width:50%;float:left;'.($appName!="Google"?'visibility: hidden;':'').'min-width:450px;">
          <div class="mo2f_googleauth-download-qrcode">
            <div class="mo2f_googleauth-download-header">Scan QR Code</div>
            <div style="text-align:center;padding:25px;">
            <div style="width:50%;float:left">
              <div>
                <img src="' . $iPhoneAppQR . '">
              </div>
              <span>Apple App Store<br />(iOS)</span>
            </div>
            <div style="width:50%;float:left">
              <div>
                <img src="' . $androidAppQR . '">
              </div>
              <span>Google Play Store<br />(Android)</span>
            </div>
            </div>
          </div>
        </div>
        </div>
        </div>';

  $secret = MoAuthUtilities::indentSecret($secret);
  $step2 = '<div style="width: 100%;float:left;padding-top: 10px;">
        <div class="mo2f_googleauth-steps"><b>Step 2:</b> Scan the below QR Code from '.$appName.' Authenticator app.</div>
        <div style="text-align:center">
        <div style="display:inline-block;width:33%">
          <img src="data:image/jpg;base64,' . $qrCode . '">
        </div>
        <div style="vertical-align: top;display: inline-flex;padding: 75px 0px;">
          <p style="margin: auto 10px;font-size:12pt;font-weight:bold">OR</p>
        </div>
        <div style="display:inline-block;width:33%">
          <div class="mo2f_googleauth-secret">
          <span style="padding:10px;">
            <p style="font-size: 10pt;">Use the following secret and Choose time-based.</p><p>
            </p><p id="googleAuthSecret" style="font-size: 13pt; font-weight: bold">' . $secret . '</p>
            <p style="font-size: 9pt;">(Spaces don&#39;t matter)</p><p>

        </p></span></div>
        </div>
        </div>
        </div>';

  $step3 = '<div style="width: 100%;float:left;padding-top: 10px;">
        <div class="mo2f_googleauth-steps"><b>Step 3:</b> Enter the Passcode generated by '.$appName.' Authenticator app.</div>
        </div>';
  return $step1 . $step2 . $step3;
}
