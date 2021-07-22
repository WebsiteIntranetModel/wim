<?php

/**
 * @file
 * OTP Over SMS and Email(test) functions.
 */

/**
 * Menu callback for testing OTP Over SMS and Email.
 */
function mo_auth_test_otp_over_sms_and_email($form, &$form_state) {
  $form['actions'] = array('#type' => 'actions');
  if (array_key_exists('txId', $form_state['input']) === FALSE) {
    global $base_url, $user;
    $user = user_load($user->uid);
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

    $authTypeCode = '';
    $divMessage = '';
	$messageHeader = '';
    $user_phone = variable_get('mo_phone');

	$authTypeCode = AuthenticationType::$SMS_AND_EMAIL['code'];

    $messageHeader = 'An OTP has been sent to ' . $user_phone . ' and ' . $user_email .'. Please enter it here to complete the test.';

    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL , $user_phone, NULL, $authTypeCode, $user_email);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->challenge($miniorange_user);
    variable_set('mo_auth_tx_id', $response->txId);
    if ($response->status == 'SUCCESS') {
        drupal_set_message(t($messageHeader), 'status');
    }
  }

    $divMessage = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Test OTP Over SMS and Email</div></div>';

    $tx = variable_get('mo_auth_tx_id', '');

	 $form['header']['#markup'] = t($divMessage);

	  $form['#attached']['js'][] = array(
        'data' => array(
          'mo_authentication' => array(
            'txId' => $tx,
            'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
          ),
        ),
        'type' => 'setting',
      );

		$form['mo_auth_otpoversms_and_email_token'] = array (
		'#type' => 'textfield',
		'#attributes' => array (
		  'placeholder' => t('Enter passcode.'),
		  'class' => array (
			'mo2f-textbox',
			'mo2f-textbox-otp'
		  ),
		  'style' => 'width:200px',
		  'autofocus' => 'true'
		)
		);

	   $form['actions'] = array (
		'#type' => 'actions'
	  );

	  $form['actions']['submit'] = array (
		'#type' => 'submit',
		'#value' => t('Verify')
	  );

	  $form['txId'] = array(
        '#type' => 'hidden',
        '#value' => $tx,
      );

	  $form['actions']['cancel'] = array (
		'#markup' => l(t('Cancel Test'), 'admin/config/people/mo_auth/setup'),
		'#suffix' => '</div>'
	  );

	return $form;
 }

/**
 * Form submit handler for otp over sms validation.
 */
function mo_auth_test_otp_over_sms_and_email_submit($form, &$form_state) {

  $form_state['rebuild'] = TRUE;
  global $base_url, $user;

  $token = $form_state['input']['mo_auth_otpoversms_and_email_token'];
  if(empty($token)){
    form_set_error('form', t('The passcode field is required. Please try again.'));
    return;
  }

  $txId = variable_get('mo_auth_tx_id', '');

  $user = user_load($user->uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

  $authTypeCode = AuthenticationType::$SMS['code'];
  $user_phone = variable_get('mo_phone');

  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, $user_phone, $authTypeCode, $user_email);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->validate($miniorange_user, $txId, $token);
  drupal_get_messages();

  // read API response
  if ($response->status == 'SUCCESS') {
    drupal_set_message(t('You have successfully completed the test.'), 'status');
    drupal_goto('admin/config/people/mo_auth/setup');
  } elseif ($response->status == 'FAILED') {
    form_set_error('form', t('The passcode you have entered is incorrect. Please try again.'));
    return;
  } else {
    form_set_error('form', t('An error occured while processing your request. Please try again.'));
    drupal_goto('admin/config/people/mo_auth/setup');
  }
}
