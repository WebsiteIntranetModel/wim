<?php

class MoAuthRBA
{
   public static function mo2f_collect_attributes( $useremail, $rba_attributes ) {
    $url          = MoAuthConstants::$BASE_URL . '/rest/rba/acs';
    $ch = curl_init($url);
    $customerKey  = variable_get('mo_auth_customer_id', '');
    $apiKey = variable_get('mo_auth_customer_api_key', '');

     $fields = "{\"customerKey\":\"" . $customerKey . "\",\"userKey\":\"" . $useremail . "\",\"attributes\":" . $rba_attributes . "}";

    /* Current time in milliseconds since midnight, January 1, 1970 UTC. */
    $currentTimeInMillis = round( microtime( true ) * 1000 );
    $currentTimeInMillis = number_format( $currentTimeInMillis, 0, '', '' );

    /* Creating the Hash using SHA-512 algorithm */
    $stringToHash = $customerKey . $currentTimeInMillis . $apiKey;
    $hashValue = hash( "sha512", $stringToHash );

    $customerKeyHeader = "Customer-Key: " . $customerKey;
    $timestampHeader = "Timestamp: " . number_format($currentTimeInMillis, 0, '', '' );
    $authorizationHeader = "Authorization: " . $hashValue;

    curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, true );
    curl_setopt( $ch, CURLOPT_ENCODING, "" );
    curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
    curl_setopt( $ch, CURLOPT_AUTOREFERER, true );
    curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );    # required for https urls
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST,false);

    curl_setopt( $ch, CURLOPT_MAXREDIRS, 10 );
    curl_setopt($ch, CURLOPT_HTTPHEADER, $var = array("Content-Type: application/json", $customerKeyHeader,
      $timestampHeader, $authorizationHeader));

    curl_setopt( $ch, CURLOPT_POST, true);
    curl_setopt( $ch, CURLOPT_POSTFIELDS, $fields);
    curl_setopt( $ch, CURLOPT_CONNECTTIMEOUT, 5);
    curl_setopt( $ch, CURLOPT_TIMEOUT, 20);
    $content = curl_exec($ch);

    if( curl_errno( $ch ) ){
      echo 'Request Error:' . curl_error( $ch );
      exit();
    }

    curl_close( $ch );
    return $content;
  }


  public static function mo2f_evaluate_risk($useremail,$sessionUuid){
    $url = MoAuthConstants::$BASE_URL . '/rest/rba/evaluate-risk';
    $ch = curl_init($url);
    /* The customer Key provided to you */
    $customerKey  = variable_get('mo_auth_customer_id', '');
    /* The customer API Key provided to you */
    $apiKey = variable_get('mo_auth_customer_api_key', '');

    $appSecret = variable_get('mo_auth_customer_app_secret', '');
    /* Current time in milliseconds since midnight, January 1, 1970 UTC. */
    $currentTimeInMillis = round(microtime(true) * 1000);
    /* Creating the Hash using SHA-512 algorithm */
    $stringToHash = $customerKey . number_format($currentTimeInMillis, 0, '', '') . $apiKey;
    $hashValue = hash("sha512", $stringToHash);
    $customerKeyHeader = "Customer-Key: " . $customerKey;
    $timestampHeader = "Timestamp: " . number_format($currentTimeInMillis, 0, '', '');
    $authorizationHeader = "Authorization: " . $hashValue;
    $fields = array(
      'customerKey' => $customerKey,
      'appSecret' => $appSecret,
      'userKey' => $useremail,
      'sessionUuid' => $sessionUuid
    );
    $field_string = json_encode( $fields );
    curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, false );
    curl_setopt( $ch, CURLOPT_ENCODING, "" );
    curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
    curl_setopt( $ch, CURLOPT_AUTOREFERER, true );
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );    # required for https urls
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


  public static function mo2f_register_rba_profile($useremail,$sessionUuid){
    $url = MoAuthConstants::$BASE_URL . '/rest/rba/register-profile';
    $ch = curl_init($url);
    /* The customer Key provided to you */
    $customerKey  = variable_get('mo_auth_customer_id', '');
    /* The customer API Key provided to you */
    $apiKey = variable_get('mo_auth_customer_api_key', '');
    /* Current time in milliseconds since midnight, January 1, 1970 UTC. */
    $currentTimeInMillis = round(microtime(true) * 1000);
    /* Creating the Hash using SHA-512 algorithm */
    $stringToHash = $customerKey . number_format($currentTimeInMillis, 0, '', '') . $apiKey;
    $hashValue = hash("sha512", $stringToHash);
    $customerKeyHeader = "Customer-Key: " . $customerKey;
    $timestampHeader = "Timestamp: " . number_format($currentTimeInMillis, 0, '', '');
    $authorizationHeader = "Authorization: " . $hashValue;
    $fields = array(
      'customerKey' => $customerKey,
      'userKey' => $useremail,
      'sessionUuid' => $sessionUuid
    );
    $field_string = json_encode( $fields );
    curl_setopt( $ch, CURLOPT_FOLLOWLOCATION, false );
    curl_setopt( $ch, CURLOPT_ENCODING, "" );
    curl_setopt( $ch, CURLOPT_RETURNTRANSFER, true );
    curl_setopt( $ch, CURLOPT_AUTOREFERER, true );
    curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, false);
    curl_setopt( $ch, CURLOPT_SSL_VERIFYPEER, false );    # required for https urls
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
