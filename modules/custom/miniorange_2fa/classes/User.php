<?php

class MiniorangeUser {

  private $customerId;

  private $username;

  private $phone;

  private $name;

  private $authType;

  private $email;

  public function __construct($customerId, $username, $phone, $name, $authType, $email = "") {
    $this->customerId = $customerId;
    $this->username = $username;
    $this->phone = str_replace(" ","",$phone);
    $this->name = $name;
    $this->authType = $authType;
    $this->email = $email;
  }

  public function update() {
    $apiKey = variable_get('mo_auth_customer_api_key', NULL);
    if (is_null($this->customerId) || is_null($apiKey)) {
      return FALSE;
    }
  $usersAPIHandler = new UsersAPIHandler($this->customerId, $apiKey);
  $response = $usersAPIHandler->update($this);
  }

  public function create() {
    $apiKey = variable_get('mo_auth_customer_api_key', NULL);
    if (is_null($this->customerId) || is_null($apiKey)) {
      return FALSE;
    }
    $usersAPIHandler = new UsersAPIHandler($this->customerId, $apiKey);
    $response = $usersAPIHandler->create($this);
  }

  public function search() {
    $apiKey = variable_get('mo_auth_customer_api_key', NULL);
    if (is_null($this->customerId) || is_null($apiKey)) {
      return FALSE;
    }
    $usersAPIHandler = new UsersAPIHandler($this->customerId, $apiKey);
    $response = $usersAPIHandler->search($this);
  }

  public function get() {
    $apiKey = variable_get('mo_auth_customer_api_key', NULL);
    if (is_null($this->customerId) || is_null($apiKey)) {
      return FALSE;
    }
    $usersAPIHandler = new UsersAPIHandler($this->customerId, $apiKey);
    $response = $usersAPIHandler->get($this);
  }

  public function getCustomerID() {
    return $this->customerId;
  }

  public function setCustomerID($customerId) {
    $this->customerId = $customerId;
  }
  public function getUsername() {
  	return $this->username;
  }

  public function setUsername($username) {
  	$this->username = $username;
  }
  public function getEmail() {
    return $this->email;
  }

  public function setEmail($email) {
    $this->email = $email;
  }

  public function getPhone() {
    return $this->phone;
  }

  public function setPhone($phone) {
    $this->phone = $phone;
  }

  public function getName() {
    return $this->name;
  }

  public function setName($name) {
    $this->name = $name;
  }

  public function getAuthType() {
    return $this->authType;
  }

  public function setAuthType($authType) {
    $this->authType = $authType;
  }
}
