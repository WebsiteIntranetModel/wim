<?php
/**
 * @file
 *  This is used to authenticate user during login.
 */
function mo_auth_authenticate_user($form, &$form_state, $user) {
  global $base_url;
  if (user_is_logged_in()) {
    drupal_goto('user');
    exit;
  }
  $form_state['uid'] = $user->uid;
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  if (isset($_SESSION['mo_auth']['status']) && $_SESSION['mo_auth']['status'] === '1ST_FACTOR_AUTHENTICATED') {
    $challenge_response = $_SESSION['mo_auth']['mo_challenge_response'];
    $form['actions'] = array('#type' => 'actions');
    if (! empty($challenge_response->authType)) {
      $form['authType'] = array(
        '#type' => 'hidden',
        '#value' => $challenge_response->authType,
      );
      $authType = AuthenticationType::getAuthType($challenge_response->authType);
      $form = mo_auth_build_form($form, $user, $base_url, $authType, $challenge_response);
      unset($form['mo_message']);
    } else {
      $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#attributes' => array('class' => array('element-invisible')),
      );
    }
    return $form;
  }
  drupal_goto('user');
  exit;
}

function mo_auth_authenticate_user_validate($form, &$form_state) {
  // $user_api_response = $_SESSION['mo_auth']['user'];
  $challenge_response = $_SESSION['mo_auth']['mo_challenge_response'];
  if ($challenge_response->authType == AuthenticationType::$GOOGLE_AUTHENTICATOR['code'] || $challenge_response->authType == AuthenticationType::$SOFT_TOKEN['code']) {
  	$token = $form_state['input']['token'];
    if (empty($token)) {
      $new_form = mo_auth_build_form_with_error_message($form_state,TRUE);
      form_set_error('form', t($new_form['mo_message']));
      unset($new_form['mo_message']);
    }
  	elseif ( strlen($token) != 6 || ! preg_match('/[0-9]/', $token)) {
  	  $new_form = mo_auth_build_form_with_error_message($form_state);
  	  form_set_error('form', t($new_form['mo_message']));
  	  unset($new_form['mo_message']);
  	}
  }
  elseif($challenge_response->authType == AuthenticationType::$SMS['code'] || $challenge_response->authType == AuthenticationType::$SMS_AND_EMAIL['code'] || $challenge_response->authType == AuthenticationType::$OTP_OVER_PHONE['code'] || $challenge_response->authType == AuthenticationType::$OTP_OVER_EMAIL['code'] ) {
	  $token = $form_state['input']['token'];
	  if (empty($token)) {
      $new_form = mo_auth_build_form_with_error_message($form_state,TRUE);
      form_set_error('form', t($new_form['mo_message']));
      unset($new_form['mo_message']);
    }
	  elseif ( ! preg_match('/[0-9]/', $token)) {
		  $new_form = mo_auth_build_form_with_error_message($form_state);
		  form_set_error('form', t($new_form['mo_message']));
		  unset($new_form['mo_message']);
  	}
  }
  elseif ($challenge_response->authType == AuthenticationType::$KBA['code']) {
  	$i=0;
  	foreach ($challenge_response->questions as $question){
  	  $i++;
  	  $ques = $form_state['input']['mo2f_kbaquestion' . $i];
  	  if ($ques != $question->question) {
  	  	form_set_error('form', t('An error occured while processing your request.'));
  	  	drupal_goto("user");
  	  	break;
  	  }
  	}
  }
}

function mo_auth_authenticate_user_submit($form, &$form_state) {
  global $base_url;
  $form_state['rebuild'] = TRUE;
  $uid = $form_state['uid'];
  $user = user_load($uid);
  $input = isset($form_state['input']) && is_array($form_state['input'])?$form_state['input']:array();

  if (array_key_exists('mo_auth_remember_device', $input) && !is_null($input['mo_auth_remember_device'])){
    if ( $input['mo_auth_remember_device'] == 1 ) {
      if (isset($_SESSION['mo2f_rba_status'])) {
        $rba_register_status = $_SESSION['mo2f_rba_status']['status'];
        $rba_session_uuid = $_SESSION['mo2f_rba_status']['sessionUuid'];
        if ($rba_register_status == 'WAIT_FOR_INPUT') {
          $mo_auth_rba = new MoAuthRBA();
          $mo_auth_rba->mo2f_register_rba_profile($user->miniorange_registered_email[LANGUAGE_NONE][0]['value'], $rba_session_uuid);
        }
      }
    }
  }


  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  // $user_api_response = $_SESSION['mo_auth']['user'];
  $challenge_response = $_SESSION['mo_auth']['mo_challenge_response'];
  $authType = AuthenticationType::getAuthType($challenge_response->authType);
  if ($authType['oob'] === FALSE) {
  	$token = '';
  	if (array_key_exists('token', $form_state['input']))
  	  $token = $form_state['input']['token'];
    $txId = '';
    $kba = array();
    if ($authType['challenge'] === TRUE) {
      $txId = $challenge_response->txId;
      if ($challenge_response->authType == AuthenticationType::$KBA['code']) {
      	$count = count($challenge_response->questions);
      	for ($i = 1; $i<=$count; $i++) {
      	  $ques = $form_state['input']['mo2f_kbaquestion' . $i];
      	  $ans = $form_state['input']['mo2f_kbaanswer' . $i];
      	  $qa = array(
      	    "question" => $ques,
      	    "answer" => $ans,
      	  );
      	  array_push($kba, $qa);
      	}
      }
    }

    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, NULL);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->validate($miniorange_user, $txId, $token, $kba);
  } else {
    $txId = $form_state['input']['txId'];
    $customer = new MiniorangeCustomerProfile();
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->getAuthStatus($txId);
  }

  // read API response
  if ( isset( $response ) ){
    if ( $response->status == 'SUCCESS' ) {
      $change2FARequest = array_key_exists('mo_auth_change_2fa',$input) && !is_null($input['mo_auth_change_2fa'])?TRUE:FALSE;
      user_login_submit(array(), $form_state);
      unset( $_SESSION['mo_auth'] );
      $mo_redirect_after_login = variable_get('mo_auth_redirect_after_login', '');
      // if change of 2fa method requested then set $mo_redirect_url to inline url
      // mark that user has requested to change his method
      if( $change2FARequest ){
        $uid = $form_state['uid'];
        $form_state['redirect'] = 'login/user/'.$uid.'/register';
        $url = $form_state['redirect'];
        drupal_goto($url,array('query'=>array('mo2faresetrequest'=>'reset')));
      }
      if( isset( $mo_redirect_after_login ) && !empty( $mo_redirect_after_login ) ) {
        drupal_goto( $mo_redirect_after_login );
      }
    } elseif ( $response->status == 'DENIED' ) {
      form_set_error('form', t('Authentication denied.'));
      unset( $_SESSION['mo_auth'] );
      drupal_goto('user');
    } elseif ( $response->status == 'FAILED' ) {
      $new_form = mo_auth_build_form_with_error_message($form_state);
      form_set_error('form', t( $new_form['mo_message'] ) );
      unset( $new_form['mo_message'] );
    }
  } else {
    form_set_error('form', t('An error occured while processing your request. Please try again.'));
    unset($_SESSION['mo_auth']);
    drupal_goto('user');
  }
}

function mo_auth_build_form($form, $user, $base_url, $authType, $challenge_response, $success_form = TRUE, $empty_token = FALSE) {
  $form['main-header']['#markup'] = t('<style>#messages div.messages{visibility:hidden;}</style>');
  $form['header']['#markup'] = t('<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Verify your identity</div>
                <div class="mo2f-modal-container">');
  $submit_attributes = array();
  $user_configured_methods_array = $user->configured_auth_methods['und'];
  $form = mo_auth_build_form_content($form,$user, $base_url, $authType, $challenge_response, $success_form, $empty_token);
  if(isset($form['submit_attributes'])) {
  $submit_attributes = $form['submit_attributes']; }
  unset($form['submit_attributes']);
  if(variable_get('mo_auth_2fa_allow_reconfigure_2fa','Allowed') == 'Allowed'){
    $form['mo_auth_change_2fa']=array(
      '#type'=>'checkbox',
      '#title'=> t('I want to change/reconfigure my 2FA method.'),
      '#description' => t('<strong>Note:</strong> If you want to change/reconfigure the 2FA method then please check this checkbox and complete the authentication.'),
    );
  }

  if ( variable_get('mo_auth_remember_device','') === 'Allowed' ) {
    $form['mo_auth_remember_device'] = array(
      '#type' => 'checkbox',
      '#title' => t('I want to remember this device.'),
      '#description' => t('<strong>Note:</strong> If you want to remember this device then please check this checkbox and complete the authentication.'),
    );
  }

  $form['loader']['#markup'] = '</div><div class="mo2f-modal-container mo2f-modal-footer">';

  $submit_attributes['class'] = array('mo2f_button');

  $form['actions']['verify'] = array(
    '#type' => 'submit',
    '#value' => t('Verify'),
    '#attributes' => $submit_attributes,
  );

if($authType['code']!='KBA' && MoAuthUtilities::isKbaConfigured($user_configured_methods_array))
   $form['actions']['mo_auth_forgot_phone_btn'] = array(
            '#type' => 'submit',
            '#attributes' => array (
                'class' => array (
                    'mo_auth_forgot_phone_btn_class','mo2f_button'
                ),
                'autofocus'=>'FALSE',
            ),
            '#value' => t('Forgot phone?'),
            '#limit_validation_errors' => array(),
            '#submit' => array('mo_auth_forgot_phone'),


        );

  $form['actions']['cancel'] = array(
      '#markup' => l(t('Back to Login'), 'user'),
      '#suffix' => '</div></div></div>',
  );
  return $form;
}

function mo_auth_forgot_phone($form,&$form_state){

   $form_state['rebuild'] = TRUE;
  $uid = $form_state['uid'];
  $user = user_load($uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, 'KBA');
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->challenge($miniorange_user);

  if ( $response->status == 'SUCCESS' ) {

    $_SESSION['mo_auth']['mo_challenge_response'] = $response;

    $form_state['redirect'] = 'login/user/' . $user->uid . '/authenticate';
    $url = $form_state['redirect'];
    drupal_goto($url);
  } else {
    drupal_set_message(t('An error occured while processing your request. Please Try again.'), 'error');
    watchdog('miniorange_2fa', $response->message);
    drupal_goto('user');
  }
}
function mo_auth_build_form_content($form, $user,$base_url, $authType, $challenge_response, $success_form = TRUE, $empty_token = FALSE) {

  switch( $authType['code'] ) {
    case AuthenticationType::$OTP_OVER_EMAIL['code']:
      return mo_auth_build_otp_over_email_form($form, $base_url, $challenge_response, $success_form);
    case AuthenticationType::$EMAIL_VERIFICATION['code']:
      return mo_auth_build_oobemail_form($form, $base_url, $challenge_response);
    case AuthenticationType::$GOOGLE_AUTHENTICATOR['code']:
      return mo_auth_build_google_authenticator_form($form, $user, $base_url, $challenge_response, $success_form, $empty_token);
    case AuthenticationType::$QR_CODE['code']:
      return mo_auth_build_qrcode_authentication_form($form, $base_url, $challenge_response);
    case AuthenticationType::$KBA['code']:
      return mo_auth_build_kba_authentication_form($form, $base_url, $challenge_response, $success_form);
	  case AuthenticationType::$SOFT_TOKEN['code']:
	    return mo_auth_build_soft_token_form($form, $base_url, $challenge_response, $success_form, $empty_token);
	  case AuthenticationType::$PUSH_NOTIFICATIONS['code']:
      return mo_auth_build_push_notifications_form($form, $base_url, $challenge_response);
    case AuthenticationType::$SMS['code']:
      return mo_auth_build_otp_over_sms_form($form, $base_url, $challenge_response,'OTP OVER SMS', $success_form, $empty_token );
    case AuthenticationType::$OTP_OVER_PHONE['code']:
      return mo_auth_build_otp_over_sms_form($form, $base_url, $challenge_response, 'OTP OVER PHONE', $success_form, $empty_token);
	  case AuthenticationType::$SMS_AND_EMAIL['code']:
      return mo_auth_build_otp_over_sms_form($form, $base_url, $challenge_response, 'OTP OVER SMS AND EMAIL', $success_form, $empty_token);
	  default:
      return $form;
  }
}

function mo_auth_build_form_with_error_message(&$form_state,$empty_token = FALSE) {
  global $base_url;
  $uid = $form_state['uid'];
  $user = user_load($uid);
  $challenge_response = $_SESSION['mo_auth']['mo_challenge_response'];
  $authType = AuthenticationType::getAuthType($challenge_response->authType);
  $form = array();
  $form = mo_auth_build_form($form, $user, $base_url, $authType, $challenge_response, FALSE, $empty_token);

  $form_state['complete form']['header']['#markup'] = $form['header']['#markup'];

  return $form;
}

function mo_auth_build_google_authenticator_form($form, $user,$base_url, $challenge_response, $success_message = TRUE, $empty_token = FALSE) {

  if ($success_message === TRUE)
	   $message = t('Please enter the  passcode generated on your '.getConfiguredAuthenticator($user)['name'].' app.');
  elseif($empty_token)
     $message = t('The passcode field is required. Please try again.');
  else
  	 $message = t('The passcode you have entered is incorrect. Please enter the valid  passcode.');

  $message_div_class = $success_message === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
  $form['header']['#markup'] .= t('<div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>');

  $form['token'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('Enter  passcode.'), 'class' => array('mo2f-textbox', 'mo2f-textbox-otp'), 'autofocus' => 'true'),
  );
  $submit_attributes = array();
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}

function mo_auth_build_qrcode_authentication_form($form, $base_url, $challenge_response) {
  $message = t('Please scan the below QR Code from miniOrange Authenticator app.');
  $form['#attached']['js'][] = array(
    'data' => array(
      'mo_authentication' => array(
        'txId' => $challenge_response->txId,
        'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
      ),
    ),
    'type' => 'setting',
  );

  $form['header']['#markup'] .= t('<div class="mo2f-message mo2f-message-status">' . $message . '</div>');

  $form['header']['#markup'] .= t('<div class="mo2f-info mo2f-text-center">Please scan the below QR Code with miniOrange Authenticator app to authenticate yourself.</div>');
  $form['header']['#markup'] .= '<div class="mo2f-text-center"><img class="mo2f_image" src="data:image/jpg;base64,' . $challenge_response->qrCode . '"></div>';

  $form['txId'] = array(
    '#type' => 'hidden',
    '#value' => $challenge_response->txId,
  );
  $submit_attributes = array('class' => array('element-invisible'));
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}

function mo_auth_build_oobemail_form($form, $base_url, $challenge_response) {
  $response = $_SESSION['mo_auth']['mo_challenge_response'];
  $user_email = $challenge_response->emailDelivery->contact;
  $hidden_email = MoAuthUtilities::getHiddenEmail($user_email);
  $message = t('A verification email is sent to <b class="mo2f_bold">' . $hidden_email . '</b>. Please click on accept link to verify your email.');
  $form['#attached']['js'][] = array(
    'data' => array(
      'mo_authentication' => array(
        'txId' => $response->txId,
        'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
      ),
    ),
    'type' => 'setting',
  );

  $form['header']['#markup'] .= t('<div class="mo2f-message mo2f-message-status">' . $message . '</div>');

  $form['header']['#markup'] .= t('<div class="mo2f-info mo2f-text-center">A verification email is sent to your registered email.</div>
                  <div class="mo2f-info mo2f-text-center">We are waiting for your approval...</div>');
  $image_path = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/ajax-loader-login.gif');
  $form['header']['#markup'] .= '<div class="mo2f-text-center"><img class="mo2f_image" src="' . $image_path . '"></div>';

  $form['txId'] = array(
    '#type' => 'hidden',
    '#value' => $response->txId,
  );
  $submit_attributes = array('class' => array('element-invisible'));
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}

function mo_auth_build_kba_authentication_form($form, $base_url, $challenge_response, $success_message = TRUE) {
	if ($success_message === TRUE)
		$message = t('Please answer the following questions.');
	else
		$message = t('The answers you have entered are incorrect.');

	$message_div_class = $success_message === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
	$form['header']['#markup'] .= t('<div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>');
	$form['header']['#markup'] .= t('<div class="mo2f-info">Please answer the following questions:</div>');
	$form['header']['#markup'] .= '<div class="mo2f-kba-header mo2f-kba-row">
  			<div class="mo2f-kba-srno">No.</div>
  			<div class="mo2f-kba-question">Questions</div>
			<div class="mo2f-kba-answer">Answers</div>
  			</div>';
	$i = 0;
	$questions = $challenge_response->questions;
	foreach ($questions as $ques) {
	  $i++;
	  $form['header']['#markup'] .= '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">' . $i . '.</div>
  			<div class="mo2f-kba-question">'
	  					. $ques->question .
	  					'</div>
			<div class="mo2f-kba-answer"><input class="form-control form-text" type="text" name="mo2f_kbaanswer' . $i . '" title="Only alphanumeric letters with special characters(_@.$#&amp;+-) are allowed." pattern="(?=\S)[A-Za-z0-9_@.$#&amp;+-\s]{1,100}" required="true" autofocus="true" autocomplete="off" placeholder="Enter your answer"></div>
  		<input type="hidden" name="mo2f_kbaquestion' . $i .'" value="' . $ques->question . '"/></div>';
	}
	$form['txId'] = array(
	  '#type' => 'hidden',
	  '#value' => $challenge_response->txId,
	);
	$submit_attributes = array();
	$form['submit_attributes'] = $submit_attributes;
	$form['mo_message'] = $message;
	return $form;
}

function mo_auth_build_soft_token_form($form, $base_url, $challenge_response, $success_message = TRUE, $empty_token = FALSE) {
  if ($success_message === TRUE)
	   $message = t('Please enter the  passcode generated on your miniOrange Authenticator app.');
  elseif($empty_token)
     $message = t('The passcode field is required. Please try again.');
  else
  	 $message = t('The passcode you have entered is incorrect. Please enter the valid passcode.');

  $message_div_class = $success_message === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
  $form['header']['#markup'] .= t('<div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>');

  $form['token'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => t('Enter  passcode.'), 'class' => array('mo2f-textbox', 'mo2f-textbox-otp'), 'autofocus' => 'true'),
  );
  $submit_attributes = array();
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}

function mo_auth_build_push_notifications_form($form, $base_url, $challenge_response) {
  $response = $_SESSION['mo_auth']['mo_challenge_response'];
  //$user_email = $challenge_response->emailDelivery->contact;
  //$hidden_email = MoAuthUtilities::getHiddenEmail($user_email);
  $message = t('Please accept the push notification sent to your miniOrange Authenticator App.');
  $form['#attached']['js'][] = array(
    'data' => array(
      'mo_authentication' => array(
        'txId' => $response->txId,
        'url' => MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API,
      ),
    ),
    'type' => 'setting',
  );

  $form['header']['#markup'] .= t('<div class="mo2f-message mo2f-message-status">' . $message . '</div>');

  $form['header']['#markup'] .= t('<div class="mo2f-info mo2f-text-center">A Push Notification has been sent to your miniOrange Authenticator App.</div>
                  <div class="mo2f-info mo2f-text-center">We are waiting for your approval...</div>');
  $image_path = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/ajax-loader-login.gif');
  $form['header']['#markup'] .= '<div class="mo2f-text-center"><img class="mo2f_image" src="' . $image_path . '"></div>';

  $form['txId'] = array(
    '#type' => 'hidden',
    '#value' => $response->txId,
  );
  $submit_attributes = array('class' => array('element-invisible'));
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}

function mo_auth_build_otp_over_sms_form($form, $base_url, $challenge_response, $method_to_test, $success_message = TRUE, $empty_token = FALSE) {
  $phone_no = '';
  if ( isset( $challenge_response->phoneDelivery->contact ) ) {
    $phone_no = $challenge_response->phoneDelivery->contact;
    $phone_no = substr_replace($phone_no,"*******",0,-4);
  }
	if ( $success_message === TRUE ){
	    if( $method_to_test === 'OTP OVER SMS AND EMAIL' ) {
            $message = t('Please enter the  passcode sent to your mobile phone and email.');
      }elseif ( $method_to_test === 'OTP OVER SMS' ) {
            $message = t('Please enter the OTP/passcode sent to your mobile phone <strong>'.$phone_no.'</strong>.');
      }elseif ($method_to_test === 'OTP OVER PHONE') {
            $message = 'Please enter the OTP/passcode prompted on phone call - <strong>'.$phone_no.'</strong>.';
      }
	}elseif( $empty_token ) {
        $message = t('The OTP field is required. Please try again.');
    }else {
        $message = t('The OTP you have entered is incorrect. Please enter the valid  OTP.');
    }

	$message_div_class = $success_message === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
    $form['header']['#markup'] .= t('<div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>');

	$form['token'] = array (
      '#type' => 'textfield',
      '#title' => t('Please enter the passcode you received:'),
      '#attributes' => array('autofocus' => 'true'),
    );

	$submit_attributes = array();
	$form['submit_attributes'] = $submit_attributes;
	$form['mo_message'] = $message;
	return $form;
}

function mo_auth_build_otp_over_email_form($form, $base_url, $challenge_response, $success_message = TRUE) {

  if ( $success_message === TRUE )
    $message = t('Please enter the one time passcode (OTP) sent to your  email.');
  else
    $message = t('The OTP you have entered is incorrect. Please enter the valid  OTP.');

  $message_div_class = $success_message === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
    $form['header']['#markup'] .= t('<div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>');


  $form['token'] = array (
      '#type' => 'textfield',
      '#title' => t('Please enter the passcode you received:'),
      '#attributes' => array('autofocus' => 'true'),
    );

  $submit_attributes = array();
  $form['submit_attributes'] = $submit_attributes;
  $form['mo_message'] = $message;
  return $form;
}


 function getConfiguredAuthenticator($user){

  $configured_methods = mo_auth_get_configured_methods($user->uid);
  if ( in_array( 'GOOGLE AUTHENTICATOR', $configured_methods ) ) {
    $users_active_method = AuthenticationType::getAuthType( 'GOOGLE AUTHENTICATOR' );
  } elseif ( in_array( 'MICROSOFT AUTHENTICATOR', $configured_methods ) ) {
    $users_active_method = AuthenticationType::getAuthType( 'MICROSOFT AUTHENTICATOR' );
  } elseif ( in_array( 'AUTHY AUTHENTICATOR', $configured_methods ) ) {
    $users_active_method = AuthenticationType::getAuthType( 'AUTHY AUTHENTICATOR' );
  } elseif ( in_array( 'LASTPASS AUTHENTICATOR', $configured_methods ) ) {
    $users_active_method = AuthenticationType::getAuthType( 'LASTPASS AUTHENTICATOR' );
  }

  return $users_active_method;
}
