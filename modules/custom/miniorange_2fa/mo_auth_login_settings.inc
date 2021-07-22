<?php
/**
 * @file
 * Contains support form for miniOrange 2FA Login Module.
 */

 /**
 * Showing Support form info.
 */
 function mo_auth_login_settings($form, &$form_state) {
  global $base_url;
  $register_url = $base_url . '/admin/config/people/mo_auth/';
  $disabled = FALSE;
  if ( !MoAuthUtilities::isCustomerRegistered() ) {
    $disabled=TRUE;
    $form['header'] = array(
      '#markup' => '<div class="mo2f_configure_message">You need to <a href="'.$register_url.'" >Register/Login</a> using miniOrange account before using this module.</div>',
    );
  }

  $form['header_top_style_1'] = array(
 	'#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container">'
  );

  $loginSettings = new MoAuthLoginSettings();

  $form['mo_auth_enable_two_factor'] = array(
  	'#type' => 'checkbox',
  	'#value' => $loginSettings->getEnable2Factor(),
  	'#prefix' => '<div><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Enable Two-Factor module</div></div><div class="mo2f-info">',
  	'#suffix' => '</div></div>',
  	'#title' => t('Enable Two-Factor plugin. <span class="mo2f_red_color_star">(<strong>If you disable this checkbox, Two-Factor authentication will not be invoked for any user during login.</strong>)</span>'),
    '#disabled'=> $disabled,
  );

   $form['mo_auth_redirect_user_after_login'] = array(
     '#type' => 'textfield',
     '#default_value' => variable_get('mo_auth_redirect_after_login', ''),
     '#attributes' => array('style' => 'width:700px', 'placeholder' => 'Enter the redirect URL'),
     '#description' => t('<strong>Note: </strong>Enter the entire URL (<em> including https:// </em>) where you want to redirect user after login.'),
     '#disabled' => $disabled,
     '#prefix' => '<br><br><div><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Redirect user after login</div>
        <div style="float:right;display:inline-block;color:#0073aa;"></div></div><div>',
     '#suffix' => '</div></div>',
   );

  $license_type = variable_get('mo_auth_2fa_license_type', 'DEMO');
  $is_free = $license_type == 'PREMIUM' || $license_type == 'DRUPAL_2FA_PLUGIN' ? FALSE : TRUE;

  $is_free_class = $is_free ? " mo2f-grayed-out" : "";
  $form['mo_auth_enforce_inline_registration'] = array(
  	'#type' => 'checkbox',
  	'#value' => $loginSettings->getEnforceInlineRegistration(),
  	'#prefix' => '<br><br><div><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Invoke Inline Registration to setup 2nd factor for users</div>
        <div style="float:right;display:inline-block;color:#0073aa;"><a href="?q=admin/config/people/mo_auth/licensing"><b>PREMIUM</b></a></div></div><div class="mo2f-info ' . $is_free_class . '">',
  	'#suffix' => '</div></div>',
  	'#disabled' => $is_free,
  	'#title' => t('Enforce 2 Factor registration for users at login time.'),
    '#description' => t('<strong>Note:</strong> If second factor is not setup for the user trying to login, he will be asked to setup before login.'),
    '#states' => array(
    // Only enable this field when the 'mo_auth_enable_two_factor' checkbox is checked.
      'enabled' => array(
        ':input[name="mo_auth_enable_two_factor"]' => array(
          'checked' => TRUE && !$is_free,
        ),
      ),
    ),
  );

  $form['mo_auth_make_email_editable'] = array(
    '#type' => 'checkbox',
    '#default_value' => variable_get('mo_auth_make_email_editable', false),
    '#title' => t('Make email editable in inline registration flow.'),
    '#description' => t('<strong>Note:</strong> User can edit the email while registering for 2FA, this email may be different from the one used for registering on the site.'),
    '#disabled' => $is_free,
    '#states' => array(
      // Only enable this field when the 'mo_auth_enable_two_factor' checkbox is checked.
      'enabled' => array(
        ':input[name="mo_auth_enable_two_factor"]' => array(
          'checked' => TRUE && !$is_free,
        ),
      ),
    ),
  );

     $form['markup_idp_login_note'] = array(
         '#markup' => '<br><br><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Select Login Screen Options</div><div style="float:right;display:inline-block;color:#0073aa;"><a href="?q=admin/config/people/mo_auth/licensing"><b>PREMIUM</b></a></div></div><div class="mo2f-info ' . $is_free_class . '"><div class="mo2f-info">
                    <div class="mo2f_highlight_background_note"><b>Note: </b>By default 2nd Factor is enabled after password authentication.
            If you do not want to remember passwords anymore and just login with 2nd Factor, please select below option.</div></br>',
     );

  $form['mo_auth_two_factor_instead_password'] = array(
    '#type' => 'checkbox',
    '#value' => $loginSettings->getEnableOTPinsteadPassword(),
    '#prefix' => '',
    '#suffix' => '</div></div>',
    '#disabled' => $is_free,
    '#title' => t('Login with 2nd Factor only (<b>No password required.</b>)'),
    '#description' => 'NOTE: To use this feature make sure you have enabled the "ENFORCE 2 FACTOR REGISTRATION FOR USERS AT LOGIN TIME" feature.',
    '#states' => array(
    // Only enable this field when the 'mo_auth_enable_two_factor' checkbox is checked.
      'enabled' => array(
        ':input[name="mo_auth_enable_two_factor"]' => array(
          'checked' => TRUE && !$is_free,
        ),
      ),
    ),
  );

   /**
    * Role base 2FA
    */

   $form['mo_auth_two_factor_enable_role_based_2fa'] = array(
     '#type' => 'checkbox',
     '#default_value' => variable_get('mo_auth_enable_role_based_2fa', FALSE),
     '#prefix' => '<br><br><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Role based 2FA</div><div style="float:right;display:inline-block;color:#0073aa;"><a href="?q=admin/config/people/mo_auth/licensing"><b>PREMIUM</b></a></div></div><div class="mo2f-info ' . $is_free_class . '"><div class="mo2f-info">
                   <div class="mo2f_highlight_background_note"><b>Note: </b>If you have enabled "LOGIN WITH 2ND FACTOR ONLY" feature, Second-Factor authentication will invoke for all roles.</div></br>',
     '#disabled' => $is_free,
     '#title' => t('Enable role based 2FA'),
     '#description' => "<strong>Note:</strong> If you want to enable 2FA for specific roles then, enable this checkbox and select appropriate roles.</br>",
   );

   $roles_arr      =  user_roles($membersonly = TRUE); //MoAuthUtilities::get_Existing_Drupal_Roles();
   $selected_roles = ( array ) json_decode( variable_get('mo_auth_role_based_2fa_roles', '') );

   foreach( $roles_arr as $sysName => $displayName ) {
     $form['mo_auth_two_factor_role_based_2fa_roles_' . strtolower($sysName)] = array(
       '#type' => 'checkbox',
       '#default_value' => array_key_exists( $sysName, $selected_roles )? TRUE : FALSE,
       '#states' => array(
         // Only show this field when the checkbox is enabled.
         'visible' => array(
           ':input[name="mo_auth_two_factor_enable_role_based_2fa"]' => array('checked' => TRUE),
         ),
       ),
       '#title' => t($displayName),
     );
   }

   /**
    * Domain base 2FA
    */
   $form['mo_auth_two_factor_enable_domain_based_2fa'] = array(
     '#type' => 'checkbox',
     '#default_value' => variable_get('mo_auth_enable_domain_based_2fa', FALSE),
     '#prefix' => '<br><br><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Domain based 2FA</div><div style="float:right;display:inline-block;color:#0073aa;">
                   <a href="?q=admin/config/people/mo_auth/licensing"><b>PREMIUM</b></a></div></div><div class="mo2f-info ' . $is_free_class . '"><div class="mo2f-info">',
     '#disabled' => $is_free,
     '#title' => t('Enable domain based 2FA'),
    // '#description' => "<strong>Note:</strong> If you want to enable 2FA for specific domains then, enable this checkbox and add domains below.</br>",
   );
   $form['mo_2fa_domain_fieldset'] = array(
     '#type' => 'fieldset',
     '#states' => array(
       // Only show this field when the checkbox is enabled.
       'visible' => array(
         ':input[name="mo_auth_two_factor_enable_domain_based_2fa"]' => array('checked' => TRUE),
       ),
     ),
   );


   $form['mo_2fa_domain_fieldset']['mo_auth_two_factor_domain_based_2fa_domains'] = array(
     '#type' => 'textarea',
     '#attributes' => array('placeholder' => 'Enter semicolon(;) separated domains eg. xxx.com;xxx.com;xxx.com'),
     '#default_value' => variable_get('mo_auth_two_factor_domain_based_2fa_domains', ''),
   );

   $form['mo_2fa_domain_fieldset']['mo_2fa_allow_or_block_domains']=array(
     '#type'=>'radios',
     '#maxlength' => 5,
     '#options' => array(  'black' => 'I want to enable 2FA for only listed domains','white' => 'I want to disable 2FA for listed domains'),
     '#default_value'=>variable_get('mo_2fa_domains_are_white_or_black','black'),
   );
   $form['mo_2fa_domain_fieldset']['mo_auth_2fa_domain_exception_emails'] = array(
     '#type' => 'textarea',
     '#title'=>'You can add some exception emails for this domain based rule.',
     '#attributes' => array('placeholder' => 'Enter semicolon(;) separated emails eg. person@xxx.com;person1@xxx.com;'),
     '#default_value' => variable_get('mo_auth_2fa_domain_exception_emails', ''),
     '#description' => "<strong>Note:</strong>Enter semicolon(;) separated emails eg. person@xxx.com;person1@xxx.com, emails listed here will be considered as exception of domain based 2FA rule.</br>",
   );

   /**
    * Password complexity
    *
    */
   $form['mo_auth_enable_password_checks'] = array(
     '#type' => 'checkbox',
     '#default_value' => variable_get('mo_auth_enable_password_checks', FALSE),
     '#prefix' => '<br><br><div class="mo2f-setup-header"><div class="mo2f-setup-header-top-left">Password complexity rules</div><div style="float:right;display:inline-block;color:#0073aa;">
                   <a href="?q=admin/config/people/mo_auth/licensing"><b>PREMIUM</b></a></div></div>',
     '#disabled' => $is_free,
     '#title' => t('Enable password complexity rules'),
   );
   $form['mo_2fa_password_check_fieldset'] = array(
     '#type' => 'fieldset',
     '#states' => array(
       // Only show this field when the checkbox is enabled.
       'visible' => array(
         ':input[name="mo_auth_enable_password_checks"]' => array('checked' => TRUE),
       ),
     ),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_unique_password'] = array(
     '#type' => 'textfield',
     '#attributes' => array(
       ' type' => 'number', 'min'=>0,'max'=>50
     ),
     '#default_value'=> variable_get( 'mo_2fa_unique_password', 1 ),
     '#maxlength' => 2,
     '#title'=>t('The new password should not be same as last ' . variable_get( 'mo_2fa_unique_password', 1 ) . ' passwords.'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_min_length'] = array(
     '#type' => 'textfield',
     '#attributes' => array(
       ' type' => 'number', 'min'=>5,'max'=>50
     ),
     '#default_value'=>$loginSettings->getPasswordMinLength(),
     '#maxlength' => 2,
     '#title'=>t('Minimum length of password:'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_max_length'] = array(
     '#type' => 'textfield',
     '#attributes' => array(
       ' type' => 'number', 'min'=>5,'max'=>50
     ),
     '#default_value'=>$loginSettings->getPasswordMaxLength(),
     '#maxlength' => 2,
     '#title'=>t('Maximum length of password:'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_password_variation_up_char'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustHaveUpChar(),
     '#title'=>t('At least one upper case letter  '),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_password_variation_low_char'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustHaveLowChar(),
     '#title'=>t('At least one lower case letter '),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_password_variation_num_char'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustHaveNumChar(),
     '#title'=>t('At least one numerical letter'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_password_variation_special_char'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustHaveSpecialChar(),
     '#title'=>t('At least one special character ( symbol ) '),
   );

   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_must_not_be_email'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustNotBeEmail(),
     '#title'=>t('Password should not be the same as username or email'),
   );

   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_must_not_be_firstname'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustNotBeFname(),
     '#title'=>t('Password should not be the same as first name'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_must_not_be_fname_text'] = array(
     '#type' => 'textfield',
     '#default_value'=>$loginSettings->getMachineNameOfFname(),
     '#states' => array(
       // Only show this field when the checkbox is enabled.
       'visible' => array(
         ':input[name="mo_2fa_password_must_not_be_firstname"]' => array('checked' => TRUE),
       ),
     ),
     '#title'=>t('Machine name of first name'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_must_not_lastname'] = array(
     '#type' => 'checkbox',
     '#default_value'=>$loginSettings->getPasswordMustNotBeLname(),
     '#title'=>t('Password should not be the same as last name'),
   );
   $form['mo_2fa_password_check_fieldset']['mo_2fa_password_must_not_be_lname_text'] = array(
     '#type' => 'textfield',
     '#default_value'=>$loginSettings->getMachineNameOfLname(),
     '#states' => array(
       // Only show this field when the checkbox is enabled.
       'visible' => array(
         ':input[name="mo_2fa_password_must_not_lastname"]' => array('checked' => TRUE),
       ),
     ),
     '#title'=>t('Machine name of last name'),
   );


   /**
    * Create container to hold @WhitelistIPAddresses form elements.
    */
   $form['mo_2fa_whitelist_ip_details']=array(
     '#markup'=>'<br><br><hr><details><summary class="mo_tfa_summary" >Whitelist IP addresses</summary><br><hr>'
   );

   $form['mo_auth_two_factor_invoke_2fa_depending_upon_IP'] = array(
     '#type' => 'checkbox',
     '#default_value' => variable_get('mo_auth_two_factor_invoke_2fa_depending_upon_IP', ''),
     '#prefix' => t('<hr>'),
     '#disabled' => $is_free,
     '#title' => t('Whitelist IP addresses'),
     '#description' => t('<strong>Note:</strong> If you whitelist the IPs then second factor authentication will not be invoked for those IPs.'),
   );

   $form['mo_auth_two_factor_whitelist_IP'] = array(
     '#type' => 'textarea',
     '#default_value' => variable_get('mo_auth_two_factor_whitelist_IP', ''),
     '#disabled' => $is_free,
     '#attributes' => array('placeholder' => t('Enter semicolon(;) separated IP addresses ( Format for range: lower_range - upper_range )'),),
     '#states' => array('disabled' => array(':input[name = "mo_auth_two_factor_invoke_2fa_depending_upon_IP"]' => array('checked' => FALSE ), ),),
     '#suffix' => '<br>',
   );

   $form['m_2fa_whitelist_ip_end_details']=array(
     '#markup'=>'</details>'
   );

   /**
    * Allow only specific 2FA methods
    */
   $form['mo_2fa_details']=array(
     '#markup'=>'<details ><summary class="mo_tfa_summary" >ALLOW SPECIFIC 2FA METHODS TO CONFIGURE</summary><br><hr>'
   );
   $form['mo_auth_two_factor_enable_specific_2fa_methods'] = array(
     '#type' => 'checkbox',
     '#default_value' => variable_get('mo_auth_enable_allowed_2fa_methods', FALSE),
     //'#prefix' => t('<hr><br><div class="mo_2fa_highlight_background_note"><strong>Note: </strong>To use this feature make sure you have enabled the "<u>ENFORCE 2 FACTOR REGISTRATION FOR USERS AT LOGIN TIME</u>" feature.</div>'),
     '#disabled' => $is_free,
     '#title' => t('Enable allow specific 2Fa'),
     '#description' => t('<strong>Note:</strong> If you want to allow only specific 2FA methods to be configured by users while inline 2fa setup then, enable this checkbox and select appropriate 2fa methods.</br></br>'),
   );

   $mo_get_2fa_methods = MoAuthUtilities::get_2fa_methods_for_inline_registration( FALSE );
   $selected_2fa_methods = MoAuthUtilities::get_2fa_methods_for_inline_registration( TRUE );


   foreach( $mo_get_2fa_methods as $sysName => $displayName ) {
       if( $displayName === AuthenticationType::$EMAIL_VERIFICATION['name'] ) {
           $displayName = $displayName . ' (Transaction Accept and Deny link will be sent to your email)';
       }
     $form['mo_Enable_allow_specific_2Fa']['mo_auth_2fa_methods_for_inline' . str_replace(' ','_', $sysName)] = array(
       '#title' => t( $displayName ),
       '#type' => 'checkbox',
       '#default_value' => array_key_exists( $sysName, $selected_2fa_methods )? 1:0,
       //'#states' => array('disabled' => array(':input[name = "mo_auth_two_factor_enable_specific_2fa_methods"]' => array('checked' => FALSE ), ),),
     );
   }

   $form['mo_Enable_allow_specific_2Fa']['mo_auth_2fa_allow_reconfigure_2fa'] = array(
     '#type' => 'radios',
     '#title' => t('Change/Re-configure 2FA methods'),
     '#default_value' => variable_get('mo_auth_2fa_allow_reconfigure_2fa','Allowed') == 'Allowed' ? 'Allowed' : 'Not_Allowed',
     '#options' => array(
       'Not_Allowed' => t('Not Allowed'),
       'Allowed' => t('Allowed'),
     ),
     '#disabled' => $is_free,
     '#prefix' => '<br><hr><br><div class="mo2f_highlight_background_note"><strong>Note: </strong>If you want to allow your users to change or re-configure there configured 2FA methods then change the setting below.</div><br><div class="container-inline">',
     '#suffix' => '</div><br>'
   );
   $form['m_2fa_end_details']=array(
     '#markup'=>'</details>'
   );

   /**
    * Create container to hold @CustomizeEmailSMSTemplate form elements.
    */
   $user_email         = variable_get('mo_auth_customer_admin_email','');
   $email_template_url = MoAuthConstants::getBaseUrl() . '/login?username=' . $user_email . '&redirectUrl=' . MoAuthConstants::getBaseUrl() . '/admin/customer/emailtemplateconfiguration';
   $logo_favicon_url   = MoAuthConstants::getBaseUrl() . '/login?username=' . $user_email . '&redirectUrl=' . MoAuthConstants::getBaseUrl() . '/admin/customer/customerrebrandingconfig';
   $sms_template_url   = MoAuthConstants::getBaseUrl() . '/login?username=' . $user_email . '&redirectUrl=' . MoAuthConstants::getBaseUrl() . '/admin/customer/showsmstemplate';
   $otp_url            = MoAuthConstants::getBaseUrl() . '/login?username=' . $user_email . '&redirectUrl=' . MoAuthConstants::getBaseUrl() . '/admin/customer/customerpreferences';
   $form['mo_customize_email_sms_template'] = array(
     '#attributes' => array( 'style' => 'padding:0% 2%; margin-bottom:2%' ),
     '#markup'=>'<details ><summary class="mo_tfa_summary" >'.t("Customize SMS and Email Template").'</summary><br><hr>'
   );
   $form['customize_email_template'] = array(
     '#markup' => '<hr><br>
                         <div class="mo_customize_email_sms_template"><strong>Steps to customize email template</strong>
                             <ol>
                                <li>Click <a target="_blank" href="'. $email_template_url .'">here</a> and login.</li>
                                <li>Select Email Template to configure.</li>
                                <li>Switch to <u>SET CUSTOMIZED EMAIL TEMPLATE</u> radio button.</li>
                             </ol>
                         </div><hr><br>
                         <div class="mo_customize_email_sms_template"><strong>Steps to customize Logo and Favicon ( These are used in Email template )</strong>
                             <ol>
                                <li>Click <a target="_blank" href="'. $logo_favicon_url .'">here</a> and login.</li>
                                <li>Navigate to <u>LOGO AND FAVICON</u> tab.</li>
                                <li>Upload images for logo and favicon and save.</li>
                             </ol>
                         </div><hr><br>
                         <div class="mo_customize_email_sms_template"><strong>Steps to customize SMS template</strong>
                             <ol>
                                <li>Click <a target="_blank" href="'. $sms_template_url .'">here</a> and login.</li>
                                <li>Select SMS Template to configure.</li>
                                <li>Switch to <u>SET CUSTOMIZED SMS TEMPLATE</u> radio button.</li>
                             </ol>
                         </div><hr><br>
                         <div class="mo_customize_email_sms_template"><strong>Steps to customize OTP Length and Validity</strong>
                             <ol>
                                <li>Click <a target="_blank" href="'. $otp_url .'">here</a> and login.</li>
                                <li>Navigate to <u>ONE TIME PASSCODE (OTP) SETTINGS</u> option.</li>
                             </ol>
                         </div><br></details>
                         ',
   );
   $form['mo_2fa_advance_settings'] = array(
     '#attributes' => array( 'style' => 'padding:0% 2%; margin-bottom:2%' ),
     '#markup'=>'<details ><summary class="mo_tfa_summary" >'.t("ADVANCE SETTINGS").'</summary><br><hr>'
   );
   $form['mo_2fa_rule'] = array(
     '#type' => 'radios',
     '#title' => t('Interaction between role based and domain based 2FA'),
     '#default_value' => variable_get('mo_2fa_domain_and_role_rule','OR') == 'OR' ? 'OR' : 'AND',
     '#options' => array(
       'OR' => t('Invoke 2FA, if 2FA is required either due to Role or Domain'),
       'AND' => t('Invoke 2FA, if 2FA is required  based on Role as well as Domain'),
     ),
     '#disabled' => $is_free,
   );

   $form['mo_auth_customer_domain_name'] = array(
     '#type' => 'textfield',
     '#title'=>t('Enter your custom xecurify domain'),
     '#default_value' => variable_get('mo_auth_customer_domain_name','login'),
     '#attributes' => array('style' => 'width:700px', 'placeholder' => 'Enter the redirect URL'),
     '#description' => t('<strong>Note: </strong>Enter the branding name you have configured on our server ( Xecurify dashboard ). If you haven\'t already configured the branding keep the default value as <strong>login.</strong>'),
     '#disabled' => $disabled,
       '#prefix' => '<hr>',
   );
   $form['mo_auth_remove_5th_step'] = array(
     '#prefix' => '<hr><br><div class="container-inline">',
     '#type' => 'radios',
     '#title' => t('Security question (Backup login method) configuration in inline registration:'),
     '#default_value' => variable_get('mo_auth_remove_5th_step','Allowed') == 'Allowed' ? 'Allowed' : 'Not_Allowed',
     '#options' => array(
         'Allowed' => t('Allowed'),
         'Not_Allowed' => t('Not Allowed'),
     ),
     '#disabled' => $disabled,
       '#suffix' => '</div>',
   );

     $backdoor_query  = variable_get('miniorange_2fa_backdoor_url_query','false');
     $mo_backdoor_URL = $base_url . '/user/login?login_2fa=' . $backdoor_query;
     $form['miniorange_2fa_enable_backdoor'] = array(
         '#type' => 'checkbox',
         '#title' => t('Check this option if you want to enable <b>backdoor login</b>'),
         '#default_value' => variable_get('miniorange_2fa_enable_backdoor', FALSE),
         '#disabled' => $disabled,
         '#description' => t('<b>Note: </b>Checking this option creates a backdoor to login to your website. User can login to Drupal site using username and password only.<br>
                             You can customize your backdoor url by replacing <b>"false"</b> with a string of your choice. <br><br> Note down this URL: <strong><code><a id="mo_saml_backdoor_url">'.$mo_backdoor_URL.'</a></code></strong> '),
         '#prefix' => '<br><hr><br>',
     );
     $form['mo_auth_customer_backdoor_url'] = array(
         '#type' => 'textfield',
         '#title'=>t('Customize backdoor URL'),
         '#default_value' => $backdoor_query,
         '#attributes' => array('style' => 'width:300px',),
         '#disabled' => $disabled,
         '#suffix' => '<br>',
     );


       //RBA- Remember device feature
      $form['mo_auth_remember_device'] = array(
        '#prefix' => '<hr><br><div class="container-inline">',
        '#type' => 'radios',
        '#title' => t('Enable Remember device<br>'),
        '#default_value' => variable_get('mo_auth_remember_device','Not_Allowed') == 'Not_Allowed' ? 'Not_Allowed' : 'Allowed',
        '#options' => array(
          'Allowed' => t('Allowed'),
          'Not_Allowed' => t('Not Allowed'),
        ),
        '#description' => t('<br><br><b>Note:-</b> If you want to allow your users to remember device then select <strong>\'Allowed\'</strong> above.
                             <br><strong>2FA will not be invoked for the remembered devices for the specified period.</strong>
                             <br><br><div class="mo2f_highlight_background_note">You can control the following settings related to this feature:-</div>
                             <br><br><strong>1. </strong>Click <a target="_blank"  href="' . MoAuthConstants::$BASE_URL . '/login?redirectUrl=' . MoAuthConstants::$BASE_URL . '/admin/customer/customerpreferences" >here</a> to configure the number of days for which the device to be remembered.
                             <br><strong>2. </strong>Click <a target="_blank" href="'. MoAuthConstants::$BASE_URL  .'/login?redirectUrl='. MoAuthConstants::$BASE_URL . '/admin/customer/configpolicy" >here</a> to manage the number of allowed devices to be remembered.
                             <br><strong>3. </strong>Click <a target="_blank"  href="' . MoAuthConstants::$BASE_URL . '/login?redirectUrl=' . MoAuthConstants::$BASE_URL . '/admin/customer/viewrbareport" >here</a> to manage the remembered devices of all the users.
                               '),
        '#suffix' => '<br></details>',
        '#disabled' => $is_free,
      );


   $form['actions'] = array('#type' => 'actions');
   $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save Settings'),
      '#disabled' => $disabled,
      '#prefix' => '<br><br>',
      '#suffix' => '</div></div>',
   );

   $form['markup_idp_attr_header_top_div_close'] = array(
      '#markup' => '</div></div></div>',
   );

   MoAuthUtilities::addSupportForm($form, $form_state);

   return $form;
 }

 /**
  * Send support query.
  */
 function mo_auth_login_settings_submit($form, &$form_state) {
   $form_state['rebuild'] = TRUE;
   $enable2Factor = FALSE;
   $enforceInlineRegistration = FALSE;
   $enableOTP_instead_password = FALSE;

   $mo_auth_redirect_after_login = $form['mo_auth_redirect_user_after_login']['#value'];
   variable_set('mo_auth_redirect_after_login', $mo_auth_redirect_after_login);


     /** Backdoor URL */
     $mo_2fa_enable_backdoor = $form['miniorange_2fa_enable_backdoor']['#value'] == 1;
     $mo_2fa_backdoor_url    = $form['mo_auth_customer_backdoor_url']['#value'] == '' ? 'false' : $form['mo_auth_customer_backdoor_url']['#value'];
     variable_set('miniorange_2fa_enable_backdoor', $mo_2fa_enable_backdoor);
     variable_set('miniorange_2fa_backdoor_url_query', $mo_2fa_backdoor_url);

   /**
    * Domain base 2FA
    */
   $mo_enable_domain_based_2fa = $form['mo_auth_two_factor_enable_domain_based_2fa']['#value'];
   $mo_enable_domain_based_2fa_domains = str_replace(' ', '', $form['mo_2fa_domain_fieldset']['mo_auth_two_factor_domain_based_2fa_domains']['#value']);
   $mo_enable_domain_based_2fa_domains = rtrim( $mo_enable_domain_based_2fa_domains, ";" );
   variable_set('mo_auth_enable_domain_based_2fa', $mo_enable_domain_based_2fa);
   variable_set('mo_auth_two_factor_domain_based_2fa_domains', $mo_enable_domain_based_2fa_domains );
   $listedDomainsAreWhiteOrBlack = $form['mo_2fa_domain_fieldset']['mo_2fa_allow_or_block_domains']['#value'];
   variable_set('mo_2fa_domains_are_white_or_black',$listedDomainsAreWhiteOrBlack);
   $exceptionEmails = $form['mo_2fa_domain_fieldset']['mo_auth_2fa_domain_exception_emails']['#value'];
   variable_set('mo_auth_2fa_domain_exception_emails',$exceptionEmails);



   /**
    * Password complexity checks
    * */
    $formValues = $form_state['values'];

    variable_set('mo_auth_enable_password_checks',$formValues['mo_auth_enable_password_checks']==1);
    variable_set('mo_2fa_unique_password', $formValues['mo_2fa_unique_password']);
    variable_set('mo_2fa_password_min_length', $formValues['mo_2fa_password_min_length']);
    variable_set('mo_2fa_password_max_length', $formValues['mo_2fa_password_max_length']);
    variable_set('mo_2fa_password_password_variation_up_char',$formValues['mo_2fa_password_password_variation_up_char']==1);
    variable_set('mo_2fa_password_password_variation_low_char',$formValues['mo_2fa_password_password_variation_low_char']==1);
    variable_set('mo_2fa_password_password_variation_num_char',$formValues['mo_2fa_password_password_variation_num_char']==1);
    variable_set('mo_2fa_password_password_variation_special_char',$formValues['mo_2fa_password_password_variation_special_char']==1);
    variable_set('mo_2fa_password_must_not_be_email',$formValues['mo_2fa_password_must_not_be_email']==1);
    variable_set('mo_2fa_password_must_not_be_firstname',$formValues['mo_2fa_password_must_not_be_firstname']==1);
    variable_set('mo_2fa_password_must_not_lastname',$formValues['mo_2fa_password_must_not_lastname']==1);
    variable_set('mo_2fa_password_must_not_be_fname_text',trim($formValues['mo_2fa_password_must_not_be_fname_text']));
    variable_set('mo_2fa_password_must_not_be_lname_text',trim($formValues['mo_2fa_password_must_not_be_lname_text']));

   /**
    * Role base 2FA
    */
   $mo_enable_role_based_2fa = $form['mo_auth_two_factor_enable_role_based_2fa']['#value'];
   $roles_arr = user_roles( $membersonly = TRUE );
   $mo_role_based_2fa_roles = array();
   foreach( $roles_arr as $sysName => $displayName ) {
     if ( $form['mo_auth_two_factor_role_based_2fa_roles_' . strtolower($sysName)]['#value'] == 1 ) {
       $mo_role_based_2fa_roles[$sysName] = $displayName;
     }
   }


   /*
    * Whitelist IP's
    * */
   $enableWhitelistIP = isset( $form['mo_auth_two_factor_invoke_2fa_depending_upon_IP']['#value'] ) && $form['mo_auth_two_factor_invoke_2fa_depending_upon_IP']['#value'] == 1 ? TRUE : FALSE;
   $whitelistedIPs = preg_replace('/\s+/', '', $form['mo_auth_two_factor_whitelist_IP']['#value'] );
   variable_set('mo_auth_two_factor_invoke_2fa_depending_upon_IP', $enableWhitelistIP);

   if( variable_get('mo_auth_two_factor_invoke_2fa_depending_upon_IP', FALSE) && !empty( $whitelistedIPs ) ){
     $valid_IPs         = MoAuthUtilities::check_for_valid_IPs( $whitelistedIPs );
     if( $valid_IPs !== TRUE ) {
       drupal_set_message(t($valid_IPs), 'error');
     }
   }

   variable_set('mo_auth_two_factor_whitelist_IP', $whitelistedIPs);

   /**
    *  Allow Specific methods
    */
   $enableSpecific2FAMethods = isset( $form['mo_auth_two_factor_enable_specific_2fa_methods']['#value'] ) && $form['mo_auth_two_factor_enable_specific_2fa_methods']['#value'] ==1 ? TRUE : FALSE;

   variable_set('mo_auth_enable_allowed_2fa_methods', $enableSpecific2FAMethods );

   if(variable_get('mo_auth_enable_allowed_2fa_methods',FALSE)){
     $mo_get_2fa_methods = MoAuthUtilities::get_2fa_methods_for_inline_registration( FALSE );
     $mo_allowed_2fa_methods = array();

     foreach( $mo_get_2fa_methods as $sysName => $displayName ) {
       if ( $form['mo_Enable_allow_specific_2Fa']['mo_auth_2fa_methods_for_inline' . str_replace(' ','_', $sysName) ]['#value'] == 1 ) {
         $mo_allowed_2fa_methods[$sysName] = $displayName;
       }
     }
     variable_set('mo_auth_selected_2fa_methods',json_encode($mo_allowed_2fa_methods));
   }
   $allow2FAReconfigure = $form['mo_Enable_allow_specific_2Fa']['mo_auth_2fa_allow_reconfigure_2fa']['#value'];
   variable_set('mo_auth_2fa_allow_reconfigure_2fa',$allow2FAReconfigure);

  /**
   * Advanced Settings
   * */
   $domainOrRoleRule = $form['mo_2fa_rule']['#value'];
   variable_set('mo_2fa_domain_and_role_rule',$domainOrRoleRule);

   $customerDomain = $form['mo_auth_customer_domain_name']['#value'];
   variable_set('mo_auth_customer_domain_name',$customerDomain);
   $removeKba       = $form['mo_auth_remove_5th_step']['#value'];
   variable_set('mo_auth_remove_5th_step',$removeKba);


   $mo_enable_role_based_2fa_value = $mo_enable_role_based_2fa == 1 && !empty( $mo_role_based_2fa_roles )  ? TRUE : FALSE;
   $mo_role_based_2fa_roles_value  = !empty( $mo_role_based_2fa_roles ) ? json_encode( $mo_role_based_2fa_roles ) : '';

   variable_set('mo_auth_enable_role_based_2fa', $mo_enable_role_based_2fa_value);
   variable_set('mo_auth_role_based_2fa_roles', $mo_role_based_2fa_roles_value);
   variable_set('mo_auth_make_email_editable', $form['mo_auth_make_email_editable']['#value']);

   //RBA- remember device
   variable_set('mo_auth_remember_device', $form['mo_auth_remember_device']['#value']);

   if ( array_key_exists('mo_auth_enable_two_factor', $form_state['input'] ) ) {
      $enable2Factor = TRUE;
      if ( array_key_exists('mo_auth_two_factor_instead_password', $form_state['input'] ) ) {
        $enableOTP_instead_password = TRUE;
        $enforceInlineRegistration = TRUE;
      }
      if ( array_key_exists('mo_auth_enforce_inline_registration', $form_state['input'] ) ) {
        $enforceInlineRegistration = TRUE;
      }
    }
   $loginSettings = MoAuthLoginSettings::withValues($enable2Factor, $enforceInlineRegistration, $enableOTP_instead_password);
   $loginSettings->updateLoginSettings();
   drupal_set_message(t("Login settings updated."), 'status');
 }

/**
 * Send support query.
 */

function miniorange_2fa_send_query($form, &$form_state) {
    $email = $form['miniorange_saml_email_address_support']['#value'];
    $phone = $form['miniorange_saml_phone_number_support']['#value'];
    $query = $form['miniorange_saml_support_query_support']['#value'];
    MoAuthUtilities::send_support_query($email, $phone, $query);
}
