<?php
class AuthenticationAPIHandler {
  private $customerId;
  private $apiKey;

  public function __construct($customerId, $apiKey) {
    $this->apiKey = $apiKey;
    $this->customerId = $customerId;
  }

  public function challenge(MiniorangeUser $user) {

    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername(),
      'email' => $user->getEmail(),
      'phone' => $user->getPhone(),
      'authType' => $user->getAuthType(),
      'transactionName' => MoAuthConstants::$TRANSACTION_NAME
    );

    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_CHALLENGE_API;



    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function validate(MiniorangeUser $user, $txId, $token, $answers = NULL) {
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername(),
      'txId' => $txId,
      'token' => str_replace(" ","",$token),
      'authType' => $user->getAuthType(),
      'answers' => $answers
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_VALIDATE_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function getAuthStatus($txId) {
    $fields = array (
      'txId' => $txId
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_STATUS_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function getGoogleAuthSecret(MiniorangeUser $user) {
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername()
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_GET_GOOGLE_AUTH_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }



  public function register(MiniorangeUser $user, $registrationType, $secret, $token, $quesAnsList) {
    $fields = array (
      'customerKey' => $user->getCustomerId(),
      'username' => $user->getUsername(),
      'registrationType' => $registrationType,
      'secret' => $secret,
      'otpToken' => str_replace(" ","",$token),
      'questionAnswerList' => $quesAnsList
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_REGISTER_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function registerQRCode(MiniorangeUser $user) {
    $fields = array (
      'username' => $user->getUsername()
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_REGISTER_MOBILE_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }

  public function getRegistrationStatus($txId) {
    $fields = array (
      'txId' => $txId
    );
    $json = json_encode($fields);

    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_REGISTRATION_STATUS_API;

    return MoAuthUtilities::callService($this->customerId, $this->apiKey, $url, $json);
  }
}
