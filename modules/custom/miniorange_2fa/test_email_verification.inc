<?php

/**
 * @file
 * Email verification functions.
 */

/**
 * Menu callback for email verification.
 */
function mo_auth_test_email_verification($form, &$form_state) {
  $form['actions'] = array('#type' => 'actions');
  if (array_key_exists('txId', $form_state['input']) === FALSE) {
    global $base_url, $user;
    $user = user_load($user->uid);
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

	/* To check which method (Soft Token, Google Authenticator') is being tested by user
     * $authTypeCode:- Code of the authentication Type
     * $messageHeader:- Info related to auth Type in the page
     */
    $query_param = $_GET["q"];
    $url_parts = explode('/',$query_param);

    $authTypeCode = '';
    $messageHeader = '';
	$divMessage = '';
    if (in_array("push-notifications",$url_parts)) {
	  $authTypeCode = AuthenticationType::$PUSH_NOTIFICATIONS['code'];
	  $messageHeader = 'A push notification has been sent to your miniOrange Authenticator App.';
	  $divMessage = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Test Push Notification</div></div><div class="mo2f-text-center"><div class="mo2f-info">A push notification has been sent to your miniOrange Authenticator App.</div><div class="mo2f-info mo2f-text-center">We are waiting for your approval...</div>';
    } else {
	  $authTypeCode = AuthenticationType::$EMAIL_VERIFICATION['code'];
	  $hidden_email = MoAuthUtilities::getHiddenEmail($user_email);
      $messageHeader = 'A verification email is sent to <b>' . $hidden_email . '</b>. Please click on accept link to verify your email.';
      $divMessage = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Test Email Verification</div></div><div class="mo2f-text-center"><div class="mo2f-info">A verification email is sent to your registered email.</div><div class="mo2f-info mo2f-text-center">We are waiting for your approval...</div>';
    }

    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, $authTypeCode);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->challenge($miniorange_user);

    if ($response->status == 'SUCCESS') {
      //$hidden_email = MoAuthUtilities::getHiddenEmail($user_email);
      drupal_set_message(t($messageHeader), 'status');

      $form['#attached']['js'][] = array(
        'data' => array(
          'mo_authentication' => array(
            'txId' => $response->txId,
            'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
          ),
        ),
        'type' => 'setting',
      );

      $form['header']['#markup'] = t($divMessage);
      $image_path = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/ajax-loader-login.gif');
      $form['loader']['#markup'] = '<div class="mo2f-text-center"><img src="' . $image_path . '" /></div>';

      $form['txId'] = array(
        '#type' => 'hidden',
        '#value' => $response->txId,
      );

      $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel Test'), 'admin/config/people/mo_auth/setup'),
        '#suffix' => '</div>',
      );

    } else {
      drupal_set_message(t('An error occured while processing your request. Please Try again.'), 'error');
      watchdog('miniorange_2fa', $response->message);
      drupal_goto('admin/config/people/mo_auth/setup');
    }
  }
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Test'),
    '#attributes' => array('class' => array('element-invisible')),
  );
  return $form;
}

/**
 * Form submit handler for email verify.
 */
function mo_auth_test_email_verification_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $txId = $form_state['input']['txId'];
  $customer = new MiniorangeCustomerProfile();
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->getAuthStatus($txId);

  // Clear all the messages
  drupal_get_messages();

  // read API response
  if ($response->status == 'SUCCESS') {
    drupal_set_message(t('You have successfully completed the test.'), 'status');
    drupal_goto('admin/config/people/mo_auth/setup');
  } elseif ($response->status == 'DENIED') {
    drupal_set_message(t('You have denied the transaction.'), 'error');
    drupal_goto('admin/config/people/mo_auth/setup');
  } else {
    drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
    watchdog('miniorange_2fa', $response->message);
    drupal_goto('admin/config/people/mo_auth/setup');
  }
}
