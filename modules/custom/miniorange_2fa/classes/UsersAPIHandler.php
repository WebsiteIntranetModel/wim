<?php
require_once 'Constants.php';
class UsersAPIHandler {
  private $customerId;
  private $apiKey;

  public function __construct($customerId, $apiKey) {
    $this->apiKey = $apiKey;
    $this->customerId = $customerId;
  }

  public function update(MiniorangeUser $user) {
    if(is_string($user->getAuthType()) && AuthenticationType::isCodeBelongsToAAuthenticator($user->getAuthType()) )
      $user->setAuthType(AuthenticationType::$GOOGLE_AUTHENTICATOR['code']);
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername(),
      'phone' => $user->getPhone(),
      'authType' => $user->getAuthType(),
      'transactionName' => MoAuthConstants::$PLUGIN_NAME
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$USERS_UPDATE_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function get(MiniorangeUser $user) {
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername()
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$USERS_GET_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function create(MiniorangeUser $user) {
    $fields = array (
      'customerKey' => $this->customerId,
      'username' => $user->getUsername(),
      'firstName' => $user->getName()
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$USERS_CREATE_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function search(MiniorangeUser $user) {
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername()
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$USERS_SEARCH_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function fetchLicense() {
    $fields = array (
      'customerId' => $this->customerId,
      'applicationName' => 'drupal_2fa'
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$CUSTOMER_CHECK_LICENSE;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }
}
