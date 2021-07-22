<?php

function mo_auth_configure_kba($form, &$form_state) {
  global $base_url, $user;
  $user = user_load($user->uid);

  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  // $response = $auth_api_handler->getGoogleAuthSecret($miniorange_user);
  // $qrCode = $response->qrCodeData;
  // $secret = $response->secret;

  $form['header']['#markup'] = '<div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Configure Security Questions (KBA)</div></div>'
      . mo_auth_create_form($base_url);

  $form['actions'] = array('#type' => 'actions');

  $form['actions']['verifyphone'] = array(
      '#type' => 'verifyphone',
      '#value' => t('Verify'),
  );

  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  $form['actions']['cancel'] = array(
      '#markup' => l(t('Cancel'), 'admin/config/people/mo_auth/setup'),
  );
  return $form;
}

function mo_auth_configure_kba_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  global $base_url, $user;

  $user = user_load($user->uid);
  $user_email = $user->miniorange_registered_email[LANGUAGE_NONE][0]['value'];
  $ques1 = $form_state['input']['mo2f_kbaquestion1'];
  $ans1 = $form_state['input']['mo2f_kbaanswer1'];

  $ques2 = $form_state['input']['mo2f_kbaquestion2'];
  $ans2 = $form_state['input']['mo2f_kbaanswer2'];

  $ques3 = $form_state['input']['mo2f_kbaquestion3'];
  $ans3 = $form_state['input']['mo2f_kbaanswer3'];

  if($ques1 == $ques2 || $ques1 == $ques3 || $ques2 == $ques3) {
  	form_set_error('configuration', t('The questions you select must not be same.'));
  	return;
  }
  $qa1 = array(
  	"question" => $ques1,
  	"answer" => $ans1,
  );

  $qa2 = array(
  	"question" => $ques2,
  	"answer" => $ans2,
  );

  $qa3 = array(
  	"question" => $ques3,
  	"answer" => $ans3,
  );

  $kba = array($qa1, $qa2, $qa3);

  $customer = new MiniorangeCustomerProfile();
  $miniorange_user = new MiniorangeUser($customer->getCustomerID(), $user_email, NULL, NULL, AuthenticationType::$KBA['code']);
  $auth_api_handler = new AuthenticationAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
  $response = $auth_api_handler->register($miniorange_user, AuthenticationType::$KBA['code'], NULL, NULL, $kba);

  // Clear all the messages
  drupal_get_messages();
  // read API response
  if ($response->status == 'SUCCESS') {
    drupal_set_message(t(''), 'status');
    $configured_methods = mo_auth_get_configured_methods($user->uid);
    // $configured_methods[] = AuthenticationType::$GOOGLE_AUTHENTICATOR['code'];
    // $user->configured_auth_methods[LANGUAGE_NONE][0]['value'] = $configured_methods;

    if (! in_array(AuthenticationType::$KBA['code'], $configured_methods)) {
      array_push($user->configured_auth_methods[LANGUAGE_NONE], array('value' => AuthenticationType::$KBA['code']));
    }

    $user_api_handler = new UsersAPIHandler($customer->getCustomerID(), $customer->getAPIKey());
    $response = $user_api_handler->update($miniorange_user);
    if ($response->status == 'SUCCESS') {
      user_save($user);
      drupal_goto('admin/config/people/mo_auth/setup');
    }
  } elseif ($response->status == 'FAILED') {
    form_set_error('form' , t('The passcode you have entered is incorrect. Please try again.'));
    // $form_state['redirect'] = FALSE;
    // drupal_goto('admin/config/people/mo_auth/setup-twofactor');
  } else {
    form_set_error('form' , t('An error occured while processing your request. Please try again.'));
    watchdog('miniorange_2fa', $response->message);
    // drupal_goto('admin/config/people/mo_auth/setup-twofactor');
  }
}

function mo_auth_create_form($base_url) {
  $form = '<div class="mo2f-info">Please choose 3 questions:</div>
  			<div class="mo2f-kba-header mo2f-kba-row">
  			<div class="mo2f-kba-srno">Sr. No.</div>
  			<div class="mo2f-kba-question">Questions</div>
			<div class="mo2f-kba-answer">Answers</div>
  			</div>
  			<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">1.</div>
  			<div class="mo2f-kba-question">
  				<select name="mo2f_kbaquestion1" id="mo2f_kbaquestion1" class="form-control form-select" required="true">
							<option value="" selected="selected">-------------------------Select your question-------------------------</option>
							<option id="mq1_1" value="What is your first company name?">What is your first company name?</option>
							<option id="mq2_1" value="What was your childhood nickname?">What was your childhood nickname?</option>
							<option id="mq3_1" value="In what city did you meet your spouse/significant other?">In what city did you meet your spouse/significant other?</option>
							<option id="mq4_1" value="What is the name of your favorite childhood friend?">What is the name of your favorite childhood friend?</option>
							<option id="mq5_1" value="What school did you attend for sixth grade?">What school did you attend for sixth grade?</option>
							<option id="mq6_1" value="In what city or town was your first job?">In what city or town was your first job?</option>
							<option id="mq7_1" value="What is your favourite sport?">What is your favourite sport?</option>
							<option id="mq8_1" value="Who is your favourite sports player?">Who is your favourite sports player?</option>
							<option id="mq9_1" value="What is your grandmother&#39;s maiden name?">What is your grandmother&#39;s maiden name?</option>
							<option id="mq10_1" value="What was your first vehicle&#39;s registration number?">What was your first vehicle&#39;s registration number?</option>
						</select>
  			</div>
			<div class="mo2f-kba-answer"><input class="form-control form-text" type="text" name="mo2f_kbaanswer1" id="mo2f_kba_ans1" title="Only alphanumeric letters with special characters(_@.$#&amp;+-) are allowed." pattern="(?=\S)[A-Za-z0-9_@.$#&amp;+-\s]{1,100}" required="true" autofocus="true" placeholder="Enter your answer"></div>
  		</div>
  		<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">2.</div>
  			<div class="mo2f-kba-question">
  				<select name="mo2f_kbaquestion2" id="mo2f_kbaquestion2" class="form-control form-select" required="true">
							<option value="" selected="selected">-------------------------Select your question-------------------------</option>
							<option id="mq1_2" value="What is your first company name?">What is your first company name?</option>
							<option id="mq2_2" value="What was your childhood nickname?">What was your childhood nickname?</option>
							<option id="mq3_2" value="In what city did you meet your spouse/significant other?">In what city did you meet your spouse/significant other?</option>
							<option id="mq4_2" value="What is the name of your favorite childhood friend?">What is the name of your favorite childhood friend?</option>
							<option id="mq5_2" value="What school did you attend for sixth grade?">What school did you attend for sixth grade?</option>
							<option id="mq6_2" value="In what city or town was your first job?">In what city or town was your first job?</option>
							<option id="mq7_2" value="What is your favourite sport?">What is your favourite sport?</option>
							<option id="mq8_2" value="Who is your favourite sports player?">Who is your favourite sports player?</option>
							<option id="mq9_2" value="What is your grandmother&#39;s maiden name?">What is your grandmother&#39;s maiden name?</option>
							<option id="mq10_2" value="What was your first vehicle&#39;s registration number?">What was your first vehicle&#39;s registration number?</option>
						</select>
  			</div>
			<div class="mo2f-kba-answer"><input class="form-control form-text" type="text" name="mo2f_kbaanswer2" id="mo2f_kba_ans2" title="Only alphanumeric letters with special characters(_@.$#&amp;+-) are allowed." pattern="(?=\S)[A-Za-z0-9_@.$#&amp;+-\s]{1,100}" required="true" autofocus="true" placeholder="Enter your answer"></div>
  		</div>
  		<div class="mo2f-kba-row">
  			<div class="mo2f-kba-srno">3.</div>
  			<div class="mo2f-kba-question">
  				<input type="text" class="form-control form-text" name="mo2f_kbaquestion3" id="mo2f_kbaquestion_3" class="form-control form-select" required="true" />
  			</div>
			<div class="mo2f-kba-answer"><input class="form-control form-text" type="text" name="mo2f_kbaanswer3" id="mo2f_kba_ans2" title="Only alphanumeric letters with special characters(_@.$#&amp;+-) are allowed." pattern="(?=\S)[A-Za-z0-9_@.$#&amp;+-\s]{1,100}" required="true" autofocus="true" placeholder="Enter your answer"></div>
  		</div>';
  return $form;
}
