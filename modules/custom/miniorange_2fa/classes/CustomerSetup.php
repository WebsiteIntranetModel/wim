<?php
/**
 * @file
 * Contains miniOrange Customer class.
 */

/**
 * @file
 * This class represents configuration for customer.
 */
class MiniorangeCustomerSetup {
  public $email;
  public $phone;
  public $customerKey;
  public $transactionId;
  public $password;
  public $otpToken;
  public $defaultCustomerId;
  public $defaultCustomerApiKey;

  /**
   * Constructor.
   */
  public function __construct($email, $phone, $password, $otp_token) {
    $this->email = $email;
    $this->phone = $phone;
    $this->password = $password;
    $this->otpToken = $otp_token;
    $this->defaultCustomerId = MoAuthConstants::$DEFAULT_CUSTOMER_ID;
    $this->defaultCustomerApiKey = MoAuthConstants::$DEFAULT_CUSTOMER_API_KEY;
  }

  /**
   * Check if customer exists.
   */
  public function checkCustomer() {
    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$CUSTOMER_CHECK_API;
    $fields = array (
      'email' => $this->email
    );
    $json = json_encode($fields);
    $response = MoAuthUtilities::callService($this->defaultCustomerId, $this->defaultCustomerApiKey, $url, $json);
    if (json_last_error() == JSON_ERROR_NONE && isset($response->status) && strcasecmp($response->status, 'CURL_ERROR')==0) {
      $error = array (
        '%method' => 'checkCustomer',
        '%file' => 'CustomerSetup.php',
        '%error' => $response->message
      );
      watchdog('mo_auth', 'Error at %method of %file: %error', $error);
    }
    return $response;
  }

  /**
   * Create Customer.
   */
  public function createCustomer() {
    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$CUSTOMER_CREATE_API;

    $fields = array (
      'companyName' => $_SERVER['SERVER_NAME'],
      'areaOfInterest' => MoAuthConstants::$PLUGIN_NAME,
      'email' => $this->email,
      'phone' => $this->phone,
      'password' => $this->password
    );
    $json = json_encode($fields);
    $response = MoAuthUtilities::callService($this->defaultCustomerId, $this->defaultCustomerApiKey, $url, $json);

    if (json_last_error() == JSON_ERROR_NONE && strcasecmp($response->status, 'CURL_ERROR')) {
      $error = array (
        '%method' => 'createCustomer',
        '%file' => 'CustomerSetup.php',
        '%error' => $response->message
      );
      watchdog('mo_auth', 'Error at %method of %file: %error', $error);
    }
    return $response;
  }

  /**
   * Get Customer Keys.
   */
  public function getCustomerKeys() {
    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$CUSTOMER_GET_API;

    $fields = array (
      'email' => $this->email,
      'password' => $this->password
    );
    $json = json_encode($fields);

    $response = MoAuthUtilities::callService($this->defaultCustomerId, $this->defaultCustomerApiKey, $url, $json);
    if (json_last_error() == JSON_ERROR_NONE && empty($response->apiKey)) {
      $error = array (
        '%method' => 'getCustomerKeys',
        '%file' => 'CustomerSetup.php',
        '%error' => $response->message
      );
      watchdog('mo_auth', 'Error at %method of %file: %error', $error);
    }
    return $response;
  }

  /**
   * Send OTP.
   */
  public function sendOtp() {
    $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_CHALLENGE_API;

    $username = variable_get('mo_auth_customer_admin_email', NULL);

    $fields = array (
      'customerKey' => $this->defaultCustomerId,
      'email' => $username,
      'authType' => AuthenticationType::$EMAIL['code']
    );
    $json = json_encode($fields);

    $response = MoAuthUtilities::callService($this->defaultCustomerId, $this->defaultCustomerApiKey, $url, $json);

    if (json_last_error() == JSON_ERROR_NONE && strcasecmp($response->status, 'CURL_ERROR')) {
      $error = array (
        '%method' => 'sendOtp',
        '%file' => 'CustomerSetup.php',
        '%error' => $response->message
      );
      watchdog('mo_auth', 'Error at %method of %file: %error', $error);
    }
    return $response;
  }

   public function send_otp_token( $uKey, $authType, $cKey, $apiKey ) {

     $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_CHALLENGE_API;
     $ch  = curl_init( $url );

     /** The customer Key provided to you */
     $customerKey         = $cKey;

     /** Current time in milliseconds since midnight, January 1, 1970 UTC. */
     $currentTimeInMillis = round(microtime(true) * 1000);

     /** Creating the Hash using SHA-512 algorithm */
     $stringToHash        = $customerKey . number_format( $currentTimeInMillis, 0, '', '' ) . $apiKey;
     $hashValue           = hash("sha512", $stringToHash);
     $customerKeyHeader   = "Customer-Key: " . $customerKey;
     $timestampHeader     = "Timestamp: " . number_format( $currentTimeInMillis, 0, '', '' );
     $authorizationHeader = "Authorization: " . $hashValue;

     if( $authType == 'EMAIL' ) {
       $fields = array(
         'customerKey' => $customerKey,
         'email' => $uKey['email'],
         'authType' => $authType,
         'transactionName' => 'Drupal 2 Factor Authentication Plugin'
       );
     } else if( $authType == 'OTP_OVER_SMS' || $authType == 'OTP_OVER_SMS_AND_EMAIL' || $authType == 'OTP_OVER_EMAIL' || $authType == 'PHONE_VERIFICATION' ){

       if( $authType == 'OTP_OVER_SMS' ) {
         $authType = "SMS";
       }elseif( $authType == 'PHONE_VERIFICATION' ) {
         $authType = "PHONE VERIFICATION";
       }elseif( $authType == 'OTP_OVER_SMS_AND_EMAIL' ) {
         $authType = "SMS AND EMAIL";
       }elseif( $authType == 'OTP_OVER_EMAIL')   {
         $authType = "OTP OVER EMAIL";
       }

       $phone = isset( $uKey['phone'] ) ? $uKey['phone'] : '' ;
       $email = isset( $uKey['email'] ) ? $uKey['email'] : '' ;
       if( $authType == 'SMS AND EMAIL' ) {
         $fields = array(
           'customerKey' => $customerKey,
           'phone'       => $phone,
           'email'       => $email,
           'authType'    => $authType
         );
       }elseif( $authType == 'OTP OVER EMAIL' ) {
         $fields = array(
           'customerKey' => $customerKey,
           'email'       => $email,
           'authType'    => $authType
         );
       }else {
         $fields = array(
           'customerKey' => $customerKey,
           'phone'       => $phone,
           'authType'    => $authType,
         );
       }
     }

     $field_string = json_encode( $fields );

     curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, false );
     curl_setopt( $ch, CURLOPT_ENCODING, "" );
     curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
     curl_setopt( $ch, CURLOPT_AUTOREFERER, true );

     curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );    # required for https urls
     curl_setopt( $ch, CURLOPT_SSL_VERIFYHOST, false );    # required for https urls

     curl_setopt( $ch, CURLOPT_MAXREDIRS, 10 );
     curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: application/json", $customerKeyHeader,
       $timestampHeader, $authorizationHeader));
     curl_setopt( $ch, CURLOPT_POST, true);
     curl_setopt( $ch, CURLOPT_POSTFIELDS, $field_string);
     curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 5);
     curl_setopt( $ch, CURLOPT_TIMEOUT, 20);
     $content = curl_exec($ch);

     if( curl_errno( $ch ) ) {
       return null;
     }
     curl_close($ch);

     return $content;
	}

  /**
   * Validate OTP.
   */
  public function validate_otp_token($transactionId,$otpToken,$cKey,$apiKey) {

	  $url = MoAuthConstants::getBaseUrl().MoAuthConstants::$AUTH_VALIDATE_API;
		$ch = curl_init($url);


		/* The customer Key provided to you */
		$customerKey = $cKey;

		/* The customer API Key provided to you */
		$apiKey = $apiKey;

		/* Current time in milliseconds since midnight, January 1, 1970 UTC. */
		$currentTimeInMillis = round(microtime(true) * 1000);

		/* Creating the Hash using SHA-512 algorithm */
		$stringToHash = $customerKey . number_format($currentTimeInMillis, 0, '', '') . $apiKey;
		$hashValue = hash("sha512", $stringToHash);

		$customerKeyHeader = "Customer-Key: " . $customerKey;
		$timestampHeader = "Timestamp: " . number_format($currentTimeInMillis, 0, '', '');
		$authorizationHeader = "Authorization: " . $hashValue;

        $fields = array(
				'txId' => $transactionId,
				'token' => $otpToken
			);

		$field_string = json_encode($fields);

		curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, false );
		curl_setopt( $ch, CURLOPT_ENCODING, "" );
		curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
		curl_setopt( $ch, CURLOPT_AUTOREFERER, true );
		curl_setopt( $ch, CURLOPT_SSL_VERIFYHOST, false);

		curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );    # required for https urls
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);    # required for https urls

		curl_setopt( $ch, CURLOPT_MAXREDIRS, 10 );
		curl_setopt($ch, CURLOPT_HTTPHEADER, array("Content-Type: application/json", $customerKeyHeader,
											$timestampHeader, $authorizationHeader));
		curl_setopt( $ch, CURLOPT_POST, true);
		curl_setopt( $ch, CURLOPT_POSTFIELDS, $field_string);
		curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 5);
        curl_setopt( $ch, CURLOPT_TIMEOUT, 20);
		$content = curl_exec($ch);

		if(curl_errno($ch)){
			return null;
		}
		curl_close($ch);
		return $content;
  }
}
