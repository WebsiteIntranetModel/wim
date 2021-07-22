<?php

/**
 * @file
 * Email verification functions.
 */

/**
 * Menu callback for email verification.
 */
function mo_auth_test_qrcode_authentication($form, &$form_state) {
  $form['actions'] = array('#type' => 'actions');
  if (array_key_exists('txId', $form_state['input']) === FALSE) {
    global $base_url, $user;
    $user = user_load($user->uid);
    $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$QR_CODE['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->challenge($miniorange_user);
    if ($response->status == 'SUCCESS') {
      $message = t('Please scan the below QR Code from miniOrange Authenticator app.');
      drupal_set_message($message, 'status');

      $form['#attached']['js'][] = array(
        'data' => array(
          'mo_authentication' => array(
            'txId' => $response->txId,
            'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
          ),
        ),
        'type' => 'setting',
      );

      $form['header']['#markup'] = t('<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Test QR Code Authentication</div></div><div class="mo2f-text-center"><div class="mo2f-info">Please scan the below QR Code with miniOrange Authenticator app to authenticate yourself.</div>');
      $form['loader']['#markup'] = '<div class="mo2f-text-center"><img src="data:image/jpg;base64,' . $response->qrCode . '"></div></div>';

      $form['txId'] = array(
        '#type' => 'hidden',
        '#value' => $response->txId,
       );

      $form['actions']['cancel'] = array(
        '#markup' => l(t('Cancel Test'), 'admin/config/people/mo_auth/setup'),
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
function mo_auth_test_qrcode_authentication_submit($form, &$form_state) {
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
  } elseif ($response->status == 'FAILED') {
    drupal_set_message(t('Authentication failed.'), 'error');
    drupal_goto('admin/config/people/mo_auth/setup');
  } else {
    drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
    watchdog('miniorange_2fa', $response->message);
    drupal_goto('admin/config/people/mo_auth/setup');
  }
}
