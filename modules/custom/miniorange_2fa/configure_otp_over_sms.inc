<?php

function mo_auth_configure_otp_over_sms($form, &$form_state)
{
    drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
    drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

    global $base_url, $user;
    $user = user_load($user->uid);

    $query_param = $_GET["q"];
    $url_parts = explode('/',$query_param);

    $authTypeCode = '';
    $messageHeader = '';
    if ( in_array("otp-over-sms", $url_parts ) ) {
        $authTypeCode  = AuthenticationType::$SMS['code'];
        $messageHeader = 'Configure OTP Over SMS';
        $methodName    = 'OTP Over SMS';
    }elseif ( in_array("otp-over-email",$url_parts ) ) {
      $authTypeCode  = AuthenticationType::$OTP_OVER_EMAIL['code'];
      $messageHeader = 'Configure OTP Over Email';
      $methodName    = 'OTP Over Email';
    } elseif ( in_array("otp-over-phone",$url_parts ) ) {
        $authTypeCode  = AuthenticationType::$OTP_OVER_PHONE['code'];
        $messageHeader = 'Configure OTP Over Phone call';
        $methodName    = 'OTP Over Phone call';
    }

    $user_email       = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $customer         = new MiniorangeCustomerProfile();
    $miniorange_user  = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, $authTypeCode);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $mo_note          = t('<ul><li>Customize SMS/Email template.</li> <li>Customize OTP Length and Validity.</li><li>For customization goto <a href="' .$base_url . '/admin/config/people/mo_auth/login_settings">Login Settings</a> tab and navigate to <u>CUSTOMIZE SMS AND EMAIL TEMPLATE</u> section.</li></ul>');
    $form['header']['#markup'] = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">'. $messageHeader .'</div></div>';
    $form['mo_2fa_custom_note'] = array(
      '#markup'=>t('<br><div class="mo2f_highlight_background_note"><strong>You can customize the following things of the '.$methodName.' method:</strong>'. $mo_note .'</div><br>')
    );

    if( $methodName == 'OTP Over Email' ) {
      $form['miniorange_email'] = array(
        '#type' => 'textfield',
        '#title' => t('Verify Your Email*'),
        '#value' => $user_email,
        '#disabled' => TRUE
      );
    } else {
      $form['miniorange_phone'] = array(
        '#type' => 'textfield',
        '#title' => t('Verify Your Phone'),
        '#id' => 'query_phone',
        '#attributes' => array('class' => array('query_phone'), 'pattern' => '[\+][0-9]{1,4}\s?[0-9]{7,12}'),
        '#description' => t('<strong>Note: </strong>Enter your phone number with country code (+1)'),
      );
    }

    $form['verifyphone'] = array(
        '#type' => 'submit',
        '#value' => t('Verify'),
        '#submit' => array(
            'mo_auth_configure_otp_over_sms_submit'
        )
    );

    $form['mo_authTypeCode'] = array(
        '#type' => 'hidden',
        '#value' => $authTypeCode,
    );

    $form['miniorange_saml_customer_setup_resendotp'] = array(
        '#type' => 'submit',
        '#value' => t('Resend OTP'),
        '#submit' => array(
            'mo_auth_configure_otp_over_sms_submit'
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

function mo_auth_configure_otp_over_sms_submit( $form, &$form_state ) {

    $form_state['rebuild'] = TRUE;
    global $base_url, $user;
    $customer          = new MiniorangeCustomerProfile();
    $custID            = $customer->getCustomerID();
    $api_key           = $customer->getAPIKey();
    $user              = user_load( $user->uid );
    $user_email        = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    $methodToConfigure = $form['mo_authTypeCode']['#value'];
    $phone_number      = isset( $form['miniorange_phone']['#value'] ) ? str_replace( ' ', '', $form['miniorange_phone']['#value'] ) : '';

    if( $methodToConfigure === 'EMAIL' ) {
      $email = str_replace(' ', '', $form['miniorange_email']['#value']);
      $success_Message = 'We have sent an OTP to <strong>'.$email.'</strong>. Please enter the OTP to verify your email address.';
      $currentMethod   = "OTP_OVER_EMAIL";
      $params = array('email' => $user_email );
    }elseif( $methodToConfigure === 'PHONE VERIFICATION' ) {
      $success_Message = 'You will get a call on <strong>'.$phone_number.'</strong> shortly, which prompts OTP. Please enter the OTP to verify your phone number.';
      $currentMethod   = "PHONE_VERIFICATION";
      $params = array('phone' => $phone_number );
    }else {
      $success_Message = 'We have sent an OTP to <strong>'.$phone_number.'</strong>. Please enter the OTP to verify your phone number.';
      $currentMethod   = "OTP_OVER_SMS";
      $params = array('phone' => $phone_number );
    }

      $customer_config   = new MiniorangeCustomerSetup($user_email, $phone_number, NULL, NULL);
      $response          = $customer_config->send_otp_token($params, $currentMethod, $custID, $api_key);
      variable_set('mo_auth_customer_admin_phone', $phone_number);
      $send_otp_response = json_decode($response);
      if ( $send_otp_response->status == 'SUCCESS' ) {
          // Store txID.
          variable_set('mo_auth_tx_id', $send_otp_response->txId );
          drupal_set_message(t( $success_Message ) );
          return;
      } elseif ( $send_otp_response->status == 'CURL_ERROR' ) {
          drupal_set_message(t('cURL is not enabled. Please enable cURL'), 'error');
          return;
      } else {
          drupal_set_message(t( $send_otp_response->message ), 'error');
          return;
      }
}

function miniorange_saml_validate_otp_submit( $form, &$form_state ) {
    $otpToken     = trim( $form['miniorange_OTP']['#value'] );
    $phone_number = isset( $form['miniorange_phone']['#value'] ) ? $form['miniorange_phone']['#value'] : '';
    if ( empty($otpToken ) ) {
        drupal_set_message(t('The <b>OTP</b> field is required.'),'error');
        return;
    }
    if (  isset( $form['miniorange_phone']['#value'] ) &&  empty( $phone_number ) ) {
        drupal_set_message(t('Please enter phone number with country code(+1).'),'warning');
        return;
    }

    global $base_url, $user;
    $customer        = new MiniorangeCustomerProfile();
    $cKey            = $customer->getCustomerID();
    $customerApiKey  = $customer->getAPIKey();
    $user            = user_load($user->uid);
    $user_email      = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
    variable_set('mo_phone', $phone_number);
    $transactionId   = variable_get('mo_auth_tx_id');

    $customer_config = new MiniorangeCustomerSetup( $user_email, $phone_number, NULL, NULL );

    $response        = $customer_config->validate_otp_token( $transactionId, $otpToken, $cKey, $customerApiKey );
    $otp_validation  = json_decode( $response );

    if ( $otp_validation->status == 'FAILED' ) {
        drupal_set_message(t("Validation Failed. Please enter the correct OTP."),'error');
        return;
    } elseif ( $otp_validation->status == 'SUCCESS' ) {
        $form_state['rebuild'] = TRUE;
        $methodToConfigure     = $form['mo_authTypeCode']['#value'];
        $user_email            = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

        $authTypeCode          = AuthenticationType::$SMS['code'];
        $success_Message       = 'OTP Over SMS has been configured successfully.';
        if( $methodToConfigure === 'EMAIL' ) {
          $authTypeCode      = AuthenticationType::$OTP_OVER_EMAIL['code'];
          $success_Message   = 'OTP Over Email has been configured successfully.';
        }elseif( $methodToConfigure === 'PHONE VERIFICATION' ) {
          $authTypeCode      = AuthenticationType::$OTP_OVER_PHONE['code'];
          $success_Message   = 'OTP Over Phone Call has been configured successfully.';
        }

        //global $base_url, $user;
        $user = user_load($user->uid);
        $customer         = new MiniorangeCustomerProfile();
        $miniorange_user  = new MiniorangeUser($customer->getCustomerID(), $user_email, $phone_number, NULL, $authTypeCode);
        $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

        $configured_methods = mo_auth_get_configured_methods($user->uid);

        if (!in_array($authTypeCode, $configured_methods)) {
            array_push($user->configured_auth_methods[LANGUAGE_NONE], array(
                'value' => $authTypeCode
            ));
        }

        $user_api_handler = new UsersAPIHandler( $customer->getCustomerID(), $customer->getAPIKey());

        // Updating the authentication method for the user
        $miniorange_user->setAuthType($authTypeCode);
        $response = $user_api_handler->update($miniorange_user);

        if ( $response->status == 'SUCCESS' ) {
            user_save($user);
            drupal_set_message(t($success_Message), 'status');
            drupal_goto('admin/config/people/mo_auth/setup');
            return;
        }
        drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
        watchdog('miniorange_2fa', $response->message);
        drupal_goto('admin/config/people/mo_auth/setup');
    }
}