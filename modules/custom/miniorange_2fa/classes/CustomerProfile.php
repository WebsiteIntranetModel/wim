<?php
/**
 * @file
 * Contains constants class.
 */

/**
 * @file
 * This class represents User Profile.
 */
class MiniorangeCustomerProfile {
  private $customer_id;
  private $registered_email;
  private $api_key;
  private $token_key;
  private $app_secret;
  private $registered_phone;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->customer_id = variable_get('mo_auth_customer_id', '');
    $this->registered_email = variable_get('mo_auth_customer_admin_email', '');
    $this->api_key = variable_get('mo_auth_customer_api_key', '');
    $this->token_key = variable_get('mo_auth_customer_admin_token', '');
    $this->app_secret = variable_get('mo_auth_customer_app_secret', '');
    $this->registered_phone = variable_get('mo_auth_customer_admin_phone', '');
  }
  public function getCustomerID() {
    return $this->customer_id;
  }
  public function getAPIKey() {
    return $this->api_key;
  }
  public function getTokenKey() {
    return $this->token_key;
  }
  public function getAppSecret() {
    return $this->app_secret;
  }
  public function getRegisteredEmail() {
    return $this->registered_email;
  }
  public function getRegisteredPhone() {
    return $this->registered_phone;
  }
}