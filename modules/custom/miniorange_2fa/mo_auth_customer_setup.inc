<?php
/**
 * @file
 * Contains form for customer setup.
 */

/**
 * Customer setup form().
 */

function mo_auth_customer_setup($form, &$form_state) {
    global $user;
    $user_obj = user_load($user->uid);
    $current_status = variable_get('mo_auth_status', '');

    drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
    drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

    if ($current_status == 'VALIDATE_OTP') {
        $form['header_top_style_2'] = array(
            '#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container">'
        );
        $form['mo_auth_customer_otp_token'] = array (
            '#type' => 'textfield',
            '#title' => t('Please enter the OTP you received<span style="color: red">*</span>'),
            '#attributes' => array(
                'autofocus' => 'true'
            ),
        );
        $form['mo_auth_customer_validate_otp_button'] = array (
            '#type' => 'submit',
            '#value' => t('Validate OTP'),
            '#submit' => array ('mo_auth_validate_otp_submit'),
        );
        $form['mo_auth_customer_setup_resendotp'] = array (
            '#type' => 'submit',
            '#value' => t('Resend OTP'),
            '#submit' => array ('mo_auth_resend_otp',),
        );
        $form['mo_auth_customer_setup_back'] = array (
            '#type' => 'submit',
            '#value' => t('Back'),
            '#submit' => array ('mo_auth_back')
        );

        $form['markup_idp_attr_header_top_div_close'] = array(
            '#markup' => '<br><br><br><br><br><br><br><br><br><br><br><br></div>',
        );

        MoAuthUtilities::addSupportForm($form, $form_state);

        return $form;
    } elseif ($current_status == 'PLUGIN_CONFIGURATION') {
        // Show customer configuration here.
        $user_email = $user_obj->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
        $customer = new MiniorangeCustomerProfile();
        $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
        $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, '', '', '');

        $response = $user_api_handler->get($miniorange_user);

        $authType = !is_null($response)?(AuthenticationType::getAuthType($response->authType)):NULL;

        $form['header_top_style_2'] = array(
            '#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container">'
        );

        $form['markup_saml_idp_regsitration_message'] = array(
            '#markup' => '<div style="display:block;margin-top:10px;text-align: center;font-size: 15px;color:rgba(0, 128, 0, 0.80);background-color:rgba(0, 255, 0, 0.15);padding:5px;">
                        Thank you for registering with miniOrange
                        </div></br>'
        );

        $header = array (
            'attribute' => array (
                'data' => t('Attribute')
            ),
            'value' => array (
                'data' => t('Value')
            )
        );

        $options = array ();
        $options[0] = array (
            'attribute' => '2 Factor Registered Email',
            'value' => variable_get('mo_auth_customer_admin_email', '')
        );
        $options[1] = array (
            'attribute' => 'Activated 2nd Factor',
            'value' => $authType['name']
        );
        $options[2] = array (
            'attribute' => 'Xecurify Registered Email',
            'value' => $user_email
        );
        $options[3] = array (
            'attribute' => 'Customer ID',
            'value' => variable_get('mo_auth_customer_id', '')
        );
        $options[4] = array (
            'attribute' => 'API Key',
            'value' => variable_get('mo_auth_customer_api_key', '')
        );
        $options[5] = array (
            'attribute' => 'Token Key',
            'value' => variable_get('mo_auth_customer_token_key', '')
        );
        $options[6] = array (
            'attribute' => 'App Secret',
            'value' => variable_get('mo_auth_customer_app_secret', '')
        );

        $form['fieldset']['customerinfo'] = array (
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $options
        );

        $license_header = array (
            'attribute' => array (
                'data' => t('Attribute')
            ),
            'value' => array (
                'data' => t('Value')
            )
        );

      $license_options = array ();
        $license_options[0] = array (
            'attribute' => 'License Type',
            'value' => variable_get('mo_auth_2fa_license_type', 'DEMO')
        );
        $license_options[1] = array (
            'attribute' => 'License Plan',
            'value' => variable_get('mo_auth_2fa_license_plan', 'DEMO')
        );
        $license_options[2] = array (
            'attribute' => 'No. of Users',
            'value' => variable_get('mo_auth_2fa_license_no_of_users', 1)
        );

        $license_options[3] = array (
          'attribute' => 'SMS Remaining',
          'value' => variable_get('mo_auth_2fa_sms_remaining', '-')
        );

        $license_options[4] = array (
          'attribute' => 'Email Remaining',
          'value' => variable_get('mo_auth_2fa_email_remaining', '-')
        );

        $license_options[5] = array (
          'attribute' => 'License Expiry',
          'value' => variable_get('mo_auth_2fa_license_expiry', '-')
        );

        $license_options[6] = array (
          'attribute' => 'Support Expiry',
          'value' => variable_get('mo_auth_2fa_support_expiry', '-')
        );

        $form['fieldset']['customer-license'] = array (
            '#theme' => 'table',
            '#header' => $license_header,
            '#rows' => $license_options,
            '#prefix' => '<div style="margin-top: 20px;"><h4>Your license info: </h4></div>'
        );
        $form['fecth_customer_license'] = array (
            '#type' => 'submit',
            '#value' => t('Check License'),
            '#submit' => array (
                'mo_auth_fetch_customer_license'
            ),
        );

        $form['remove_customer_account'] = array (
          '#type' => 'submit',
          '#value' => t('Remove Account'),
          '#submit' => array (
            'mo_auth_remove_customer_account'
          ),
          '#attributes' => array('style' => 'margin-left: 10%;'),
          '#suffix' => '</div>',
        );

        MoAuthUtilities::addSupportForm($form, $form_state);

        return $form;
    }

    $form['header_top_style_2'] = array(
        '#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container">');

    $form['markup_14'] = array (
        '#markup' => '<h3>Register/Login with miniOrange</br></br><hr></h3>'
    );

    $form['markup_15'] = array (
        '#markup' => '<div class="mo2f_highlight_background_note">Just complete the short registration below to configure the Two-Factor Module.
                        Please enter a valid email ID that you have access to.
                        You will be able to move forward after verifying an OTP that we will send to this email.
                      </div></br>'
    );


    $form['mo_auth_customer_setup_username'] = array (
        '#type' => 'textfield',
        '#title' => t('Email<span class = "mo2f_red_color_star">*</span>'),
        '#attributes' => array (
            'autofocus' => 'true'
        ),
    );

    $form['mo_auth_customer_setup_phone'] = array (
        '#type' => 'textfield',
        '#title' => t('Phone'),
        '#id' => 'query_phone',
        '#attributes' => array('class'=>array('query_phone'),),
        '#description' => t('<strong>Note:</strong> Enter your phone number with country code (eg. +1xxxxxx )'),
    );

    $form['mo_auth_customer_setup_password'] = array (
        '#type' => 'password_confirm',
        '#description' => t('<strong>Note:</strong> Enter your password with minimum length of 6.')
    );

    $form['mo_auth_customer_setup_button'] = array (
        '#type' => 'submit',
        '#value' => t('Submit'),
        '#submit' => array ('mo_auth_customer_setup_submit'),
    );

    $form['markup_idp_attr_header_top_support_5'] = array(
        '#markup' => '</div>',
    );

    MoAuthUtilities::addSupportForm($form, $form_state);

    return $form;
}

/**
 * Validate OTP.
 */
function mo_auth_validate_otp_submit(&$form, $form_state) {
    global $user;
    $user = user_load($user->uid);
    $otp_token = trim($form['mo_auth_customer_otp_token']['#value']);

    if(empty($otp_token)){
        drupal_set_message(t('The <b><u>OTP</u></b> field is mandatory.'), 'error');
        return;
    }
    $username = variable_get('mo_auth_customer_admin_email', NULL);
    $phone = variable_get('mo_auth_customer_admin_phone', NULL);
    $txId = variable_get('mo_auth_tx_id', NULL);
    $customerSetup = new MiniorangeCustomerSetup($username, $phone, NULL, $otp_token);

    // Validate OTP.
    $validate_otp_response = json_decode($customerSetup->validate_otp_token($txId, $otp_token, MoAuthConstants::$DEFAULT_CUSTOMER_ID, MoAuthConstants::$DEFAULT_CUSTOMER_API_KEY ));


    if ($validate_otp_response->status == 'SUCCESS') {

        // OTP Validated. Show Configuration page.
        variable_del('mo_auth_tx_id');

        // OTP Validated. Create customer.
        $password = variable_get('mo_auth_customer_admin_password', '');
        $customer_config = new MiniorangeCustomerSetup($username, $phone, $password, NULL);
        $create_customer_response = $customer_config->createCustomer();
        if ($create_customer_response->status == 'SUCCESS') {
            // Customer created.
            mo_auth_save_customer($user, $create_customer_response, $username, $phone);
            $current_status = 'PLUGIN_CONFIGURATION';
            variable_set('mo_auth_status', $current_status);


            drupal_set_message(t('Customer account created. Email Verification has been set as your default 2nd factor method.'));
            drupal_goto('admin/config/people/mo_auth');
        }
        else if(trim($create_customer_response->message) == 'Email is not enterprise email.')
        {
            variable_del('mo_auth_status');
            drupal_set_message(t('There was an error creating an account for you.<br> You may have entered an invalid Email-Id
            <strong>(We discourage the use of disposable emails) </strong>
            <br>Please try again with a valid email.'), 'error');
        }
        else {
            watchdog('miniorange_2fa', $create_customer_response->message);
            variable_del('mo_auth_status');
            drupal_set_message(t('An error occured while creating your account. Please try again or contact us at <a href="mailto:info@xecurify.com">info@xecurify.com</a>.'), 'error');
        }
    } else {
        drupal_set_message(t('The OTP you have entered is incorrect. Please try again.'), 'error');
    }
}

/**
 * Resend OTP.
 */
function mo_auth_resend_otp(&$form, $form_state) {

    variable_del('mo_auth_tx_id');
    $username = variable_get('mo_auth_customer_admin_email', NULL);
    $phone = variable_get('mo_auth_customer_admin_phone', NULL);
    $customer_config = new MiniorangeCustomerSetup($username, $phone, NULL, NULL);
    $send_otp_response = $customer_config->sendOtp();
    if ($send_otp_response->status == 'SUCCESS') {
        // Store txID.
        variable_set('mo_auth_tx_id', $send_otp_response->txId);
        $current_status = 'VALIDATE_OTP';
        variable_set('mo_auth_status', $current_status);
        drupal_set_message(t('We have resend an OTP to @username. Please enter the OTP to verify your email.', array (
            '@username' => $username
        )));
    }else{
        variable_del('mo_auth_status');
        drupal_set_message(t('There was an error sending OTP to @username. Please try after some time or contact us at <a href="mailto:info@xecurify.com">info@xecurify.com</a>.', array (
                '@username' => $username
            )));
    }
}

/**
 * Handle submit for customer setup.
 */
function mo_auth_customer_setup_submit(&$form, $form_state) {
    global $user;
    $user = user_load($user->uid);
    $username = $form['mo_auth_customer_setup_username']['#value'];
    $phone = $form['mo_auth_customer_setup_phone']['#value'];
    $phone = str_replace(' ', '', $phone);
    $password = trim($form['mo_auth_customer_setup_password']['#value']['pass1']);

    if(empty($username)||empty($password)){
        drupal_set_message(t('The <b><u>Email Address</u></b> and <b><u>Password</u></b> fields are mandatory.'), 'error');
        return;
    }
    if (!valid_email_address($username)) {
        drupal_set_message(t('The email address <b><u>' . $username . '</u></b> is not valid.'), 'error');
        return;
    }
    if (strlen($password)<6) {
        drupal_set_message(t('The length of the password field is less than 6. Please try again.'), 'error');
        return;
    }

    $customer_config = new MiniorangeCustomerSetup($username, $phone, $password, NULL);
    $check_customer_response = $customer_config->checkCustomer();

    if (isset($check_customer_response->status) && $check_customer_response->status == 'CUSTOMER_NOT_FOUND') {
        // Create customer.
        // Store email and phone.
        variable_set('mo_auth_customer_admin_email', $username);
        $send_otp_response = $customer_config->sendOtp();

        if ($send_otp_response->status == 'SUCCESS') {
            // Store txID.
            variable_set('mo_auth_tx_id', $send_otp_response->txId);
            $current_status = 'VALIDATE_OTP';
            variable_set('mo_auth_status', $current_status);
            drupal_set_message(t('We have sent an OTP to @username. Please enter the OTP to verify your email.', array (
                '@username' => $username
            )));
        }else {
            variable_del('mo_auth_status');
            drupal_set_message(t('There was an error sending OTP to @username. Please try after some time or contact us at <a href="mailto:info@xecurify.com">info@xecurify.com</a>.', array (
                '@username' => $username
            )));
        }


    } elseif (isset($check_customer_response->status) && $check_customer_response->status == 'CURL_ERROR') {
        drupal_set_message(t('cURL is not enabled. Please enable cURL'), 'error');
    } elseif (isset($check_customer_response->status) && $check_customer_response->status == 'SUCCESS') {
        // Customer exists. Retrieve keys.
        $customer_keys_response = $customer_config->getCustomerKeys();
        if (json_last_error() == JSON_ERROR_NONE) {
             mo_auth_save_customer($user, $customer_keys_response, $username, $phone);
            variable_set('mo_auth_customer_admin_email', $username);
            variable_set('mo_auth_customer_admin_phone', $phone);
            variable_set('mo_auth_customer_admin_password', $password);
            drupal_set_message(t('Your account has been retrieved successfully. Email Verification has been set as your default 2nd factor method.'));
            drupal_goto('admin/config/people/mo_auth');
        } else {
          watchdog('miniorange_2fa', $check_customer_response->message);
          drupal_set_message(t('Invalid username or password.'), 'error');
        }
    } else {
         drupal_set_message(t('An error has been occured. Please try after some time or contact us at <a href="mailto:info@xecurify.com">info@xecurify.com</a>.'), 'error');
    }

}

/**
 * Handle back button submit for customer setup.
 */
function mo_auth_back($form, &$form_state) {
    $current_status = 'CUSTOMER_SETUP';
    variable_set('mo_auth_status', $current_status);
    variable_del('mo_auth_customer_admin_email');
    variable_del('mo_auth_customer_admin_phone');
    variable_del('mo_auth_tx_id');
    drupal_set_message(t('Register/Login with your miniOrange Account'));
}
function mo_auth_save_customer($user, $json, $username, $phone) {
    variable_set('mo_auth_customer_id', $json->id);
    variable_set('mo_auth_customer_token_key', $json->token);
    variable_set('mo_auth_customer_admin_email', $username);
    variable_set('mo_auth_customer_admin_phone', $phone);
    variable_set('mo_auth_customer_api_key', $json->apiKey);
    variable_set('mo_auth_customer_app_secret', $json->appSecret);
    isset($json->appSecret)?(variable_set('mo_auth_customer_app_secret', $json->appSecret)):NULL;
    $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'] = $username;
    $user->configured_auth_methods[LANGUAGE_NONE][0]['value'] = array (
        AuthenticationType::$EMAIL_VERIFICATION['code']
    );
    $current_status = 'PLUGIN_CONFIGURATION';
    variable_set('mo_auth_status', $current_status);
    user_save($user);

    // Update the customer second factor to OOB Email in miniOrange
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $username, '', '', AuthenticationType::$EMAIL_VERIFICATION['code']);
    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $user_api_handler->update($miniorange_user);

    $license_response = $user_api_handler->fetchLicense();

    $license_type = 'DEMO';
    $license_plan = 'DEMO';
    $no_of_users = 1;
    if ( $license_response->status == 'SUCCESS' ) {

        $license_type = $license_response->licenseType;
        if ( $license_type == 'DRUPAL_2FA_PLUGIN' ) {
            $license_plan = $license_response->licensePlan;
        }
        $no_of_users = $license_response->noOfUsers;
    }
    variable_set('mo_auth_2fa_license_type', $license_type);
    variable_set('mo_auth_2fa_license_plan', $license_plan);
    variable_set('mo_auth_2fa_license_no_of_users', $no_of_users);
    variable_set('mo_auth_2fa_sms_remaining', isset( $license_response->smsRemaining ) ? $license_response->smsRemaining : '');
    variable_set('mo_auth_2fa_email_remaining', isset( $license_response->emailRemaining ) ? $license_response->emailRemaining : '');
    variable_set('mo_auth_2fa_license_expiry', isset( $license_response->licenseExpiry ) ? date('Y-M-d H:i:s', strtotime( $license_response->licenseExpiry ) ) : '' );
    variable_set('mo_auth_2fa_support_expiry', isset( $license_response->supportExpiry ) ? date('Y-M-d H:i:s', strtotime( $license_response->supportExpiry ) ) : '' );

    variable_set('mo_auth_enable_two_factor', TRUE);
    variable_set('mo_auth_enforce_inline_registration', FALSE);
}

function mo_auth_fetch_customer_license($form, &$form_state) {
    $customer = new MiniorangeCustomerProfile();
    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $license_response = $user_api_handler->fetchLicense();

    if ( $license_response->status == 'SUCCESS' ) {
        $license_type = $license_response->licenseType;
        $license_plan = 'DEMO';
        if ( $license_type == 'DRUPAL_2FA_PLUGIN' ) {
            $license_plan = $license_response->licensePlan;
        }
        $no_of_users = $license_response->noOfUsers;
        variable_set('mo_auth_2fa_license_type', $license_type);
        variable_set('mo_auth_2fa_license_plan', $license_plan);
        variable_set('mo_auth_2fa_license_no_of_users', $no_of_users);
      variable_set('mo_auth_2fa_sms_remaining', isset( $license_response->smsRemaining ) ? $license_response->smsRemaining : '');
      variable_set('mo_auth_2fa_email_remaining', isset( $license_response->emailRemaining ) ? $license_response->emailRemaining : '');
      variable_set('mo_auth_2fa_license_expiry', isset( $license_response->licenseExpiry ) ? date('Y-M-d H:i:s', strtotime( $license_response->licenseExpiry ) ) : '' );
      variable_set('mo_auth_2fa_support_expiry', isset( $license_response->supportExpiry ) ? date('Y-M-d H:i:s', strtotime( $license_response->supportExpiry ) ) : '' );
    }
    drupal_set_message(t('License fetched successfully.'), 'status');
}

/**
 * Send support query.
 */
function miniorange_2fa_send_query($form, &$form_state)
{
    $email = $form['miniorange_saml_email_address_support']['#value'];
    $phone = $form['miniorange_saml_phone_number_support']['#value'];
    $query = $form['miniorange_saml_support_query_support']['#value'];
    MoAuthUtilities::send_support_query($email, $phone, $query);
}

function mo_auth_remove_customer_account()
{
  variable_del('mo_auth_customer_id');
  variable_del('mo_auth_customer_token_key');
  variable_del('mo_auth_customer_admin_email');
  variable_del('mo_auth_customer_admin_phone');
  variable_del('mo_auth_customer_api_key');
  variable_del('mo_auth_customer_app_secret');
  variable_del('mo_auth_customer_app_secret');
  variable_del('mo_auth_customer_admin_password');

  variable_set('mo_auth_status', '');

  drupal_set_message(t('Account removed successfully.'));
}
