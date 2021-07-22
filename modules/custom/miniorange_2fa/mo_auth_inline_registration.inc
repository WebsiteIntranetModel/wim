<?php
/*
 * @file
 * Page 1: Select Email address.
 * Page 2: Verify OTP.
 * Page 3: Select Auth Method.
 * Page 4: Configure Auth Method.
 * Page 5: Configure KBA.
 *
 */

function mo_auth_inline_registration($form, &$form_state, $user) {
  global $base_url;
  $mo2FAResetRequest = isset($_GET['mo2faresetrequest'])?TRUE:FALSE;
  if (user_is_logged_in() && ($user->uid !=$GLOBALS['user']->uid || !$mo2FAResetRequest)) {
    drupal_goto('user');
    exit();
  }
  $form_state['uid'] = $user->uid;


  if ((empty($user->miniorange_registered_email) && isset($_SESSION['mo_auth']['1ST_FACTOR_AUTHENTICATED_FOR']) && $_SESSION['mo_auth']['1ST_FACTOR_AUTHENTICATED_FOR']==$user->uid)  || ( $mo2FAResetRequest && user_is_logged_in()) ) {
    // Display page 5 if $form_state['storage']['page_five'] is set

    if (isset($form_state['storage']['page_five'])) {
      return mo_auth_inline_registration_page_five($form_state,TRUE);
    } elseif (isset($form_state['storage']['page_otp_validate'])) {
	  return mo_auth_inline_registration_page_four_otp_validate($form_state);
    } elseif (isset($form_state['storage']['page_four'])) {
      return mo_auth_inline_registration_page_four($form_state);
    } elseif (isset($form_state['storage']['page_three']) || ($mo2FAResetRequest&& user_is_logged_in())) {
      return mo_auth_inline_registration_page_three();
    } elseif (isset($form_state['storage']['page_two'])) {
      // $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
      return mo_auth_inline_registration_page_two($form, $form_state);
    } else {
      return mo_auth_inline_registration_page_one(NULL,$user->mail);
    }
  }
}
function mo_auth_inline_registration_validate($form, &$form_state) {
  if ($form_state['clicked_button']['#id'] == 'page-one-submit') {
    $email = $form['mo_auth_user_email']['#value'];
	  $trimed_email = trim($email);

	if (empty($trimed_email)) {
	  form_set_error('user_registration', 'Please enter your valid email.');
      $error_form = mo_auth_inline_registration_page_one('EMPTY_EMAIL',$trimed_email, FALSE);
      $form_state['complete form']['mo_auth_user_email']['#prefix'] = $error_form['mo_auth_user_email']['#prefix'];
      $form_state["rebuild"] = TRUE;
	}

  if (!valid_email_address($trimed_email) ) {
    form_set_error('user_registration', 'Please enter your valid email.');
      $error_form = mo_auth_inline_registration_page_one('INVALID_EMAIL',$trimed_email, FALSE);
      $form_state['complete form']['mo_auth_user_email']['#prefix'] = $error_form['mo_auth_user_email']['#prefix'];
      $form_state["rebuild"] = TRUE;
  }
  } elseif ($form_state['clicked_button']['#id'] == 'page-two-submit') {
    $token = $form['mo_auth_verify_token']['#value'];
    $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
    $challenge_response = $form_state['storage']['page_one_values']['user_challenge_response'];
    $validate_response = validate_otp_for_user($challenge_response->txId, $token);

    if (empty($token)) {
      $error_form = mo_auth_inline_registration_page_two($form, $form_state, FALSE);
      $form_state['complete form']['mo_auth_verify_token']['#prefix'] = $error_form['mo_auth_verify_token']['#prefix'];
      $form_state['storage']['page_two_values'] = $form_state['values'];
      $form_state['storage']['page_two_values']['invalid_otp'] = TRUE;
      form_set_error('user_registration', 'The passcode field is required. Please try again.');
      $form_state["rebuild"] = TRUE;
    }

    if ($validate_response->status == 'FAILED') {
      $error_form = mo_auth_inline_registration_page_two($form, $form_state, FALSE);
      $form_state['complete form']['mo_auth_verify_token']['#prefix'] = $error_form['mo_auth_verify_token']['#prefix'];
      $form_state['storage']['page_two_values'] = $form_state['values'];
      $form_state['storage']['page_two_values']['invalid_otp'] = TRUE;
      form_set_error('user_registration', 'The OTP you have entered is incorrect.');
      $form_state["rebuild"] = TRUE;
    } elseif ($validate_response->status != 'SUCCESS') {
      $form_state["rebuild"] = TRUE;
      form_set_error('user_registration', 'An error occured while registering the user.');
      drupal_goto("user");
    }
  } elseif ($form_state['clicked_button']['#id'] == 'page-four-submit') {
    $method = $form_state['storage']['page_three_values']['mo_auth_method'];
    if ( AuthenticationType::isCodeBelongsToAAuthenticator($method)) {
      $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
      $google_auth_response = $form_state['storage']['page_four_values']['google_auth_response'];
      $token = $form['mo_auth_googleauth_token']['#value'];
      $secret = $google_auth_response->secret;

      $customer = new MiniorangeCustomerProfile();
      $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, NULL, AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
      $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
      $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$GOOGLE_AUTHENTICATOR['code'], $secret, $token, NULL);
      if ($response->status == 'FAILED') {
        // Passcode incorrect. Try again - Show error form
        form_set_error('user_registration', 'The passcode you have entered is incorrect.');
        $error_form = mo_auth_get_google_authentication_form($form_state, FALSE);
        $form_state['complete form']['mo_auth_googleauth_token']['#prefix'] = $error_form['mo_auth_googleauth_token']['#prefix'];
        $form_state["rebuild"] = TRUE;
      } elseif ($response->status != 'SUCCESS') {
        $form_state["rebuild"] = TRUE;
        form_set_error('user_registration', 'An error occured while registering the user.');
        watchdog('miniorange_2fa', $response->message);
        drupal_goto("user");
      }
    } elseif ($method == AuthenticationType::$KBA['code']) {
      if (mo_auth_check_if_kba_empty($form)) {
		form_set_error('empty_kba', 'All the fields are required. Please try again.');
	    $form_state['storage']['error_code'] = 'EMPTY_KBA_INPUT';
        $error_form = mo_auth_get_kba_authentication_form($form_state, FALSE);
        $form_state['complete form']['mo_auth_question1']['#prefix'] = $error_form['mo_auth_question1']['#prefix'];
        $form_state["rebuild"] = TRUE;
        return;
	  } elseif (mo_auth_validate_kba_questions($form)) {
        form_set_error('user_registration', 'The question you select cannot be same.');
        $error_form = mo_auth_get_kba_authentication_form($form_state, FALSE);
        $form_state['complete form']['mo_auth_question1']['#prefix'] = $error_form['mo_auth_question1']['#prefix'];
        $form_state["rebuild"] = TRUE;
        return;
      }
    }elseif ($method == AuthenticationType::$SMS['code'] ||	$method == AuthenticationType::$SMS_AND_EMAIL['code'] || $method == AuthenticationType::$OTP_OVER_PHONE['code']) {
		$email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
		$phone = str_replace(" ","",$form_state['input']['mo_auth_otpoversms_phone']);
		if( empty( $phone ) || strlen($phone)<5) {
			$error = 'The passcode field is required. Please enter the phone number with country code.';
			form_set_error('empty_phone_number', $error);
			$form_state['storage']['error_code'] = 'EMPTY_PHONE_INPUT';
			$error_form = mo_auth_get_otp_over_sms_authentication_form($form_state, FALSE,  $error);
			$form_state['complete form']['mo_auth_otpoversms_phone']['#prefix'] = $error_form['mo_auth_otpoversms_phone']['#prefix'];
			$form_state["rebuild"] = TRUE;
			return;
		}
	}

  } elseif ($form_state['clicked_button']['#id'] == 'page-five-submit') {
	if (mo_auth_check_if_kba_empty($form)) {
	  form_set_error('empty_kba', 'All the fields are required. Please try again.');
	  $form_state['storage']['error_code'] = 'EMPTY_KBA_INPUT';
      $error_form = mo_auth_get_kba_authentication_form($form_state, FALSE);
      $form_state['complete form']['mo_auth_question1']['#prefix'] = $error_form['mo_auth_question1']['#prefix'];
      $form_state["rebuild"] = TRUE;
      return;
	} elseif (mo_auth_validate_kba_questions($form)) {
      form_set_error('user_registration', 'The question you select cannot be same.');
      $error_form = mo_auth_get_kba_authentication_form($form_state, FALSE);
      $form_state['complete form']['mo_auth_question1']['#prefix'] = $error_form['mo_auth_question1']['#prefix'];
      $form_state["rebuild"] = TRUE;
      return;
    }
  }elseif ($form_state['clicked_button']['#id'] == 'page-otp-validate') {
	  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
	  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
	  $otp_code = $form_state['input']['mo_auth_otpoversms_code'];

	  if(empty($otp_code)){
		$message = "The passcode field is required. Please try again.";
		form_set_error('empty_code', $message);
		$form_state['storage']['error_code'] = 'EMPTY_OTP_CODE_INPUT';
		$error_form = mo_auth_get_otp_over_sms_validate_form($form_state, FALSE, $message);
		$form_state['complete form']['mo_auth_otpoversms_code']['#prefix'] = $error_form['mo_auth_otpoversms_code']['#prefix'];
		$form_state["rebuild"] = TRUE;
		return;
	  }

  }

}

function mo_auth_check_if_kba_empty($form) {
  $question1 = $form['mo_auth_question1']['#value'];
  $answer1 = $form['mo_auth_answer1']['#value'];

  $question2 = $form['mo_auth_question2']['#value'];
  $answer2 = $form['mo_auth_answer2']['#value'];

  $question3 = $form['mo_auth_question3']['#value'];
  $answer3 = $form['mo_auth_answer3']['#value'];
  if(empty($question1) || empty($answer1) || empty($question2) || empty($answer2) || empty($question3) || empty($answer3)){
    return TRUE;
  }
  return FALSE;
}
function mo_auth_validate_kba_questions($form) {
  $question1 = $form['mo_auth_question1']['#value'];
  $question2 = $form['mo_auth_question2']['#value'];
  $question3 = $form['mo_auth_question3']['#value'];

  if ( $question1 == $question2 || $question1 == $question3 || $question2 == $question3 ) {
    return TRUE;
  }
  return FALSE;
}

function mo_auth_inline_registration_submit($form, &$form_state) {
  if (isset($form_state['storage']['form_build_id'])) {
    $form_state['values']['form_build_id'] = $form_state['storage']['form_build_id'];
  }
  $form_state['storage']['form_build_id'] = $form_state['values']['form_build_id'];
  // Handle page 1 submissions
  if ($form_state['clicked_button']['#id'] == 'page-one-submit') {
    // Search user and send OTP
    return handle_page_one_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-one-back') {
    // Send back to login. NOT REQUIRED.
    drupal_goto("user");
  } elseif ($form_state['clicked_button']['#id'] == 'page-two-submit') {
    // Validate the OTP
    return handle_page_two_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-two-back') {
    // Send back to Select email screen
    unset($form_state['storage']['page_two']);
    unset($form_state['storage']['page_one_values']);
    unset($form_state['storage']['user_search_response']);
    $form_state["rebuild"] = TRUE;
  } elseif ($form_state['clicked_button']['#id'] == 'page-three-submit') {
    // Show configure auth page. skip to page 5 if email-verification
    return handle_page_three_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-three-back') {
    // Send back to login. NOT REQUIRED.
    drupal_goto("user");
  } elseif ($form_state['clicked_button']['#id'] == 'page-four-submit') {
    // Configure Auth method.
    return handle_page_four_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-four-back') {
    // Send back to Auth Method selection.
    unset($form_state['storage']['page_four']);
    unset($form_state['storage']['page_three_values']);
    $form_state["rebuild"] = TRUE;
  } elseif ($form_state['clicked_button']['#id'] == 'page-otp-validate') {
    // Configure Auth method.
    return handle_page_otp_validate_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-otp-validate-back') {
    // Send back to Auth Method selection.
    unset($form_state['storage']['page_otp_validate']);
    unset($form_state['storage']['page_otp_validate_values']);
    $form_state["rebuild"] = TRUE;
  } elseif ($form_state['clicked_button']['#id'] == 'page-five-submit') {
    // Configure KBA.
    return handle_page_five_submit($form, $form_state);
  } elseif ($form_state['clicked_button']['#id'] == 'page-five-back') {
    // Send back to login. NOT REQUIRED.
	unset($form_state['storage']['page_four']);
    unset($form_state['storage']['page_three_values']);
	unset($form_state['storage']['page_five']);
    unset($form_state['storage']['page_four_values']);
    $form_state["rebuild"] = TRUE;
  } else {
    // ERROR: send to login page.
    drupal_goto("user");
  }
}
function mo_auth_inline_registration_page_one($status,$user_email, $success_form = TRUE) {

  $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Register (Step '.getStepNumber(1,5).')</div>
                <div class="mo2f-modal-container">';
  if ($success_form === FALSE) {
    if ($status == 'USER_FOUND_UNDER_DIFFERENT_CUSTOMER') {
      $message = 'This email is already in use. Please try another email.';
      $prefix .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
    } elseif ($status == 'EMPTY_EMAIL') {
	  $message = 'Please enter your valid email.';
      $prefix .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
	} elseif ($status == 'INVALID_EMAIL') {
    $message = 'Please enter your valid email.';
      $prefix .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
  }

  }
  $prefix .= '<div class="mo2f-info mo2f-text-center">
  		A new security system has been enabled to better protect your account. Please configure
  		your Two-Factor Authentication method.</div>
  		<div class="mo2f-text-center">';
  $sufix = '</div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';

  $form['mo_auth_user_email'] = array (
    '#type' => 'textfield',
    '#default_value'=>$user_email,
    '#attributes' => array (
      'placeholder' => 'person@example.com',
      'class' => array (
        'mo2f_email_textbox'
      ),
    ),
	'#disabled'=> variable_get('mo_auth_make_email_editable',false) == false ? true : false,
	'#required' => TRUE,
    '#prefix' => $prefix,
    '#suffix' => $sufix
  );
  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['start'] = array (
    '#type' => 'submit',
    '#id' => 'page-one-submit',
    '#value' => t('Get Started'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#markup' => l(t('Back to Login'), 'user'),
    '#suffix' => '</div></div></div>'
  );
  return $form;
}
function mo_auth_inline_registration_page_two($form, &$form_state, $success_form = TRUE) {
  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
  $user_creation_limit_exceeded = FALSE;
  if (isset($form_state['storage']['user_limit_exceeded'])) {
    $user_creation_limit_exceeded = $form_state['storage']['user_limit_exceeded'];
  }
  if ( $user_creation_limit_exceeded ) {
     $message = t('Something went wrong. Please contact your administrator.');
  }
  elseif ($success_form === TRUE && ! isset($form['mo_auth_verify_token'])) {
    $message = t('We have sent an one time passcode (OTP) to ' . $email . '. Enter the passcode to verify your email.');
  }
  elseif (empty($form['mo_auth_verify_token']['#value'])) {
     $message = t('The passcode field is required. Please try again.');
  }
  else {
    $message = t('The one time passcode (OTP) you have entered is incorrect.');
  }

  $message_div_class = $success_form === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';
  if ($user_creation_limit_exceeded)
    $message_div_class = 'mo2f-message-error';
  $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Verify Email (Step '.getStepNumber(2,5).')</div>
                <div class="mo2f-modal-container">
				  <div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>
  		          <div class="mo2f-info">Enter the passcode:</div>
				<div>';
  $sufix = '</div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';
  $form['mo_auth_verify_token'] = array (
    '#type' => 'textfield',
    '#attributes' => array (
      'placeholder' => 'Enter the passcode',
      'class' => array (
        'mo2f-textbox',
        'mo2f-textbox-otp'
      ),
      'autofocus' => 'true'
    ),
    '#prefix' => $prefix,
    '#suffix' => $sufix
  );

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['verify'] = array (
    '#type' => 'submit',
    '#id' => 'page-two-submit',
    '#value' => t('Verify'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-two-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
}
function mo_auth_inline_registration_page_three($success_form = TRUE) {
  $prefix = '<div class="mo2f-modal">
            <div class="mo2f-modal-content">
              <div class="mo2f-modal-container mo2f-modal-header">Select
  		      Authentication method (Step '.getStepNumber(3,5).')</div>
              <div class="mo2f-modal-container">
		<div class="mo2f-info">Select your authentication method:</div><div>';
  $sufix = '</div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';

  $options = MoAuthUtilities::get_2fa_methods_for_inline_registration(TRUE);
  $form['mo_auth_method'] = array (
    '#type' => 'radios',
    '#default_value' => array_keys($options)[0],
    '#options' => $options,
    '#required' => TRUE,
    '#prefix' => $prefix,
    '#suffix' => $sufix
  );

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['next'] = array (
    '#type' => 'submit',
    '#id' => 'page-three-submit',
    '#value' => t('Next'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-three-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
}
function mo_auth_inline_registration_page_four(&$form_state, $success_form = TRUE) {
  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
  if ( AuthenticationType::isCodeBelongsToAAuthenticator($method) ) {
    return mo_auth_get_google_authentication_form($form_state, $success_form);
  } elseif ($method == AuthenticationType::$QR_CODE['code']) {
    return mo_auth_get_qrcode_authentication_form($form_state);
  } elseif ($method == AuthenticationType::$KBA['code']) {
    return mo_auth_get_kba_authentication_form($form_state, $success_form);
  } elseif ($method == AuthenticationType::$SOFT_TOKEN['code']) {
	return mo_auth_get_qrcode_authentication_form($form_state);
  } elseif ($method == AuthenticationType::$PUSH_NOTIFICATIONS['code']) {
    return mo_auth_get_qrcode_authentication_form($form_state);
  } elseif ($method == AuthenticationType::$SMS['code'] || $method == AuthenticationType::$SMS_AND_EMAIL['code'] || $method == AuthenticationType::$OTP_OVER_PHONE['code'] || $method == AuthenticationType::$OTP_OVER_EMAIL['code'] ) {
    return mo_auth_get_otp_over_sms_authentication_form($form_state, $success_form, "");
  }
}

function mo_auth_inline_registration_page_four_otp_validate(&$form_state, $success_form = TRUE) {
    return mo_auth_get_otp_over_sms_validate_form($form_state, $success_form, "");
}

function mo_auth_inline_registration_page_five(&$form_state,$success_form = TRUE) {
  handle2FAReset($form_state);

  $prefixQuestion1 = '<div class="mo2f-modal">
    <div class="mo2f-modal-content">
      <div class="mo2f-modal-container mo2f-modal-header">Configure Backup method
  		(Step '.getStepNumber(5,5).')</div>
      <div class="mo2f-modal-container">
	    <div class="mo2f-info">Please choose your backup security questions:</div>
  		  <div>
  		    <div class="mo2f-kba-header mo2f-kba-row">
  			  <div class="mo2f-kba-srno">Sr. No.</div>
  			  <div class="mo2f-kba-question">Questions</div>
			  <div class="mo2f-kba-answer">Answers</div>
  			</div>
  			<div class="mo2f-kba-row">
  			  <div class="mo2f-kba-srno">1.</div>
  			  <div class="mo2f-kba-question">';
  $suffixQuestion1 = '</div>';

  $prefixAnswer1 = '<div class="mo2f-kba-answer">';
  $suffixAnswer1 = '</div></div>';

  $prefixQuestion2 = '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">2.</div>
  			<div class="mo2f-kba-question">';
  $suffixQuestion2 = '</div>';

  $prefixAnswer2 = '<div class="mo2f-kba-answer">';
  $suffixAnswer2 = '</div></div>';

  $prefixQuestion3 = '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">3.</div>
  			<div class="mo2f-kba-question">';
  $suffixQuestion3 = '</div>';

  $prefixAnswer3 = '<div class="mo2f-kba-answer">';
  $suffixAnswer3 = '</div></div></div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $suffixAnswer3 .= '<style>#messages div.messages{visibility:hidden;}</style>';

  $options = array (
    'What is your first company name?' => 'What is your first company name?',
    'What was your childhood nickname?' => 'What was your childhood nickname?',
    'In what city did you meet your spouse/significant other?' => 'In what city did you meet your spouse/significant other?',
    'What is the name of your favorite childhood friend?' => 'What is the name of your favorite childhood friend?',
    'What school did you attend for sixth grade?' => 'What school did you attend for sixth grade?',
    'In what city or town was your first job?' => 'In what city or town was your first job?',
    'What is your favourite sport?' => 'What is your favourite sport?',
    'Who is your favourite sports player?' => 'Who is your favourite sports player?',
    'What is your grandmothers maiden name?' => 'What is your grandmothers maiden name?',
    'What was your first vehicles registration number?' => 'What was your first vehicles registration number?'
  );
  $form['mo_auth_question1'] = array (
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $options['What is your first company name?'],
    '#prefix' => $prefixQuestion1,
    '#suffix' => $suffixQuestion1,
    '#attributes' => array('class' => array('mo2f_select')),
  );
  $form['mo_auth_answer1'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer1,
    '#suffix' => $suffixAnswer1,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );
  $form['mo_auth_question2'] = array (
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => $options['What is the name of your favorite childhood friend?'],
    '#prefix' => $prefixQuestion2,
    '#suffix' => $suffixQuestion2,
    '#attributes' => array('class' => array('mo2f_select')),
  );
  $form['mo_auth_answer2'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer2,
    '#suffix' => $suffixAnswer2,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );
  $form['mo_auth_question3'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixQuestion3,
    '#suffix' => $suffixQuestion3,
    '#attributes' => array (
      'placeholder' => 'Enter your custom question here'
    )
  );
  $form['mo_auth_answer3'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer3,
    '#suffix' => $suffixAnswer3,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['register'] = array (
    '#type' => 'submit',
    '#id' => 'page-five-submit',
    '#value' => t('Register'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-five-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
}
function handle_page_one_submit($form, &$form_state) {
  $email = variable_get('mo_auth_make_email_editable',false) == false ? user_load($form_state['uid'])->mail : $form_state['input']['mo_auth_user_email'];
  $users = entity_load('user');
  $email_used = FALSE;
  foreach ($users as $u) {
    if (! empty($u->miniorange_registered_email)) {
      $registered_email = $u->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
      if (strcasecmp(trim($registered_email), trim($email)) == 0) {
        $email_used = TRUE;
        break;
      }
    }
  }
  if ($email_used) {
    // Send Status as this to show error message
    $form = mo_auth_inline_registration_page_one('USER_FOUND_UNDER_DIFFERENT_CUSTOMER',$email, FALSE);
    $form_state['complete form']['mo_auth_user_email']['#prefix'] = $form['mo_auth_user_email']['#prefix'];
    form_set_error('user_registration', 'This email is already in use. Please try another email.');
    $form_state["rebuild"] = TRUE; // Added
    return $form;
  }
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, NULL, NULL);
  $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

  $response = $user_api_handler->search($miniorange_user);
  if ( ($response->status == 'USER_FOUND' || $response->status == 'USER_NOT_FOUND')) {
    $challenge_response = send_otp_email_to_user($email);
    if ($challenge_response->status == 'SUCCESS') {
      // if (true) {
      /*
       * We set this to determine which elements to display when the page reloads.
       * Values below in the $form_state['storage'] array are saved to carry
       * forward to subsequent pages in the form.
       */
      $form_state['storage']['page_two'] = TRUE;
      $form_state['storage']['page_one_values'] = $form_state['values'];
      $form_state['storage']['page_one_values']['user_search_response'] = $response;
      $form_state['storage']['page_one_values']['user_challenge_response'] = $challenge_response;
      $form_state["rebuild"] = TRUE; // Added
    } else {
      drupal_set_message('An error occurred while registering. Please contact your administrator.', 'error');
    }
  } elseif ($response->status == 'USER_FOUND_UNDER_DIFFERENT_CUSTOMER') {
    $error_form = mo_auth_inline_registration_page_one($response->status,$email, FALSE);
    $form_state['complete form']['mo_auth_user_email']['#prefix'] = $error_form['mo_auth_user_email']['#prefix'];
    form_set_error('user_registration', 'This email is already in use. Please try another email.');
    $form_state["rebuild"] = TRUE; // Added
    return;
  } else {
    form_set_error('user_registration', $response->message);
    drupal_goto("user");
  }
}
function handle_page_two_submit($form, &$form_state) {
  $form_state["rebuild"] = TRUE; // Added
  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
  $user_search_response = $form_state['storage']['page_one_values']['user_search_response'];
  $getUserObj = user_load_by_mail($email);
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, $getUserObj->name, AuthenticationType::$EMAIL_VERIFICATION['code']);
  $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());

  if ($user_search_response->status == 'USER_NOT_FOUND') {
    $create_response = $user_api_handler->create($miniorange_user);

    if ($create_response->status == 'ERROR') {
      $form_state['storage']['user_limit_exceeded'] = TRUE;
      return;
    }
  }
  // Update User Auth method to OUT OF BAND EMAIL
  $user_update_response = $user_api_handler->update($miniorange_user);

  if ($user_update_response->status == 'SUCCESS') {
    $user = user_load($form_state['uid']);
    /*
     take decision if third page is required or not
     there are 2 condition
          1. 3rd page is not required but 4th page is required
          2. Both 3rd and 4th page both are not required
    */

    if(isThirdPageRequired()){
      $form_state['storage']['page_three'] = TRUE;
    }
    else{
      $form_state['storage']['page_four'] = TRUE;
      $form_state['storage']['page_three_values']['mo_auth_method'] = onlySelectedMethod();
      if ( !isFourthPageRequired() ){
        $form_state['storage']['page_five'] = TRUE;
      }
    }

    // $form_state['storage']['page_two_values'] = $form_state['values'];
    /*
     * $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'] = $email;
     * $user->configured_auth_methods[LANGUAGE_NONE][0]['value'] = array(
     * AuthenticationType::$EMAIL_VERIFICATION['code']
     * );
     * $registered_emails = variable_get('mo_auth_users_registered_emails');
     * $registered_emails[$email] = TRUE;
     * variable_set('mo_auth_users_registered_emails', $registered_emails);
     */
    return;
  }
  // Handle error. return to login.
}
function handle_page_three_submit($form, &$form_state) {
  $form_state["rebuild"] = TRUE; // Added

  if(!isset($form_state['storage']['page_one_values'])){
    global $user;

    $currentUser = user_load($user->uid);
    $form_state['storage']['page_one_values']['mo_auth_user_email']=$currentUser->miniorange_registered_email['und'][0]['value'];
    $form_state['storage']['page_one_values']['mo_2fa_new_user']=FALSE;
    $form_state['storage']['page_one_values']['mo_2fa_reset']=TRUE;
    $form_state['storage']['page_two_values']=array();

  }
  $method = $form['mo_auth_method']['#value'];

  if ($method == AuthenticationType::$EMAIL_VERIFICATION['code'] || $method == AuthenticationType::$EMAIL['code']) {
    // Go to Step 5 directly
    $form_state['storage']['page_five'] = TRUE;
    $form_state['storage']['page_three_values'] = $form_state['values'];
  } else {
    $form_state['storage']['page_four'] = TRUE;
    $form_state['storage']['page_three_values'] = $form_state['values'];
  }
}
function handle_page_four_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $method = $form_state['storage']['page_three_values']['mo_auth_method'];

  if ( AuthenticationType::isCodeBelongsToAAuthenticator($method) ) {
    $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
    $google_auth_response = $form_state['storage']['page_four_values']['google_auth_response'];
    $token = $form['mo_auth_googleauth_token']['#value'];
    $secret = $google_auth_response->secret;

    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, NULL, AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$GOOGLE_AUTHENTICATOR['code'], $secret, $token, NULL);
    if ($response->status == 'SUCCESS') {
      $form_state['storage']['page_five'] = TRUE;
      $form_state['storage']['page_four_values'] = $form_state['values'];
      return;
    } elseif ($response->status == 'FAILED') {
      // Passcode incorrect. Try again - Show error form
      form_set_error('user_registration', 'The passcode you have entered is incorrect.');
      $error_form = mo_auth_get_google_authentication_form($form_state, FALSE);
      $form_state['complete form']['mo_auth_googleauth_token'] = $error_form['mo_auth_googleauth_token'];
      return;
    }
  } elseif ($method == AuthenticationType::$QR_CODE['code'] || $method == AuthenticationType::$SOFT_TOKEN['code'] || $method == AuthenticationType::$PUSH_NOTIFICATIONS['code']) {
    $qrcode_response = $form_state['storage']['page_four_values']['qrcode_response'];
    $customer = new MiniorangeCustomerProfile();
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->getRegistrationStatus($qrcode_response->txId);
    if ($response->status == 'SUCCESS') {
      $form_state['storage']['page_five'] = TRUE;
      return;
    }
  } elseif ( $method == AuthenticationType::$SMS['code'] || $method == AuthenticationType::$SMS_AND_EMAIL['code'] || $method == AuthenticationType::$OTP_OVER_PHONE['code'] || $method == AuthenticationType::$OTP_OVER_EMAIL['code']) {
	 global $base_url;
	 $phone = $form_state['input']['mo_auth_otpoversms_phone'];
	 $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];

	 $customer = new MiniorangeCustomerProfile();

	 if( $method == AuthenticationType::$SMS_AND_EMAIL['code'] ) {
       $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, $phone, NULL, $method, $email);
   }elseif( $method == AuthenticationType::$SMS['code'] || $method == AuthenticationType::$OTP_OVER_PHONE['code'] ) {
       $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, $phone, NULL, $method, NULL);
   } elseif ( $method == AuthenticationType::$OTP_OVER_EMAIL['code'] ) {
     $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, NULL, NULL, $method, $email );
   }

	 $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
   $response = $auth_api_handler->challenge($miniorange_user);

	 if ( $response->status == 'SUCCESS' ) {
	  $form_state['storage']['page_otp_validate'] = TRUE;
	  $form_state['storage']['page_four_values'] = $form_state['values'];
	  $form_state['storage']['page_four_values']['user_challenge_response'] = $response;
      return;
	 }elseif ( $response->status == 'FAILED' ) {
		 $error = $response->message;

		 /* If transactions limit exceeded return to the same form */
		 if ( $error == 'The phone verification transaction limit has been exceeded. Please upgrade your premium plan.' ) {
             form_set_error('form', t('Something went wrong. Please contact your administrator.' ) );
             drupal_goto('user');
             exit;
         }
         form_set_error('error_sending_otp', $error);
         $form_state['storage']['error_code'] = 'INVALID_OTP';
         $error_form = mo_auth_get_otp_over_sms_validate_form($form_state, FALSE,  $error);
         $form_state['complete form']['mo_auth_otpoversms_code']['#prefix'] = $error_form['mo_auth_otpoversms_code']['#prefix'];
	     $form_state["rebuild"] = TRUE;
	     return;
	 }

  }elseif ($method == AuthenticationType::$KBA['code']) {
    handle_page_five_submit($form, $form_state);
    return;
  }
  // Handle all error
}

function handle_page_otp_validate_submit($form, &$form_state){
	$form_state['rebuild'] = TRUE;
    $method = $form_state['storage']['page_three_values']['mo_auth_method'];
	$otp_code = $form['mo_auth_otpoversms_code']['#value'];
    $challenge_response = $form_state['storage']['page_four_values']['user_challenge_response'];

	$validate_response = validate_otp_for_user($challenge_response->txId, $otp_code);
	if ( $validate_response->status == 'SUCCESS' ) {
      $form_state['storage']['page_five'] = TRUE;
	  $form_state['storage']['page_otp_validate_values'] = $form_state['values'];
	  return;
    }
	elseif ( $validate_response->status == 'FAILED' ) {
      $error = $validate_response->message;
	  form_set_error('invalid_otp', $error);
	  $form_state['storage']['error_code'] = 'INVALID_OTP';
	  $error_form = mo_auth_get_otp_over_sms_validate_form($form_state, FALSE,  $error);
	  $form_state['complete form']['mo_auth_otpoversms_code']['#prefix'] = $error_form['mo_auth_otpoversms_code']['#prefix'];
	  $form_state["rebuild"] = TRUE;
	  return;
    }
}


function handle_page_five_submit($form, &$form_state) {
  global $base_url;
  $form_state['rebuild'] = TRUE;
  $user_email = $form_state['storage']['page_one_values']['mo_auth_user_email'];

  $user_phone = isset($form_state['storage']['page_four_values']['mo_auth_otpoversms_phone']) ?
				$form_state['storage']['page_four_values']['mo_auth_otpoversms_phone'] : NULL;


  $question1 = $form['mo_auth_question1']['#value'];
  $answer1 = $form['mo_auth_answer1']['#value'];

  $question2 = $form['mo_auth_question2']['#value'];
  $answer2 = $form['mo_auth_answer2']['#value'];

  $question3 = $form['mo_auth_question3']['#value'];
  $answer3 = $form['mo_auth_answer3']['#value'];

  $qa1 = array (
    "question" => $question1,
    "answer" => $answer1
  );

  $qa2 = array (
    "question" => $question2,
    "answer" => $answer2
  );

  $qa3 = array (
    "question" => $question3,
    "answer" => $answer3
  );

  $kba = array (
    $qa1,
    $qa2,
    $qa3
  );
  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, $user_phone, NULL, $method);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$KBA['code'], NULL, NULL, $kba);
  if ($response->status == 'SUCCESS') {

    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $user_update_response = $user_api_handler->update($miniorange_user);
    if ($user_update_response->status == 'SUCCESS') {

      saveConfigurationInDB($form_state,TRUE);
      if(is2FAResetRequest($form_state)){
        drupal_set_message('Successfully updated your 2FA method to '.AuthenticationType::$KBA['name']);
        drupal_goto(variable_get('mo_auth_redirect_after_login', $base_url));
        exit;
      }

      $registered_emails = variable_get('mo_auth_users_registered_emails');
      $registered_emails[$user_email] = TRUE;
      variable_set('mo_auth_users_registered_emails', $registered_emails);
      user_login_submit(array (), $form_state);
      $mo_redirect_after_login = variable_get('mo_auth_redirect_after_login', $base_url);
      if( isset( $mo_redirect_after_login ) && !empty( $mo_redirect_after_login ) ) {
        drupal_goto( $mo_redirect_after_login );
      }
    }
  }
  // Error out. Send to login.
}

function send_otp_email_to_user($username) {
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, NULL, NULL, AuthenticationType::$EMAIL['code'], $username);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->challenge($miniorange_user);
  return $response;
}

function validate_otp_for_user($txId, $token) {
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), NULL, NULL, NULL, NULL);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->validate($miniorange_user, $txId, $token);
  return $response;
}
function mo_auth_get_google_authentication_form(&$form_state, $success_form = TRUE) {
  global $base_url;
  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
  $secret = '';
  $qrCode = '';
  $appName = ucwords(strtolower($form_state['storage']['page_three_values']['mo_auth_method']));

  if (isset($form_state['storage']['page_four_values']['google_auth_response'])) {
    $google_auth_response = $form_state['storage']['page_four_values']['google_auth_response'];
    $secret = $google_auth_response->secret;
    $qrCode = $google_auth_response->qrCodeData;
  } else {
    $customer = new MiniorangeCustomerProfile();
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, NULL, NULL);
    $response = $auth_api_handler->getGoogleAuthSecret($miniorange_user);
    if ($response->status == 'SUCCESS') {
      $form_state['storage']['page_four_values']['google_auth_response'] = $response;
      $secret = $response->secret;
      $qrCode = $response->qrCodeData;
    }
  }
  $iPhoneAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-google-authenticator-app-link.png');
  $androidAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-google-authenticator-app-link.png');
  $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Configure '.$appName.' (Step '.getStepNumber(4,5).')</div>
                <div class="mo2f-modal-container">';
  if ($success_form === FALSE) {
    $message = 'The passcode you have entered is incorrect.';
    $prefix .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
  }
  $prefix .= '<div><div class="mo2f-info"><b class="mo2f_bold">Step 1:</b> Download and install the '.$appName.' app</div>
			<div class="mo2f-text-center" style="display:inline-block;width:60%;'.($appName!=AuthenticationType::$GOOGLE_AUTHENTICATOR['code']?'visibility: hidden;':'').'text-align:center">
			  <a target="_blank" href="https://itunes.apple.com/in/app/google-authenticator/id388497605?mt=8"><img class="mo2f_image" src="' . $iPhoneAppLink . '"></a>
				</div>
				<div class="mo2f-text-center" style="display:inline-block;'.($appName!=AuthenticationType::$GOOGLE_AUTHENTICATOR['code']?'visibility: hidden;"':'"').'>
				  <a target="_blank" href="https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2"><img class="mo2f_image" src="' . $androidAppLink . '"></a>
				</div>
				</div>';
  $prefix .= '<div><div class="mo2f-info"><b class="mo2f_bold">Step 2:</b> Scan the QR Code from '.$appName.' app</div>
  			<div class="mo2f-info mo2f-text-center"><img class="mo2f_image" src="data:image/jpg;base64,' . $qrCode . '" /></div>
  			</div><div><div class="mo2f-info"><b class="mo2f_bold">Step 3:</b> Enter the passcode generated by '.$appName.' app</div>';
  $sufix = '</div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';
  $form['mo_auth_googleauth_token'] = array (
    '#type' => 'textfield',
    '#attributes' => array (
      'placeholder' => 'Enter the passcode',
      'class' => array (
        'mo2f-textbox',
        'mo2f-textbox-otp'
      ),
      'autofocus' => 'true'
    ),
    '#prefix' => $prefix,
    '#suffix' => $sufix
  );
  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['verify'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-submit',
    '#value' => t('Verify and Save'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
  //
}
function mo_auth_get_qrcode_authentication_form(&$form_state) {
  global $base_url;
  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];

  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
  $configureMessage = 'Configure QR Code Authentication';
  if ($method == AuthenticationType::$SOFT_TOKEN['code']) {
    $configureMessage = 'Configure Soft Token';
  } elseif ($method == AuthenticationType::$PUSH_NOTIFICATIONS['code']) {
	$configureMessage = 'Configure Push Notification';
  }

  $customer = new MiniorangeCustomerProfile();
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $email, NULL, NULL, NULL);
  $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$QR_CODE['code'], NULL, NULL, NULL);
  if (isset($response->status) && $response->status == 'IN_PROGRESS') {
    $form_state['storage']['page_four_values']['qrcode_response'] = $response;
    $iPhoneAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/iphone-google-authenticator-app-link.png');
    $androidAppLink = file_create_url($base_url . '/' . drupal_get_path('module', 'mo_auth') . '/includes/images/android-google-authenticator-app-link.png');
    $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">' . $configureMessage . ' (Step '.getStepNumber(4,5).')</div>
                <div class="mo2f-modal-container">';
    $prefix .= '<div><div class="mo2f-info"><b class="mo2f_bold">Step 1:</b> Download and install the miniOrange Authenticator app</div>
				<div class="mo2f-text-center" style="display:inline-block;width:60%;text-align:center">
				  <a target="_blank" href="https://itunes.apple.com/us/app/miniorange-authenticator/id796303566?ls=1"><img class="mo2f_image" src="' . $iPhoneAppLink . '"></a>
				</div>
				<div class="mo2f-text-center" style="display:inline-block">
				  <a target="_blank" href="https://play.google.com/store/apps/details?id=com.miniorange.authbeta"><img class="mo2f_image" src="' . $androidAppLink . '"></a>
				</div>
				</div>';
    $prefix .= '<div><div class="mo2f-info"><b class="mo2f_bold">Step 2:</b> Scan the QR Code from miniOrange Authenticator app</div>
  			<div class="mo2f-info mo2f-text-center"><img class="mo2f_image" src="data:image/jpg;base64,' . $response->qrCode . '" /></div>
  			</div>';
    $sufix = '</div><div class="mo2f-modal-container mo2f-modal-footer">';
	$sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';
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
      '#value' => $response->txId,
      '#prefix' => $prefix,
      '#suffix' => $sufix
    );
    $form['actions'] = array (
      '#type' => 'actions'
    );
    $form['actions']['save'] = array (
      '#type' => 'submit',
      '#id' => 'page-four-submit',
      '#value' => t('Save'),
      '#attributes' => array (
        'class' => array (
          'element-invisible','mo2f_button'
        )
      )
    );
    $form['actions']['cancel'] = array (
      '#type' => 'submit',
      '#id' => 'page-four-back',
      '#value' => t('Cancel'),
      '#attributes' => array('class' => array('mo2f_button')),
    );
    return $form;
  }
}
function mo_auth_get_kba_authentication_form(&$form_state, $success_form = TRUE) {
  $prefixQuestion1 = '<div class="mo2f-modal">
            <div class="mo2f-modal-content">
              <div class="mo2f-modal-container mo2f-modal-header">Configure Security Questions (Step '.getStepNumber(5,5).')</div>
              <div class="mo2f-modal-container">';
  if ($success_form === FALSE) {
	if ($form_state['storage']['error_code'] == 'EMPTY_KBA_INPUT') {
	  $message = 'All the fields are required. Please try again.';
      $prefixQuestion1 .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
	} else {
      $message = 'The questions you select cannot be same.';
      $prefixQuestion1 .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
	}
  }
  $prefixQuestion1 .= '<div class="mo2f-info">Please choose your backup security questions:</div><div><div class="mo2f-kba-header mo2f-kba-row">
  			<div class="mo2f-kba-srno">Sr. No.</div>
  			<div class="mo2f-kba-question">Questions</div>
			<div class="mo2f-kba-answer">Answers</div>
  			</div>
  			<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">1.</div>
  			<div class="mo2f-kba-question">';
  $suffixQuestion1 = '</div>';

  $prefixAnswer1 = '<div class="mo2f-kba-answer">';
  $suffixAnswer1 = '</div></div>';

  $prefixQuestion2 = '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">2.</div>
  			<div class="mo2f-kba-question">';
  $suffixQuestion2 = '</div>';

  $prefixAnswer2 = '<div class="mo2f-kba-answer">';
  $suffixAnswer2 = '</div></div>';

  $prefixQuestion3 = '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">3.</div>
  			<div class="mo2f-kba-question">';
  $suffixQuestion3 = '</div>';

  $prefixAnswer3 = '<div class="mo2f-kba-answer">';
  $suffixAnswer3 = '</div></div></div></div><div class="mo2f-modal-container mo2f-modal-footer">';
  $suffixAnswer3 .= '<style>#messages div.messages{visibility:hidden;}</style>';

  $options = array (
    'What is your first company name?' => t('What is your first company name?'),
    'What was your childhood nickname?' => t('What was your childhood nickname?'),
    'In what city did you meet your spouse/significant other?' => t('In what city did you meet your spouse/significant other?'),
    'What is the name of your favorite childhood friend?' => t('What is the name of your favorite childhood friend?'),
    'What school did you attend for sixth grade?' => t('What school did you attend for sixth grade?'),
    'In what city or town was your first job?' => t('In what city or town was your first job?'),
    'What is your favourite sport?' => t('What is your favourite sport?'),
    'Who is your favourite sports player?' => t('Who is your favourite sports player?'),
    'What is your grandmothers maiden name?' => t('What is your grandmothers maiden name?'),
    'What was your first vehicles registration number?' => t('What was your first vehicles registration number?')
  );
  $form['mo_auth_question1'] = array (
    '#type' => 'select',
    '#options' => $options,
    '#prefix' => $prefixQuestion1,
    '#suffix' => $suffixQuestion1
  );
  $form['mo_auth_answer1'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer1,
    '#suffix' => $suffixAnswer1,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );
  $form['mo_auth_question2'] = array (
    '#type' => 'select',
    '#options' => $options,
    '#prefix' => $prefixQuestion2,
    '#suffix' => $suffixQuestion2
  );
  $form['mo_auth_answer2'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer2,
    '#suffix' => $suffixAnswer2,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );
  $form['mo_auth_question3'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixQuestion3,
    '#suffix' => $suffixQuestion3,
    '#attributes' => array (
      'placeholder' => 'Enter your custom question here'
    )
  );
  $form['mo_auth_answer3'] = array (
    '#type' => 'textfield',
    '#prefix' => $prefixAnswer3,
    '#suffix' => $suffixAnswer3,
    '#size' => '20',
    '#attributes' => array (
      'placeholder' => 'Enter your answer'
    )
  );

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['register'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-submit',
    '#value' => t('Register'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-back',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
}

function mo_auth_get_otp_over_sms_authentication_form(&$form_state, $success_form = TRUE, $message="") {
  drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
  drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));
  global $base_url;
  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];

  $otp_over_sms = AuthenticationType::$SMS['code'];
  $otp_over_email = AuthenticationType::$OTP_OVER_EMAIL['code'];
  $otp_over_sms_and_email = AuthenticationType::$SMS_AND_EMAIL['code'];
  $otp_over_phone_call = AuthenticationType::$OTP_OVER_PHONE['code'];

  if( $method == $otp_over_sms ) {
	  $authmethod = 'OTP Over SMS';
  } elseif( $method == $otp_over_email ) {
    $authmethod = 'OTP Over Email';
  } elseif( $method == $otp_over_sms_and_email ) {
	  $authmethod = 'OTP Over SMS And Email';
  } elseif ( $method == $otp_over_phone_call ) {
    $authmethod =  'OTP Over Phone Call';
  }

  $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Configure ' . $authmethod .' (Step '.getStepNumber(4,5).')</div><div class="mo2f-modal-container">';

  if ( $success_form === FALSE ) {
    $prefix .= '<div class="mo2f-message mo2f-message-error">' . $message . '</div>';
  }

  if( $method == $otp_over_sms || $method == $otp_over_phone_call ) {
	  $step1 = ' Verify your phone number.';
  } elseif( $method == $otp_over_sms_and_email ) {
	  $step1 = ' Verify your phone number and email.';
  } elseif ( $method == $otp_over_email ) {
    $step1 = t('Verify your email.');
  }

  $prefix .= '<div><div class="mo2f-info">' . $step1 ;
  if( $method == $otp_over_sms_and_email ){
	  $prefix .= '<br><input type="text" class="mo2f-textbox mo2f-textbox-otp" value="' . $email . '" disabled><br>';
  }
  $prefix .= '</div></div>';
  $sufix = '</div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';
  if( $method != $otp_over_email ) {
    $form['mo_auth_otpoversms_phone'] = array(
      '#type' => 'textfield',
      '#description' => t('Enter number with country code Eg. +00xxxxxxxxxx'),
      '#id' => 'query_phone',
      '#attributes' => array(

        'placeholder' => 'Phone Number',
        'class' => array(
          'mo2f-textbox',
          'mo2f-textbox-otp',
          'query_phone'
        ),
        '#required' => 'true',
        'autofocus' => 'true'
      ),
      '#prefix' => $prefix,
      '#suffix' => $sufix,
    );
  }else{
    $form['mo_auth_otpoversms_phone'] = array(
      '#type' => 'textfield',
      '#default_value' => $email,
      '#disabled' => true,
      '#description' => t('<strong>Note: </strong>Your Email Id to which an OTP will be sent'),
      '#attributes' => array(
        'class' => array(
          'mo2f-textbox',
          'mo2f-textbox-otp'
        ),
        'autofocus' => TRUE
      ),
      '#required' => TRUE,
      '#prefix' => $prefix,
      '#suffix' => $sufix
    );
  }

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['send'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-submit',
    '#value' => t('Send OTP'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-four-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
    '#limit_validation_errors' => array(),
  );
  return $form;
}

function mo_auth_get_otp_over_sms_validate_form(&$form_state, $success_form = TRUE, $message = "") {
  $method                 = $form_state['storage']['page_three_values']['mo_auth_method'];
  $otp_over_sms           = AuthenticationType::$SMS['code'];
  $otp_over_email         = AuthenticationType::$OTP_OVER_EMAIL['code'];
  $otp_over_sms_and_email = AuthenticationType::$SMS_AND_EMAIL['code'];
  $otp_over_phone_call    = AuthenticationType::$OTP_OVER_PHONE['code'];

  if( $method == $otp_over_sms ) {
	  $authmethod = t('OTP Over SMS');
  } elseif( $method == $otp_over_sms_and_email ) {
	  $authmethod = t('OTP Over SMS And Email');
  } elseif ( $method == $otp_over_email ) {
    $authmethod = t('OTP Over Email');
  } elseif( $method == $otp_over_phone_call ) {
    $authmethod = t('OTP Over Phone Call');
  }

  $email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
  $phone = $form_state['storage']['page_four_values']['mo_auth_otpoversms_phone'];

  if ( $success_form === TRUE ) {
	 if( $method == $otp_over_sms ) {
	     $message = t('We have sent an one time passcode (OTP) to ' . $phone . '. Enter the OTP received to verify your phone.');
	 } elseif( $method == $otp_over_sms_and_email ) {
		 $message = t('We have sent an one time passcode (OTP) to ' . $phone . ' and ' . $email . '. Enter the OTP received to verify your phone and email.');
	 } elseif ( $method == $otp_over_email ) {
     $message = t('We have sent an one time passcode (OTP) to '.$email .'. Enter the OTP received to verify your email.');
   } elseif( $method == $otp_over_phone_call ) {
         $message = t('You will get a call on '.$phone.' shortly, which prompts one time passcode (OTP). Please enter the OTP to verify your phone number.');
     }
  }

  $message_div_class = $success_form === TRUE ? 'mo2f-message-status' : 'mo2f-message-error';

  $prefix = '<div class="mo2f-modal">
              <div class="mo2f-modal-content">
                <div class="mo2f-modal-container mo2f-modal-header">Configure ' . $authmethod . ' (Step '.getStepNumber(4,5).')</div>
                <div class="mo2f-modal-container"><div class="mo2f-message ' . $message_div_class . '">' . $message . '</div>
  		          <div class="mo2f-info">Enter the passcode:</div>
				<div>';

  $sufix = '</div><div class="mo2f-modal-container mo2f-modal-footer">';
  $sufix .= '<style>#messages div.messages{visibility:hidden;}</style>';

  $form['mo_auth_otpoversms_code'] = array (
    '#type' => 'textfield',
    '#attributes' => array (
      'placeholder' => 'Enter the passcode',
      'class' => array (
        'mo2f-textbox',
        'mo2f-textbox-otp'
      ),
	  '#required' => 'true',
      'autofocus' => 'true'

    ),
    '#prefix' => $prefix,
	'#suffix' => $sufix
  );

  $form['actions'] = array (
    '#type' => 'actions'
  );
  $form['actions']['validate'] = array (
    '#type' => 'submit',
    '#id' => 'page-otp-validate',
    '#value' => t('Validate OTP'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  $form['actions']['cancel'] = array (
    '#type' => 'submit',
    '#id' => 'page-otp-validate-back',
    '#value' => t('Back'),
    '#attributes' => array('class' => array('mo2f_button')),
  );
  return $form;
}

function handle2FAReset(&$form_state){
  global $base_url;
  $storage = $form_state['storage'];
  $phone = isset($storage['page_four_values']['mo_auth_otpoversms_phone'])?$storage['page_four_values']['mo_auth_otpoversms_phone']:NULL;
  $method = $storage['page_three_values']['mo_auth_method'];
  $email = $storage['page_one_values']['mo_auth_user_email'];
  $customer         = new MiniorangeCustomerProfile();
  $is2FAResetRequest = is2FAResetRequest($form_state);

  if( $is2FAResetRequest || backupIsDisabled($form_state) && $method!=AuthenticationType::$KBA['code'] ){
    $miniorange_user  = new MiniorangeUser( $customer->getCustomerID(), $email, $phone, NULL, strpos($method,'AUTHENTICATOR')!==FALSE  ? 'GOOGLE AUTHENTICATOR' : $method );
    // update user info
    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $user_update_response = $user_api_handler->update($miniorange_user);
    if( $user_update_response->status == 'SUCCESS' ) {
      $type = 'status';
      if( AuthenticationType::getAuthType($method)['name'] == 'OTP Over Email') {
          $updateMsg = t('Success! Your 2-Factor Authentication has been successfully ' . (backupIsDisabled() ? 'configured' : 'updated') . ' to send a One Time Passcode (OTP) to your email address for verification upon login.');
      } else {
          $updateMsg = t('Success! Your 2-Factor Authentication has been successfully ' . (backupIsDisabled() ? 'configured' : 'updated') . ' to ' . AuthenticationType::getAuthType($method)['name']);
      }

      $redirectUrl = variable_get('mo_auth_redirect_after_login', $base_url);
     if( $is2FAResetRequest || backupIsDisabled()  ) {
        saveConfigurationInDB($form_state);
        user_login_submit(array (), $form_state);
      }
    }
    else{
      $type='error';
      $updateMsg = 'Facing issues in '.(backupIsDisabled()?'configuring':'updating').' your 2FA method. Please try in your next login.';
      $redirectUrl = backupIsDisabled()?$base_url:variable_get('mo_auth_redirect_after_login', $base_url);
    }
    drupal_set_message($updateMsg,$type,TRUE);
    drupal_goto($redirectUrl);
    exit;
  }
}
function is2FAResetRequest(&$form_state){
  $storage = $form_state['storage'];
  return isset($storage['page_one_values']['mo_2fa_reset']) && $storage['page_one_values']['mo_2fa_reset']===TRUE?TRUE:FALSE;
}
function backupIsDisabled(){
  return variable_get('mo_auth_remove_5th_step','Allowed') == 'Not_Allowed' ;
}

function saveConfigurationInDB(&$form_state,$isKba=FALSE){
  $user = user_load($form_state['uid']);
  $method = $form_state['storage']['page_three_values']['mo_auth_method'];
  $user_email = $form_state['storage']['page_one_values']['mo_auth_user_email'];
  $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'] = $user_email;
  $configured_methods = mo_auth_get_configured_methods($user->uid);

  if($isKba && !in_array(AuthenticationType::$KBA['code'],$configured_methods)){
    array_push($configured_methods,AuthenticationType::$KBA['code']);
  }

  /**
   * Delete all the configured TOTP methods as only one can be used at a time
   */
  $authenticators = array( 'MICROSOFT AUTHENTICATOR', 'GOOGLE AUTHENTICATOR', 'AUTHY AUTHENTICATOR', 'LASTPASS AUTHENTICATOR' );

  $configured_methods = array_values(array_diff( $configured_methods,$authenticators ));
  array_push($configured_methods, $method );
  array_push($configured_methods,AuthenticationType::$EMAIL_VERIFICATION['code']);
  $user->configured_auth_methods[LANGUAGE_NONE] = array();
  $configured_methods = array_unique($configured_methods);

  foreach ($configured_methods as $value){
    array_push($user->configured_auth_methods[LANGUAGE_NONE], array (
      'value' => $value
    ));
  }



  user_save($user);
}

function getStepNumber( $defaultStepNumber,$defaultMaxSteps ) {
  if( backupIsDisabled() )
    $defaultMaxSteps--;
  // user is logged in means he is reconfiguring his 2FA method
  if(user_is_logged_in()){
    $defaultMaxSteps = 2;
    $defaultStepNumber -=2;
  }
  return strval($defaultStepNumber).'/'.strval($defaultMaxSteps);
}

function isFourthPageRequired(){

  $onlySelectedMethod = onlySelectedMethod();
  return !($onlySelectedMethod==AuthenticationType::$EMAIL_VERIFICATION['code'] || $onlySelectedMethod==AuthenticationType::$EMAIL['code']);


}
function isThirdPageRequired(){

  return count(MoAuthUtilities::get_2fa_methods_for_inline_registration(TRUE))>1;
}

function onlySelectedMethod(){
  return array_keys(MoAuthUtilities::get_2fa_methods_for_inline_registration(TRUE))[0];
}
