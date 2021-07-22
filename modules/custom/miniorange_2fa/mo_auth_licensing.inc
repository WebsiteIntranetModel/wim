<?php

/**
 * @file
 * Contains support form for miniOrange 2FA Login Module.
 */

/**
 * Showing Support form info.
 */
function mo_auth_licensing($form, &$form_state) {

  drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/bootstrap.min.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));
  // drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/st_settings.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

  $license_type = variable_get('mo_auth_2fa_license_type', 'DEMO');
  $license_plan = variable_get('mo_auth_2fa_license_plan', 'DEMO');
  $free = '';
  global $base_url;
  if ($license_type != 'DRUPAL_2FA_PLUGIN') {
    $free .= "You are on this plan";
  } else {
    $free .= "Upgraded";
  }

   $form['markup_1'] = array(
     '#markup' =>'<div class="mo2f_table_layout_1"><div class="mo2f_table_layout"><br>
                <h3 style="margin-left: 25px;">UPGRADE PLANS</h3><hr>'
   );

   $form['markup_free'] = array(
     '#markup' => '<html lang="en">
        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1">
            <!-- Main Style -->
        </head>
        <body>
        <!-- Pricing Table Section -->
        <section id="mo2f_pricing-table">
            <div class="mo2f_container_1">
                <div class="row">
                    <div class="mo2f_pricing">
                        <div>
                            <div class="mo2f_pricing-table mo2f_class_inline_1">
                                <div class="mo2f_pricing-header">
                                    <h1 class="mo2f_pricing-title" style="margin-bottom:31px;">Features / Plans</h1>
                                </div>
                                <div class="mo2f_pricing-list">
                                    <ul>
                                        <li>All Authentication Methods</li>
                                        <li>Security Questions (KBA)</li>
                                        <li>Redirect user after login</li>                                       
                                        <li>Change app name in Google Authenticator app</li>
                                        <li>Customize Email Templates</li>
                                        <li>Customize SMS Templates</li>
                                        <li>Customize OTP length and validity</li>
                                        <li>Customize number of KBA to be asked while login</li>
                                        <li>Reset 2FA for users</li>
                                        <li>Enforce 2FA registration for users</li>
                                        <li>Role based 2FA</li>
                                        <li>Domain based 2FA</li>
                                        <li>IP Whitelisting</li>
                                        <li>Login with 2nd Factor only (No password required)</li>
                                        <li>Manage Registered Device Profiles</li>
                                        <li>Remember Device (available soon)</li>
                                        <li>End to End 2FA Integration***</li>
                                        <li>Premium Support Plans Available</li>
                                    </ul>
                                </div>
                        </div>

                        <div class="mo2f_pricing-table mo2f_class_inline">
                            <div class="mo2f_pricing-header" style="height: 259px;">
                                <p class="mo2f_pricing-title">Free</p><br><br><br><br><br><br>
                                <p class="mo2f_pricing-rate">
                                </p>
                                <div class="mo2f_filler-class"></div>
                                 <input type="button" class="mo2fa_btn mo2fa_btn-primary mo2fa_btn-sm mo2f-pricing-button" value="'.$free.'" /> <br><br>
                            </div>

                            <div class="mo2f_pricing-list">
                                <ul>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                    <li></li>
                                  </ul>
                            </div>
                        </div>

                        <div class="mo2f_pricing-table mo2f_class_inline">
                            <div class="mo2f_pricing-header" style="height: 259px;">
                                <p class="mo2f_pricing-title">Premium<br></p><br>
                                <p style="font-size: 15px; color: #fff; text-align: center;margin-bottom:6px;">Yearly Subscription Fees**
                        <select required style=" margin-left: 7px;height:25px;">
                            <option>Upto 5 users - $20 / year
                            <option>Upto 10 users - $40 / year
                            <option>Upto 20 users - $65 / year
                            <option>Upto 30 users - $90 / year
                            <option>Upto 40 users - $115 / year
                            <option>Upto 50 users - $140 / year
                            <option>Upto 60 users - $165 / year
                            <option>Upto 70 users - $190 / year
                            <option>Upto 80 users - $215 / year
                            <option>Upto 90 users - $240 / year
                            <option>Upto 100 users - $265 / year
                            <option>Upto 150 users - $295 / year
                            <option>Upto 200 users - $325 / year
                            <option>Upto 250 users - $355 / year
                            <option>Upto 300 users - $385 / year
                            <option>Upto 350 users - $415 / year
                            <option>Upto 400 users - $445 / year
                            <option>Upto 450 users - $475 / year
                            <option>Upto 500 users - $505 / year
                            <option>Upto 600 users - $540 / year
                            <option>Upto 700 users - $575 / year
                            <option>Upto 800 users - $610 / year
                            <option>Upto 900 users - $645 / year
                            <option>Upto 1000 users - $680 / year
                            <option>Upto 2000 users - $730 / year
                            <option>Upto 3000 users - $780 / year
                            <option>Upto 4000 users - $830 / year
                            <option>Upto 5000 users - $880 / year
                            <option>More Than 5000 users - Contact Us
                      </select>
                    </p>

                                <a target="_blank" href="https://login.xecurify.com/moas/login?redirectUrl=https://login.xecurify.com/moas/initializepayment&requestOrigin=drupal_2fa_premium_plan" class="mo2fa_btn mo2fa_btn-primary mo2fa_btn-sm mo2f-pricing-button" />Click here to upgrade*</a>
                                </br></br>
                                <a  href="'.$base_url.'/admin/config/people/mo_auth/support'.'" class="mo2fa_btn mo2fa_btn-primary mo2fa_btn-sm mo2f-pricing-button" style="margin-top:17px !important;" />Buy SMS transactions</a>

                            </div>
                            <div class="mo2f_pricing-list">
                                <ul>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                    <li>&#x2714;</li>
                                </ul>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </section>
    <!-- Pricing Table Section End -->
    </body>
    </html>',
   );


   $form['markup_4'] = array(
     '#markup' => '</b><br><div class="mo2f_space"><h3>* Steps to Upgrade to Premium Module</h3>'
       . '<ol>
          <li>Click on the <strong>Click here to upgrade button</strong> you will be redirected to xecurify login console. Login with the account with which you created with us. After that you will be redirected to payment page.</li>'
       . '<li>Enter your card details and complete the payment. On successful payment completion, go to <a href="?q=admin/config/people/mo_auth">Register/Login</a> tab and click on Check License button.</li>'
       . '</ol>'
   );

    $form['markup_5'] = array(
     '#markup' => '</b><br><h3>** If you dont find the number of users in the dropdown then check the price for exact number of users by clicking on "Click here to upgrade" button.</h3>'
       . '<ol>
                <li>You can mail us at <a href="mailto:drupalsupport@xecurify.com">drupalsupport@xecurify.com</a> or submit the support form under Support tab to contact us.</li>'
       . '<li>We also support OTP over SMS, Hardware Token like Yubico and Display Token. Contact us if you want to use these authentication methods.</li>'
       . '</ol><br>'
   );

   $form['markup_6'] = array(
     '#markup' => '<h3>*** End to End 2FA Integration</h3>'
       . ' We will setup a Conference Call / Gotomeeting and do end to end configuration for you to setup two factor authentication.'
       . ' We provide services to do the configuration on your behalf.<br />'
       . ' If you have any doubts regarding the licensing plans, you can mail us at <a href="mailto:drupalsupport@xecurify.com">drupalsupport@xecurify.com</a> or submit a query using the support form <b>( support form available on each tab )</b>.<br><br>
       
       <h3>Return Policy - </h3>
        At miniOrange, we want to ensure you are 100% happy with your purchase. If the module you purchased is not working as advertised and you\'ve attempted to resolve any issues with our support team, which couldn\'t get resolved, we will refund the whole amount given that you have a raised a request for refund within the first 10 days of the purchase. Please email us at <a href="mailto:drupalsupport@xecurify.com">drupalsupport@xecurify.com</a> for any queries regarding the return policy. 
       <br><br></div></div>'
   );

   $form['markup_8'] = array(
     '#markup' => '</div></div>'
   );

   $customer = new MiniorangeCustomerProfile();
  $form['username'] = array (
    '#type' => 'hidden',
    '#value' => $customer->getRegisteredEmail()
  );
  $form['redirectUrl'] = array (
    '#type' => 'hidden',
    '#value' => MoAuthConstants::getBaseUrl() . '/initializepayment'
  );
  $form['requestOrigin'] = array (
    '#type' => 'hidden',
    '#value' => ''
  );
  $form['#action'] = MoAuthConstants::getBaseUrl() . '/login';
  $form['#attributes'] = array (
    'target' => '_blank'
  );

    return $form;
}
