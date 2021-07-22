<?php
/**
 * @file
 * Contains constants class.
 */

/**
 * @file
 * This class represents constants used throughout project.
 */
class MoAuthConstants {
  public static $MODULE_NAME              = 'mo_auth';
  public static $BASE_URL                 = 'https://login.xecurify.com/moas';
  public static $PLUGIN_NAME              = 'Drupal Two-Factor Plugin';
  public static $TRANSACTION_NAME         = 'Drupal Two-Factor Module';
  public static $DEFAULT_CUSTOMER_ID      = '16555';
  public static $DEFAULT_CUSTOMER_API_KEY = 'fFd2XcvTGDemZvbw1bcUesNJWEqKbbUq';

  public static $CUSTOMER_CHECK_API           = '/rest/customer/check-if-exists';
  public static $CUSTOMER_CREATE_API          = '/rest/customer/add';
  public static $CUSTOMER_GET_API             = '/rest/customer/key';
  public static $CUSTOMER_CHECK_LICENSE       = '/rest/customer/license';
  public static $SUPPORT_QUERY                = '/rest/customer/contact-us';

  public static $USERS_CREATE_API             = '/api/admin/users/create';
  public static $USERS_GET_API                = '/api/admin/users/get';
  public static $USERS_UPDATE_API             = '/api/admin/users/update';
  public static $USERS_SEARCH_API             = '/api/admin/users/search';

  public static $AUTH_CHALLENGE_API           = '/api/auth/challenge';
  public static $AUTH_VALIDATE_API            = '/api/auth/validate';
  public static $AUTH_STATUS_API              = '/api/auth/auth-status';
  public static $AUTH_REGISTER_API            = '/api/auth/register';
  public static $AUTH_REGISTRATION_STATUS_API = '/api/auth/registration-status';
  public static $AUTH_GET_GOOGLE_AUTH_API     = '/api/auth/google-auth-secret';

  public static function getBaseUrl() {
      $getBrandingName = variable_get('mo_auth_customer_domain_name','login');
      return "https://" . $getBrandingName . ".xecurify.com/moas";
  }
}
