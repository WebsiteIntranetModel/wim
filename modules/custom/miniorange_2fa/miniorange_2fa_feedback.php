<?php


	function miniorange_2fa_feedback()
	{
		If( (isset($_POST['mo_2fa_check'])) && ($_POST['mo_2fa_check'] == "True" ))
		{
			//code to send email alert


			$reason = $_POST['deactivate_plugin'];
			$q_feedback = $_POST['query_feedback'];

            $email = !empty(variable_get('mo_auth_customer_admin_email','')) ? variable_get('mo_auth_customer_admin_email','') : $_POST['miniorange_feedback_email'];

			$message='<br><b>Reason: </b>'.$reason.'<br><b>Feedback: </b>'.$q_feedback;

			$url = 'https://login.xecurify.com/moas/api/notify/send';          //get_option( 'mo2f_host_name' ) . '/moas/api/notify/send';
			$ch = curl_init($url);

			if(valid_email_address($email)) {

                $phone = variable_get('mo_auth_customer_admin_phone', '');
                $customerKey = variable_get('mo_auth_customer_id', '');
                $apikey = variable_get('mo_auth_customer_api_key', '');

                if ($customerKey == '') {
                    $customerKey = "16555";
                    $apikey = "fFd2XcvTGDemZvbw1bcUesNJWEqKbbUq";
                }

                $currentTimeInMillis = get_2fa_timestamp();
                $stringToHash = $customerKey . $currentTimeInMillis . $apikey;
                $hashValue = hash("sha512", $stringToHash);
                $customerKeyHeader = "Customer-Key: " . $customerKey;
                $timestampHeader = "Timestamp: " . $currentTimeInMillis;
                $authorizationHeader = "Authorization: " . $hashValue;
                $fromEmail = $email;
                $query = '[Drupal-7 2FA Module]: ' . $message;

                $content = '<div >Hello, <br><br>Company :<a href="' . $_SERVER['SERVER_NAME'] . '" target="_blank" >' . $_SERVER['SERVER_NAME'] . '</a>
                                         <br><br>Phone Number :' . $phone . '<br><br>Email :<a href="mailto:' . $fromEmail . '" target="_blank">' . $fromEmail . '</a>
                                         <br><br><b>Query: </b>' . $query . '</div>';

                $fields = array(
                    'customerKey' => $customerKey,
                    'sendEmail' => true,
                    'email' => array(
                        'customerKey' => $customerKey,
                        'fromEmail' => $fromEmail,
                        'fromName' => 'miniOrange',
                        'toEmail' => 'drupalsupport@xecurify.com',
                        'toName' => 'drupalsupport@xecurify.com',
                        'subject' => 'Drupal-7 2FA Module Feedback',
                        'content' => $content,
                    ),
                );

                $field_string = json_encode($fields);

                curl_setopt($ch, CURLOPT_FOLLOWLOCATION, true);
                curl_setopt($ch, CURLOPT_ENCODING, "");
                curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
                curl_setopt($ch, CURLOPT_AUTOREFERER, true);
                curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);    # required for https urls
                curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
                curl_setopt($ch, CURLOPT_MAXREDIRS, 10);
                curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: application/json", $customerKeyHeader, $timestampHeader, $authorizationHeader));
                curl_setopt($ch, CURLOPT_POST, true);
                curl_setopt($ch, CURLOPT_POSTFIELDS, $field_string);
                $content = curl_exec($ch);

                if (curl_errno($ch)) {
                    return json_encode(array("status" => 'ERROR', 'statusMessage' => curl_error($ch)));
                }
                curl_close($ch);
            }
		}
		  else if(($_SESSION['mo_other'] == "False"))
		{
            unset($_SESSION['mo_other']);
        $myArray = array();
        $myArray = $_POST;
        $form_id = $_POST['form_id'];
        $form_token = $_POST['form_token'];

        ?>
        <html>
        <head>
            <title>Feedback</title>
            <link href="https://fonts.googleapis.com/css?family=PT+Serif" rel="stylesheet">
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
            <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
            <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>
            <style>
                .2fa_loader {
                    margin: auto;
                    display: block;
                    border: 5px solid #f3f3f3; /* Light grey */
                    border-top: 5px solid #3498db; /* Blue */
                    border-radius: 50%;
                    width: 50px;
                    height: 50px;
                    animation: spin 2s linear infinite;
                }

                @keyframes spin {
                    0% {
                        transform: rotate(0deg);
                    }
                    100% {
                        transform: rotate(360deg);
                    }
                }
            </style>
            <script type="text/javascript">
                $(document).ready(function () {
                    if(document.getElementById('miniorange_feedback_email').value == '') {
                        document.getElementById('email_error').style.display = "block";
                        document.getElementById('submit_button').disabled = true;
                    }
                    $("#myModal").modal({
                        backdrop: 'static',
                        keyboard: false
                    });
                    $('.button').click(function () {
                        document.getElementById('2fa_loader').style.display = 'block';
                    });
                });

                function validateEmail(emailField) {
                    var reg = /^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/;

                    if (reg.test(emailField.value) == false) {
                        document.getElementById('email_error').style.display = "block";
                        document.getElementById('submit_button').disabled = true;
                    } else {
                        document.getElementById('email_error').style.display = "none";
                        document.getElementById('submit_button').disabled = false;
                    }
                }
            </script>
        </head>
        <body>
        <div class="container">
            <div class="modal fade" id="myModal" role="dialog" style="background: rgba(0,0,0,0.1);">
                <div class="modal-dialog" style="width: 500px;">
                    <div class="modal-content" style="border-radius: 20px;">
                        <div class="modal-header"
                             style="padding: 25px; border-top-left-radius: 20px; border-top-right-radius: 20px; background-color: #8fc1e3;">
                            <h4 class="modal-title" style="color: white; text-align: center;">
                                Hey, it seems like you want to deactivate miniOrange Two Factor Authentication Module
                            </h4>
                            <hr>
                            <h4 style="text-align: center; color: white;">What happened?</h4>
                        </div>
                        <div class="modal-body"
                             style="font-size: 11px; padding-left: 25px; padding-right: 25px; border-bottom-left-radius: 20px; border-bottom-right-radius: 20px; background-color: #ececec;">
                            <form name="f" method="post" action="" id="mo_feedback">
                                <div>
                                    <p>

                                        <br>Email: <input onblur="validateEmail(this)" class="form-control" type="email"
                                                          id="miniorange_feedback_email"
                                                          name="miniorange_feedback_email"/>
                                    <p style="display: none;color:red" id="email_error">Invalid Email</p>

                                    <br>
                                    <?php
                                    $deactivate_reasons = array(
                                        "Not Working",
                                        "Not receiving OTP during registration",
                                        "Does not have the features I'm looking for",
                                        "Redirecting back to login page after Authentication",
                                        "Confusing interface",
                                        "Bugs in the plugin",
                                        "Other reasons: "
                                    );
                                    foreach ($deactivate_reasons as $deactivate_reasons) {
                                        ?>
                                        <div class="radio" style="vertical-align: middle;">
                                            <label for="<?php echo $deactivate_reasons; ?>">
                                                <input type="radio" name="deactivate_plugin" id="deactivate_plugin"
                                                       value="<?php echo $deactivate_reasons; ?>" required>
                                                <?php echo $deactivate_reasons; ?>
                                            </label>
                                        </div>
                                    <?php } ?>
                                    <input type="hidden" name="mo_2fa_check" value="True">
                                    <input type="hidden" name="form_token" value=<?php echo $form_token ?>>
                                    <input type="hidden" name="form_id" value= <?php echo $form_id ?>>
                                    <br>
                                    <textarea class="form-control" id="query_feedback" name="query_feedback" rows="4"
                                              cols="50" placeholder="Write your query here"></textarea>
                                    <br><br>
                                    <div class="mo2f_modal-footer">
                                        <input type="submit" id="submit_button" name="miniorange_feedback_submit"
                                               class="button btn btn-primary" value="Submit and Continue"
                                               style="margin: auto; display: block; font-size: 11px;"/><br>
                                        <div class="2fa_loader" id="2fa_loader" style="display: none;"></div>
                                    </div>
                                    <?php
                                    foreach ($_POST as $key => $value) {
                                        hidden_2fa_Fields($key, $value);
                                    }
                                    ?>
                                    </p>
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        </body>
        </html>

        <?php

        exit;
		}
	}


	function hidden_2fa_Fields($key,$value)
	{
		$hidden_2fa_Field = "";
        $value2 = array();
        if(is_array($value)) {
            foreach($value as $key2 => $value2)
            {
                if(is_array($value2)){
                    hidden_2fa_Fields($key."[".$key2."]",$value2);
                } else {
                    $hidden_2fa_Field = "<input type='hidden' name='".$key."[".$key2."]"."' value='".$value2."'>";
                }
            }
        }else{
            $hidden_2fa_Field = "<input type='hidden' name='".$key."' value='".$value."'>";
        }

		echo $hidden_2fa_Field;
	}


	function get_2fa_timestamp() {
		$url = 'https://login.xecurify.com/moas/rest/mobile/get-timestamp';
		$ch  = curl_init( $url );

		curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, true );
		curl_setopt( $ch, CURLOPT_ENCODING, "" );
		curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
		curl_setopt( $ch, CURLOPT_AUTOREFERER, true );
		curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );
		curl_setopt( $ch, CURLOPT_SSL_VERIFYHOST, false ); // required for https urls

		curl_setopt( $ch, CURLOPT_MAXREDIRS, 10 );

		curl_setopt( $ch, CURLOPT_POST, true );

		if ( defined( 'WP_PROXY_HOST' ) && defined( 'WP_PROXY_PORT' ) && defined( 'WP_PROXY_USERNAME' ) && defined( 'WP_PROXY_PASSWORD' ) ) {
			curl_setopt( $ch, CURLOPT_PROXY, WP_PROXY_HOST );
			curl_setopt( $ch, CURLOPT_PROXYPORT, WP_PROXY_PORT );
			curl_setopt( $ch, CURLOPT_HTTPAUTH, CURLAUTH_BASIC );
			curl_setopt( $ch, CURLOPT_PROXYUSERPWD, WP_PROXY_USERNAME . ':' . WP_PROXY_PASSWORD );
		}

		$content = curl_exec( $ch );

		if ( curl_errno( $ch ) ) {
			echo 'Error in sending curl Request';
			exit ();
		}
		curl_close( $ch );

		if(empty( $content )){
			$currentTimeInMillis = round( microtime( true ) * 1000 );
			$currentTimeInMillis = number_format( $currentTimeInMillis, 0, '', '' );
		}
		return empty( $content ) ? $currentTimeInMillis : $content;
}