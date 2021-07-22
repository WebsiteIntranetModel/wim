<?php

function mo_auth_configure_otp_over_sms_and_email($form, &$form_state)
{
    drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
    drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

    global $base_url, $user;
    $user = user_load($user->uid);

    $user_email       = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $customer         = new MiniorangeCustomerProfile();
    $miniorange_user  = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$SMS_AND_EMAIL['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $mo_note          = t('<ul><li>Customize Email template.</li><li>Customize SMS template.</li> <li>Customize OTP Length and Validity.</li><li>For customization goto <a href="' .$base_url . '/admin/config/people/mo_auth/login_settings">Login Settings</a> tab and navigate to <u>CUSTOMIZE SMS AND EMAIL TEMPLATE</u> section.</li></ul>');
    $form['header']['#markup'] = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Configure OTP Over SMS And Email</div></div>';
    $form['mo_2fa_custom_note'] = array(
      '#markup'=>t('<br><hr><br><div class="mo2f_highlight_background_note"><strong>You can customize the following things of the OTP OVER SMS AND EMAIL method:</strong>'. $mo_note .'</div><br>')
    );
    $form['miniorange_phone'] = array(
        '#type' => 'textfield',
        '#title' => t('Verify Your Phone'),
        '#id' => 'query_phone',
        '#attributes' => array(
            'class'=>array('query_phone'),
            'pattern' => '[\+][0-9]{1,4}\s?[0-9]{7,12}'
        ),
        '#description' => t('Enter your phone number with country code (+1)'),
    );

    $form['miniorange_email'] = array(
        '#type' => 'textfield',
        '#value' => $user_email,
        '#disabled' => TRUE
    );

	$form['verifyphone'] = array(
        '#type' => 'submit',
        '#value' => t('Verify'),
        '#submit' => array(
            'mo_auth_configure_otp_over_sms_and_email_submit'
        )
    );

    $form['miniorange_saml_customer_setup_resendotp'] = array(
        '#type' => 'submit',
        '#value' => t('Resend OTP'),
        '#submit' => array(
            'miniorange_saml_resend_otp'
        )
    );

    $form['miniorange_OTP'] = array(
        '#type' => 'textfield',
        '#title' => t('OTP')
    );

    $form['miniorange_saml_customer_validate_otp_button'] = array(
        '#type' => 'submit',
        '#value' => t('Validate OTP'),
        '#submit' => array(
            'miniorange_saml_validate_otp_submit'
        )
    );

    $form['actions']['cancel'] = array(
        '#markup' => l(t('Back'), 'admin/config/people/mo_auth/setup')
    );
    return $form;
}

function mo_auth_configure_otp_over_sms_and_email_submit($form, &$form_state)
{
    $form_state['rebuild'] = TRUE;

    $phone_number = $form['miniorange_phone']['#value'];
    $phone_number = str_replace(' ', '', $phone_number);

    if (empty($phone_number)) {
        drupal_set_message(t('Please enter phone number to proceed.'), 'warning');
        return;
    }

    global $base_url, $user;

    $customer = new MiniorangeCustomerProfile();
    $custID   = $customer->getCustomerID();
    $api_key  = $customer->getAPIKey();

    $user            = user_load($user->uid);
    $user_email      = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $currentMethod   = "OTP_OVER_SMS_AND_EMAIL";
    $customer_config = new MiniorangeCustomerSetup($user_email, $phone_number, NULL, NULL);

	$params          = array(
        'phone' => $phone_number,
        'email' => $user_email
    );
	$response          = $customer_config->send_otp_token($params, $currentMethod, $custID, $api_key);
    $send_otp_response = json_decode($response);
    if ($send_otp_response->status == 'SUCCESS') {
        // Store txID.
        variable_set('mo_auth_tx_id', $send_otp_response->txId);
        drupal_set_message(t('We have sent an OTP to @phone and @email. Please enter the OTP to verify your phone number.', array(
            '@phone' => $phone_number,
			'@email' => $user_email
        )));
    } elseif ($send_otp_response->status == 'CURL_ERROR') {
        drupal_set_message(t('cURL is not enabled. Please enable cURL'), 'error');
    } else {
        drupal_set_message(t($send_otp_response->message), 'error');
    }

}

function miniorange_saml_resend_otp($form, &$form_state)
{
    $form_state['rebuild'] = TRUE;

    if (empty($form['miniorange_phone']['#value'])) {
        drupal_set_message(t('Please enter phone number to proceed.'), 'warning');
        return;
    }

    global $base_url, $user;

    $customer = new MiniorangeCustomerProfile();
    $custID   = $customer->getCustomerID();
    $api_key  = $customer->getAPIKey();

    $user            = user_load($user->uid);
    $user_email      = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $phone_number    = $form['miniorange_phone']['#value'];
    $currentMethod   = "OTP_OVER_SMS_AND_EMAIL";
    $customer_config = new MiniorangeCustomerSetup($user_email, $phone_number, NULL, NULL);

    $params          = array(
        'phone' => $phone_number,
        'email' => $user_email
    );

    $response          = $customer_config->send_otp_token($params, $currentMethod, $custID, $api_key);
    $send_otp_response = json_decode($response);
    if ($send_otp_response->status == 'SUCCESS') {
        // Store txID.
        variable_set('mo_auth_tx_id', $send_otp_response->txId);
        drupal_set_message(t('We have sent an OTP to @phone. Please enter the OTP to verify your phone number.', array(
            '@phone' => $phone_number
        )));
    } elseif ($send_otp_response->status == 'CURL_ERROR') {
        drupal_set_message(t('cURL is not enabled. Please enable cURL'), 'error');
    } else {
        drupal_set_message(t($send_otp_response->message), 'error');
    }
}

function miniorange_saml_validate_otp_submit($form, &$form_state)
{

    global $base_url, $user;

    if (empty($form['miniorange_phone']['#value'])) {
        drupal_set_message(t('Please enter phone number to proceed.'), 'warning');
        return;
    }
    elseif (empty($form['miniorange_OTP']['#value'])) {
        drupal_set_message(t('Please enter otp to proceed.'), 'warning');
        return;
    }

    $customer       = new MiniorangeCustomerProfile();
    $cKey           = $customer->getCustomerID();
    $customerApiKey = $customer->getAPIKey();
    $otpToken       = $form['miniorange_OTP']['#value'];
    $user           = user_load($user->uid);
    $user_email     = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $phone_number   = $form['miniorange_phone']['#value'];
    variable_set('mo_phone', $phone_number);
    $transactionId = variable_get('mo_auth_tx_id');

    $customer_config = new MiniorangeCustomerSetup($user_email, $phone_number, NULL, NULL);

    $response       = $customer_config->validate_otp_token($transactionId, $otpToken, $cKey, $customerApiKey);
    $otp_validation = json_decode($response);
    $txId           = $otp_validation->txId;

    if ($otp_validation->status == 'FAILED') {
        drupal_set_message(t("Validation Failed. Please enter the correct OTP."),'error');
    } else if ($otp_validation->status == 'SUCCESS') {

        $form_state['rebuild'] = TRUE;
        $authTypeCode          = AuthenticationType::$SMS_AND_EMAIL['code'];
        global $base_url, $user;
        $user = user_load($user->uid);

        $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

        $customer         = new MiniorangeCustomerProfile();
        $miniorange_user  = new MiniorangeUser($customer->getCustomerID(), $user_email, $phone_number, NULL, AuthenticationType::$SMS_AND_EMAIL['code']);
        $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

        $configured_methods = mo_auth_get_configured_methods($user->uid);

        if (!in_array(AuthenticationType::$SMS_AND_EMAIL['code'], $configured_methods)) {
            array_push($user->configured_auth_methods[LANGUAGE_NONE], array(
                'value' => AuthenticationType::$SMS_AND_EMAIL['code']
            ));
        }

        $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

        // Updating the authentication method for the user
        $miniorange_user->setAuthType($authTypeCode);
        $response = $user_api_handler->update($miniorange_user);

        if ($response->status == 'SUCCESS') {
            user_save($user);
            if ($authTypeCode == AuthenticationType::$SMS_AND_EMAIL['code']) {
                drupal_set_message(t('OTP Over SMS and Email has been configured successfully.'), 'status');
            }

            drupal_goto('admin/config/people/mo_auth/setup');
        }
        return;
        drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
        drupal_goto('admin/config/people/mo_auth/setup');
    }
}
