<?php

/**
 * @file
 * Email verification functions.
 */

/**
 * Menu callback for email verification.
 */
function mo_auth_test_kba_authentication($form, &$form_state) {
  global $base_url, $user;
  $user = user_load($user->uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];

  $questions = NULL;
  $count = 0;
  $txId = '';
  if (array_key_exists('txId', $form_state['input']) === FALSE) {
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$KBA['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->challenge($miniorange_user);

    if ($response->status == 'SUCCESS') {
  	  $questions = $response->questions;
  	  $count = count($response->questions);
  	  $txId = $response->txId;
    } else {
      drupal_set_message(t('An error occured while processing your request. Please Try again.'), 'error');
      watchdog('miniorange_2fa', $response->message);
      drupal_goto('admin/config/people/mo_auth/setup');
    }
  } else {
  	$count = $form_state['input']['question_count'];
  	$questions = array();
  	for ($i = 1; $i<=$count; $i++) {
  		$ques = $form_state['input']['mo2f_kbaquestion' . $i];
  		$ans = $form_state['input']['mo2f_kbaanswer' . $i];
  		$qa = NULL;
  		$qa->question = $ques;
  		$qa->answer = $ans;
  		array_push($questions, $qa);
  	}
  }
  $form['header']['#markup'] = t('<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Test Security Questions (KBA)</div></div><div class="mo2f-info">Please answer the following questions:</div>');
  $form = mo_auth_create_form($form, $questions);
  $form['txId'] = array(
  	'#type' => 'hidden',
  	'#value' => $txId,
  );
  $form['question_count'] = array(
  	'#type' => 'hidden',
  	'#value' => $count,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
  	'#type' => 'submit',
  	'#value' => t('Verify'),
  );
  $form['actions']['cancel'] = array(
  	'#markup' => l(t('Cancel Test'), 'admin/config/people/mo_auth/setup'),
  	'#suffix' => '</div>',
  );
  return $form;
}

/**
 * Form submit handler for email verify.
 */
function mo_auth_test_kba_authentication_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  global $base_url, $user;
  $user = user_load($user->uid);

  $txId = $form_state['input']['txId'];
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  $count = $form_state['input']['question_count'];
  $kba = array();
  for ($i = 1; $i<=$count; $i++) {
  	$ques = $form_state['input']['mo2f_kbaquestion' . $i];
  	$ans = $form_state['input']['mo2f_kbaanswer' . $i];
  	$qa = array(
  	  "question" => $ques,
  	  "answer" => $ans,
  	);
  	array_push($kba, $qa);
  }

  if (count($kba) > 0) {
    $customer = new MiniorangeCustomerProfile();
    $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$KBA['code']);
    $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $auth_api_handler->validate($miniorange_user, $txId, NULL, $kba);

    // Clear all the messages
    drupal_get_messages();

    // read API response
    if ($response->status == 'SUCCESS') {
      drupal_set_message(t('You have successfully completed the test.'), 'status');
      drupal_goto('admin/config/people/mo_auth/setup');
    } elseif ($response->status == 'FAILED') {
      form_set_error('form' , t('The answers you have entered are incorrect. Please try again.'));
      return;
    }
  }
  drupal_set_message(t('An error occured while processing your request. Please try again.'), 'error');
  watchdog('miniorange_2fa', $response->message);
  drupal_goto('admin/config/people/mo_auth/setup');
}

function mo_auth_create_form($form, $questions) {
	$form['header']['#markup'] .= '<div class="mo2f-kba-header mo2f-kba-row">
  			<div class="mo2f-kba-srno">Sr. No.</div>
  			<div class="mo2f-kba-question">Questions</div>
			<div class="mo2f-kba-answer">Answers</div>
  			</div>';
	$i = 0;
	foreach ($questions as $ques) {
	  $i++;
	  $form['header']['#markup'] .= '<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">' . $i . '.</div>
  			<div class="mo2f-kba-question">'
  				. $ques->question .
  			'</div>
			<div class="mo2f-kba-answer"><input class="form-control form-text" type="text" name="mo2f_kbaanswer' . $i . '" title="Only alphanumeric letters with special characters(_@.$#&amp;+-) are allowed." pattern="(?=\S)[A-Za-z0-9_@.$#&amp;+-\s]{1,100}" required="true" autofocus="true" placeholder="Enter your answer"></div>
  		<input type="hidden" name="mo2f_kbaquestion' . $i .'" value="' . $ques->question . '"/></div>';
	}
	return $form;
}
