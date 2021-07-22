<?php

/**
 * @file
 * This file is part of miniOrange 2FA module.
 *
 * The miniOrange 2FA module is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * miniOrange 2FA module is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with miniOrange 2FA module.  If not, see <http://www.gnu.org/licenses/>.
 */

class MoAuthUtilities {

  public static function get_2fa_methods_for_inline_registration( $methods_selected ) {
    if( $methods_selected === TRUE && variable_get('mo_auth_enable_allowed_2fa_methods',FALSE) ) {
      $selected_2fa_methods = json_decode( variable_get('mo_auth_selected_2fa_methods'),TRUE );

      if( is_array($selected_2fa_methods) && !empty( $selected_2fa_methods ) ) {
        return $selected_2fa_methods;
      }
    }

    $options = array(
      AuthenticationType::$EMAIL_VERIFICATION['code']      => AuthenticationType::$EMAIL_VERIFICATION['name'],
      AuthenticationType::$GOOGLE_AUTHENTICATOR['code']    => AuthenticationType::$GOOGLE_AUTHENTICATOR['name'],
      AuthenticationType::$MICROSOFT_AUTHENTICATOR['code']  => AuthenticationType::$MICROSOFT_AUTHENTICATOR['name'],
      AuthenticationType::$AUTHY_AUTHENTICATOR['code']      => AuthenticationType::$AUTHY_AUTHENTICATOR['name'],
      AuthenticationType::$LASTPASS_AUTHENTICATOR['code']   => AuthenticationType::$LASTPASS_AUTHENTICATOR['name'],
      AuthenticationType::$SMS['code']                     => AuthenticationType::$SMS['name'],
      AuthenticationType::$OTP_OVER_EMAIL['code']          => AuthenticationType::$OTP_OVER_EMAIL['name'],
      AuthenticationType::$SMS_AND_EMAIL['code']           => AuthenticationType::$SMS_AND_EMAIL['name'],
      AuthenticationType::$OTP_OVER_PHONE['code']          => AuthenticationType::$OTP_OVER_PHONE['name'],
      AuthenticationType::$KBA['code']                     => AuthenticationType::$KBA['name'],
      AuthenticationType::$QR_CODE['code']                 => AuthenticationType::$QR_CODE['name'],
      AuthenticationType::$PUSH_NOTIFICATIONS['code']      => AuthenticationType::$PUSH_NOTIFICATIONS['name'],
      AuthenticationType::$SOFT_TOKEN['code']              => AuthenticationType::$SOFT_TOKEN['name'],
      /** DO NOT REMOVE OR UNCOMMENT UNTIL THESE FEATURES IMPLEMENTED */
      //AuthenticationType::$HARDWARE_TOKEN['code']          => AuthenticationType::$HARDWARE_TOKEN['name'],
      //AuthenticationType::$OTP_OVER_WHATSAPP['code']     => AuthenticationType::$OTP_OVER_WHATSAPP['name'],
    );

    return $options;
  }

    public static function addSupportForm(&$form, $form_state) {
        drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
        drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

        $form['markup_idp_attr_header_top_support'] = array(
            '#markup' => '<div class="mo2f_table_layout_support_2">',
        );

        $form['markup_support_1'] = array(
            '#markup' => '<div style="font-size:20px;margin-top:10px;margin-bottom:8px;"><b>Support:</b></div></span></h3><div>Need any help? Just send us a query so we can help you.<br /></div>',
        );

        $form['miniorange_saml_email_address_support'] = array(
            '#type' => 'textfield',
            '#attributes' => array('style' => 'width:100%','placeholder' => 'Enter your Email'),
            '#default_value' => variable_get('mo_auth_customer_admin_email', ''),
        );

        $form['miniorange_saml_phone_number_support'] = array(
            '#type' => 'textfield',
            '#id' => 'query_phone',
            '#attributes' => array('class'=>array('query_phone'), 'style' => 'width:100%',),
            '#default_value' => variable_get('mo_auth_customer_admin_phone', ''),
        );

        $form['miniorange_saml_support_query_support'] = array(
            '#type' => 'textarea',
            '#cols' => '10',
            '#rows' => '5',
            '#attributes' => array('style' => 'width:100%','placeholder' => 'Write your query here.'),
        );


        $form['miniorange_saml_support_submit_click'] = array(
            '#type' => 'submit',
            '#value' => t('Submit Query'),
            '#submit' => array('miniorange_2fa_send_query'),
            '#prefix' => '<p style="text-align: center">',
            '#suffix' => '</p>',
            '#limit_validation_errors' => array(),
        );

        $form['miniorange_saml_support_note'] = array(
            '#markup' => '<div>If you want custom features in the module, just drop an email to <a href="mailto:drupalsupport@xecurify.com">drupalsupport@xecurify.com</a></div><br><hr><br>'
        );

        self::faq($form, $form_state);

        $form['miniorange_sp_guide_link_end'] = array(
            '#markup' => '</div>',
        );

    }

    public static function send_support_query( $email, $phone, $query ) {
        if( empty( $email ) || empty( $query ) ){
            drupal_set_message(t('The <b><u>Email</u></b> and <b><u>Query</u></b> fields are mandatory.'), 'error');
            return;
        } elseif( !valid_email_address( $email ) ) {
            drupal_set_message(t('The email address <b><i>' . $email . '</i></b> is not valid.'), 'error');
            return;
        }
        $support = new Miniorange2FASupport($email, $phone, $query);
        $support_response = $support->sendSupportQuery();
        if($support_response) {
            drupal_set_message(t('Your support query has been sent successfully. We will get back to you soon.'));
        }
        else {
            drupal_set_message(t('Error sending support query. Please try again.'), 'error');
        }
    }

    public static function faq(&$form, &$form_state){

        $form['miniorange_2fa_faq'] = array(
            '#markup' => '<div class="mo2f_text_center"><b></b>
                          <a class="mo2f_btn mo2f_btn-primary-faq mo2f_btn_faq_buttons mo_faq_button_left" href="https://faq.miniorange.com/kb/drupal/two-factor-authentication-drupal/" target="_blank">FAQs</a>
                          <b></b><a class="mo2f_btn mo2f_btn-primary-faq mo2f_btn_faq_buttons mo_faq_button_right" href="https://forum.miniorange.com/" target="_blank">Ask questions on forum</a></div>',
        );
    }

    public static function check_roles_to_invoke_2fa( $roles ) {
      $mo_auth_enable_role_based_2fa = variable_get('mo_auth_enable_role_based_2fa');
      $mo_auth_enable_use_only_2nd_factor    = variable_get('mo_auth_two_factor_instead_password');
      if( $mo_auth_enable_role_based_2fa !== TRUE || $mo_auth_enable_use_only_2nd_factor === TRUE ) {
         return TRUE;
      }
      $return_value   = FALSE;
      $selected_roles = ( array ) json_decode( variable_get('mo_auth_role_based_2fa_roles') );
      foreach( $selected_roles as $sysName => $displayName ) {
         if( in_array( $displayName, $roles, TRUE ) ){
           $return_value = TRUE;
           break;
         }
      }
      return $return_value;
    }

    public static function check_domain_to_invoke_2fa( $moUserEmail ) {
      $moUserEmail = strtolower($moUserEmail);
      $mo_auth_enable_domain_based_2fa = variable_get('mo_auth_enable_domain_based_2fa');

      if( $mo_auth_enable_domain_based_2fa != TRUE ) {
        return TRUE;
      }
      $return_value   = FALSE;
      $selected_domains = explode(';', variable_get('mo_auth_two_factor_domain_based_2fa_domains') );
      $moUserDomain = substr( strrchr( $moUserEmail, "@" ), 1 );
      if ( in_array($moUserDomain, $selected_domains ) ) {
        $return_value   = TRUE;
      }
      if($return_value==TRUE){
        $exceptionEmails = variable_get('mo_auth_2fa_domain_exception_emails','');
        $exceptionEmailsArray = explode(";",$exceptionEmails);
        foreach ($exceptionEmailsArray as $key=>$value){
          if( strcasecmp($value,$moUserEmail)==0 ){
            $return_value=FALSE;
            break;
          }
        }
      }
      $whiteOrBlack = variable_get('mo_2fa_domains_are_white_or_black','black')=='white'?FALSE:TRUE;
      return $return_value == $whiteOrBlack ;
    }


    public static function isKbaConfigured($user_configured_array){
        $kba_configured = 0;
        $total = count($user_configured_array);

        for ($i=0; $i < $total ; $i++) {
            if ($user_configured_array[ $i ]['value'] == "KBA")
                $kba_configured = 1;
        }

        return $kba_configured;
    }

    public static function isCurlInstalled() {
        if (in_array('curl', get_loaded_extensions())) {
          return 1;
        } else {
          return 0;
        }
    }

    public static function isCustomerRegistered() {
        if (variable_get('mo_auth_customer_admin_email', NULL) == NULL || variable_get('mo_auth_customer_id', NULL) == NULL || variable_get('mo_auth_customer_token_key', NULL) == NULL || variable_get('mo_auth_customer_api_key', NULL) == NULL) {
          return FALSE;
        }
        return TRUE;
    }

    public static function get_timestamp() {
    $url = MoAuthConstants::getBaseUrl() . '/rest/mobile/get-timestamp';
    $ch = curl_init ( $url );

    curl_setopt ( $ch, CURLOPT_FOLLOWLOCATION, true );
    curl_setopt ( $ch, CURLOPT_ENCODING, "" );
    curl_setopt ( $ch, CURLOPT_RETURNTRANSFER, true );
    curl_setopt ( $ch, CURLOPT_AUTOREFERER, true );
    curl_setopt ( $ch, CURLOPT_SSL_VERIFYPEER, false );
    curl_setopt ( $ch, CURLOPT_SSL_VERIFYHOST, false ); // required for https urls

    curl_setopt ( $ch, CURLOPT_MAXREDIRS, 10 );

    curl_setopt ( $ch, CURLOPT_POST, true );

    $content = curl_exec ( $ch );

    if (curl_errno ( $ch )) {
        echo 'Error in sending curl Request';
        exit ();
    }
    curl_close ( $ch );
    return $content;
    }

    public static function getHiddenEmail($email) {
        $split = explode("@", $email);
        if (count($split) == 2) {
          $hidden_email = substr($split[0], 0, 1) . 'xxxxxx' . substr($split[0], - 1) . '@' . $split[1];
          return $hidden_email;
        }
        return $email;
    }

    public static function indentSecret($secret) {
        $strlen = strlen($secret);
        $indented = '';
        for ($i = 0; $i <= $strlen; $i = $i + 4) {
          $indented .= substr($secret, $i, 4) . ' ';
        }
        $indented = trim($indented);
        return $indented;
    }

    public static function callService($customer_id, $apiKey, $url, $json) {
        if (! self::isCurlInstalled()) {
          return json_encode(array (
            "status" => 'CURL_ERROR',
            "message" => 'PHP cURL extension is not installed or disabled.'
          ));
        }

        $ch = curl_init($url);

        $current_time_in_millis = round(microtime(TRUE) * 1000);

        $string_to_hash = $customer_id . number_format($current_time_in_millis, 0, '', '') . $apiKey;
        $hash_value = hash("sha512", $string_to_hash);

        $customer_key_header = "Customer-Key: " . $customer_id;
        $timestamp_header = "Timestamp: " . number_format($current_time_in_millis, 0, '', '');
        $authorization_header = "Authorization: " . $hash_value;

        curl_setopt($ch, CURLOPT_FOLLOWLOCATION, TRUE);
        curl_setopt($ch, CURLOPT_ENCODING, "");
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, TRUE);
        curl_setopt($ch, CURLOPT_AUTOREFERER, TRUE);
        // Required for https urls.
        curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
        curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
        curl_setopt($ch, CURLOPT_MAXREDIRS, 10);
        curl_setopt($ch, CURLOPT_HTTPHEADER, array (
          "Content-Type: application/json",
          $customer_key_header,
          $timestamp_header,
          $authorization_header
        ));
        curl_setopt($ch, CURLOPT_POST, TRUE);
        curl_setopt($ch, CURLOPT_POSTFIELDS, $json);
        curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 5);
        curl_setopt($ch, CURLOPT_TIMEOUT, 20);
        $content = curl_exec($ch);
        // $httpcode = curl_getinfo($ch, CURLINFO_HTTP_CODE);
        if (curl_errno($ch)) {
          return json_encode(array (
            "status" => 'CURL_ERROR',
            "message" => curl_errno($ch)
          ));
        }
        curl_close($ch);
        return json_decode($content);
    }

  /**
   * Return current URL parts.
   */
  public static function mo_auth_get_url_parts() {
    $query_param = current_path();
    $url_parts   = explode('/', $query_param );
    return $url_parts;
  }

  /**
   * Collect system specific information using JS files
   * @param $username
   */
  public static function mo2f_collect_device_attributes_handler($username ) {
    global $base_url;
    if (empty(session_id())){
      session_start();
    }
    $session_id_encrypt = session_id();
    $module_path = drupal_get_path('module', 'mo_auth');
    ?>
    <!DOCTYPE html>
    <head>
      <?php
      echo '<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.4/jquery.min.js"></script>';
      echo '<script  src="' . $module_path . '/includes/js/rba/js/jquery-1.9.1.js" ></script>';
      echo '<script type="text/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/jquery.flash.js" ></script>';
      ?>
    </head>
    <body>
    <div>
      <form id="morba_loginform"  action="<?php echo $base_url . '/collectattributes';?>" method="post">
        <h1 style="margin-left: 43%; margin-top: 5%;"><?php echo 'Please wait'; ?>...</h1>
        <img style="margin-left: 44%; margin-top: 1%" src="<?php echo $base_url. '/' . $module_path;?>/includes/images/ajax-loader-login.gif" />
        <?php
          ?>
          <p><input type="hidden" id="miniorange_rba_attributes" name="miniorange_rba_attributes" value=""/></p>
          <?php

          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/ua-parser.js" ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/client.js " ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/device_attributes.js" ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/swfobject.js" ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/fontdetect.js" ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/murmurhash3.js" ></script>';
          echo '<script type="application/javascript" src="' . $base_url. '/' . $module_path . '/includes/js/rba/js/miniorange-fp.js" ></script>';
        ?>
        <input type="hidden" name="session_id" value="<?php echo $session_id_encrypt; ?>"/>
        <input type="hidden" name="username" value="<?php echo $username; ?>"/>
      </form>
    </div>
    </body>
    </html>
    <?php
    exit;
  }


  public static function showErrorMessage( $error, $message, $cause, $closeWindow = FALSE ) {
    global $base_url;
    $actionToTakeUponWindow = $closeWindow === TRUE ? 'onClick="self.close();"' : 'href="' . $base_url . '/user/login"';
    echo '<div style="font-family:Calibri;padding:0 3%;">';
    echo '<div style="color: #a94442;background-color: #f2dede;padding: 15px;margin-bottom: 20px;text-align:center;border:1px solid #E6B3B2;font-size:18pt;"> ERROR</div>
                                  <div style="color: #a94442;font-size:14pt; margin-bottom:20px;"><p><strong>Error: </strong>' .  $error  . '</p>
                                      <p>' .  $message  . '</p>
                                      <p><strong>Possible Cause: </strong>' .  $cause  . '</p>
                                  </div>
                                  <div style="margin:3%;display:block;text-align:center;"></div>
                                  <div style="margin:3%;display:block;text-align:center;">
                                      <a style="padding:1%;width:100px;background: #0091CD none repeat scroll 0% 0%;cursor: pointer;font-size:15px;border-width: 1px;border-style: solid;border-radius: 3px;white-space: nowrap;box-sizing: border-box;border-color: #0073AA;box-shadow: 0px 1px 0px rgba(120, 200, 230, 0.6) inset;color: #FFF; text-decoration: none;"type="button"  '.$actionToTakeUponWindow .' >Done</a>
                                  </div>';
    exit;
  }

  /**
   * @param $mo_saved_IP_address = IP Addresses entered by user
   * @return boolean | string if error
   * Check whether provided IP is valid or not
   */
  Public static function check_for_valid_IPs( $mo_saved_IP_address ) {
    /** Separate IP address with the semicolon (;) **/
    $whitelisted_IP_array = explode(";", rtrim( $mo_saved_IP_address, ";") );
    foreach( $whitelisted_IP_array as $key => $value ) {
      if( stristr( $value, '-' ) ) {
        /** Check if it is a range of IP address **/
        list( $lower, $upper ) = explode('-', $value, 2 );
        if ( !filter_var( $lower, FILTER_VALIDATE_IP, FILTER_FLAG_IPV4 ) && !filter_var( $upper, FILTER_VALIDATE_IP, FILTER_FLAG_IPV4 ) ) {
          return "Invalid IP (<strong> ". $lower . "-" . $upper . "</strong> ) address. Please check lower range and upper range.";
        }
        $lower_range = ip2long( $lower );
        $upper_range = ip2long( $upper );
        if ( $lower_range >= $upper_range ){
          return "Invalid IP range (<strong> ". $lower . "-" . $upper . "</strong> ) address. Please enter range in <strong>( lower_range - upper_range )</strong> format.";
        }
      }else {
        /** Check if it is a single IP address **/
        if ( !filter_var( $value, FILTER_VALIDATE_IP, FILTER_FLAG_IPV4 ) ) {
          return " Invalid IP (<strong> ". $value . "</strong> ) address. Please enter valid IP address.";
        }
      }
    }
    return TRUE;
  }


  /**
   * @return bool
   */
  public static function check_white_IPs(){
    $enable_whitelisted_IP = variable_get('mo_auth_two_factor_invoke_2fa_depending_upon_IP', FALSE);
    if( $enable_whitelisted_IP == FALSE ){
      return FALSE;
    }
    $current_IP_address = self::get_client_ip();
    $whitelisted_IP = variable_get('mo_auth_two_factor_whitelist_IP','');
    if( is_null( $whitelisted_IP ) || empty( $whitelisted_IP ) ){
      return FALSE;
    }
    $whitelisted_IP_array = explode(";", $whitelisted_IP );
    $mo_ip_found = FALSE;

    foreach( $whitelisted_IP_array as $key => $value ) {
      if( stristr( $value, '-' ) ){
        /** Search in range of IP address **/
        list($lower, $upper) = explode('-', $value, 2);
        $lower_range = ip2long( $lower );
        $upper_range = ip2long( $upper );
        $current_IP  = ip2long( $current_IP_address );
        if( $lower_range !== FALSE && $upper_range !== FALSE && $current_IP !== FALSE && ( ( $current_IP >= $lower_range ) && ( $current_IP <= $upper_range ) ) ){
          $mo_ip_found = TRUE;
          break;
        }
      }else {
        /** Compare with single IP address **/
        if( $current_IP_address == $value ){
          $mo_ip_found = TRUE;
          break;
        }
      }
    }
    return $mo_ip_found;
  }

  /**
   * @return array|false|string
   * Function to get the client IP address
   */
  static function get_client_ip() {
    $ipaddress = '';
    if (getenv('HTTP_CLIENT_IP'))
      $ipaddress = getenv('HTTP_CLIENT_IP');
    else if(getenv('REMOTE_ADDR'))
      $ipaddress = getenv('REMOTE_ADDR');
    else if(getenv('HTTP_X_FORWARDED_FOR'))
      $ipaddress = getenv('HTTP_X_FORWARDED_FOR');
    else if(getenv('HTTP_X_FORWARDED'))
      $ipaddress = getenv('HTTP_X_FORWARDED');
    else if(getenv('HTTP_FORWARDED_FOR'))
      $ipaddress = getenv('HTTP_FORWARDED_FOR');
    else if(getenv('HTTP_FORWARDED'))
      $ipaddress = getenv('HTTP_FORWARDED');
    else
      $ipaddress = 'UNKNOWN';

    return $ipaddress;
  }

}
