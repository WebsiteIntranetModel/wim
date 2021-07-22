<?php
function mo_auth_configure_qrcode_authentication($form, &$form_state) {
  global $base_url, $user;
  $user = user_load($user->uid);
  $form['actions'] = array (
    '#type' => 'actions'
  );

  /* To check which method (Soft Token, QR Code, Push Notification') is being configured by user
   * $authTypeCode:- Code of the authentication Type
   * $messageHeader:- Title of the Page
   */
  $query_param = $_GET["q"];
  $url_parts = explode('/',$query_param);

  $authTypeCode = '';
  $messageHeader = '';
  if (in_array("soft-token", $url_parts)) {
	$authTypeCode = AuthenticationType::$SOFT_TOKEN['code'];
	$messageHeader = 'Configure Soft Token';
  } elseif (in_array("push-notifications",$url_parts)) {
	$authTypeCode = AuthenticationType::$PUSH_NOTIFICATIONS['code'];
	$messageHeader = 'Configure Push Notifications';
  }else {
	$authTypeCode = AuthenticationType::$QR_CODE['code'];
    $messageHeader = 'Configure QR Code Authentication';
  }

  if (array_key_exists('txId', $form_state['input']) === FALSE) {
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$QR_CODE['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$QR_CODE['code'], NULL, NULL, NULL);
    $qrCode = $response->qrCode;
    $form['header']['#markup'] = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">' . $messageHeader . '</div></div>' . mo_auth_create_form($base_url, $qrCode);


    $form['#attached']['js'][] = array (
      'data' => array (
        'mo_authentication' => array (
          'txId' => $response->txId,
          'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_REGISTRATION_STATUS_API
        )
      ),
      'type' => 'setting'
    );
    $form['txId'] = array (
      '#type' => 'hidden',
      '#value' => $response->txId
    );

	$form['authTypeCode'] = array (
      '#type' => 'hidden',
      '#value' => $authTypeCode
    );

  }

  $form['actions']['submit'] = array (
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array (
      'class' => array (
        'element-invisible'
      )
    )
  );
  $form['actions']['cancel'] = array (
    '#markup' => l(t('Cancel'), 'admin/config/people/mo_auth/setup'),
    '#suffix' => '</div>',
    '#attributes' => array (
      'style' => 'display:inline-block'
    )
  );
  return $form;
}
function mo_auth_configure_qrcode_authentication_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $txId = $form_state['input']['txId'];
  $authTypeCode = $form_state['input']['authTypeCode'];
  global $base_url, $user;
  $user = user_load($user->uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$QR_CODE['code']);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

  $response = $auth_api_handler->getRegistrationStatus($txId);

  // Clear all the messages
  drupal_get_messages();
  // read API response
  if ($response->status == 'SUCCESS') {
    $configured_methods = mo_auth_get_configured_methods($user->uid);
    // $configured_methods[] = AuthenticationType::$GOOGLE_AUTHENTICATOR['code'];
    // $user->configured_auth_methods[LANGUAGE_NONE][0]['value'] = $configured_methods;

	/* If one of the methods in Soft Token, QR Code Authentication, Push Notification is configured then all three methods are configured.*/
    if (! in_array(AuthenticationType::$SOFT_TOKEN['code'], $configured_methods)) {
      array_push($user->configured_auth_methods[LANGUAGE_NONE], array (
        'value' => AuthenticationType::$SOFT_TOKEN['code']
      ));
    }
    if (! in_array(AuthenticationType::$QR_CODE['code'], $configured_methods)) {
      array_push($user->configured_auth_methods[LANGUAGE_NONE], array (
        'value' => AuthenticationType::$QR_CODE['code']
      ));
    }
	if (! in_array(AuthenticationType::$PUSH_NOTIFICATIONS['code'], $configured_methods)) {
      array_push($user->configured_auth_methods[LANGUAGE_NONE], array (
        'value' => AuthenticationType::$PUSH_NOTIFICATIONS['code']
      ));
    }

    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

	// Updating the authentication method for the user
	$miniorange_user->setAuthType($authTypeCode);
    $response = $user_api_handler->update($miniorange_user);
    if ($response->status == 'SUCCESS') {
      user_save($user);
	  if($authTypeCode == AuthenticationType::$SOFT_TOKEN['code']){
		drupal_set_message(t('Soft Token configured successfully.'), 'status');
	  } elseif ($authTypeCode == AuthenticationType::$PUSH_NOTIFICATIONS['code']) {
		drupal_set_message(t('Push Notifications configured successfully.'), 'status');
	  } else {
		drupal_set_message(t('QR Code Authentication configured successfully.'), 'status');
	  }
      drupal_goto('admin/config/people/mo_auth/setup');
    }
    return;
  }
  drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
  watchdog('miniorange_2fa', $response->message);
  drupal_goto('admin/config/people/mo_auth/setup');
}
function mo_auth_create_form($base_url, $qrCode) {
  $androidAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-google-authenticator-app-link.png');
  $iPhoneAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-google-authenticator-app-link.png');
  $androidAppQR = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-mo-authenticator-app-qr.jpg');
  $iPhoneAppQR = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-mo-authenticator-app-qr.png');

  $step1 = '<div>
        <div class="mo2f_googleauth-steps"><b>Step 1:</b> Download & Install the miniOrange Authenticator app.</div>
        <div style="margin-bottom:20px;">
        <div style="width:50%;float:left;">
          <div class="mo2f_googleauth-download-manual">
            <div class="mo2f_googleauth-download-header">Manual Installation</div>
            <div>
              <div style="font-size:1.1em;padding:10px;">iPhone Users</div>
              <div>
              <div style="width:60%;float:left">
                <ul>
                  <li>Go to App Store.</li>
                  <li>Search for miniOrange.</li>
                  <li>Download and install the app. <b>(NOT MOAuth)</b></li>
                </ul>
              </div>
              <div style="width:40%;float:left;">
                <a target="_blank" href="https://apps.apple.com/app/id1482362759"><img src="' . $iPhoneAppLink . '"></a>
              </div>
              </div>
              <br><br><br>
              <div style="font-size:1.1em;padding:10px;">Android Users</div>
              <div>
              <div style="width:60%;float:left;">
                <ul>
                  <li>Go to Google Play Store.</li>
                  <li>Search for miniOrange.</li>
                  <li>Download and install <span style="color: #F78701;"><b> Authenticator</b></span> app (<b>NOT miniOrange Authenticator/MOAuth)</b></li>
                </ul>
              </div>
              <div style="width:40%;float:left;">
                <a target="_blank" href="https://play.google.com/store/apps/details?id=com.miniorange.android.authenticator"><img src="' . $androidAppLink . '"></a>
              </div>
              </div>
            </div>
          </div>
        </div>
        <div style="width:50%;float:left;">
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

  $step2 = '<div style="width: 100%;float:left;padding-top: 10px;">
        <div class="mo2f_googleauth-steps"><b>Step 2:</b> Scan the below QR Code from miniOrange Authenticator app.</div>
        <div style="text-align:center">
        <div style="display:inline-block;width:33%">
          <img src="data:image/jpg;base64,' . $qrCode . '">
        </div>
        <!--<div style="vertical-align: top;display: inline-flex;padding: 75px 0px;">
          <p style="margin: auto 10px;">OR</p>
        </div>
        <div style="display:inline-block;width:33%">
          <div class="mo2f_googleauth-secret">
          <span style="padding:10px;">
            <p style="font-size: 10pt;">Use the following secret</p><p>
            </p><p id="googleAuthSecret" style="font-size: 13pt; font-weight: bold"></p>
            <p style="font-size: 9pt;">(Spaces don&#39;t matter)</p><p>

        </p></span></div>
        </div>-->
        </div>
        </div>';

  $step3 = '<div style="width: 100%;float:left;padding-top: 10px;">
        <div class="mo2f_googleauth-steps"><b>Step 3:</b> Enter the Passcode generated by Google Authenticator app.</div>
        </div>';
  return $step1 . $step2;
}
