<?php
class MoAuthLoginSettings {

  private $enable2Factor;

  private $enforceInlineRegistration;

  private $enableOTP_instead_password;

  private $enablePasswordChecks;

  private $lastNUniquePassword;
  private $passwordMaxLength;
  private $passwordMinLength;
  private $passwordMustHaveLowChar;
  private $passwordMustHaveUpChar;
  private $passwordMustHaveNumChar;
  private $passwordMustHaveSpecialChar;
  private $passwordMustNotBeEmail;
  private $passwordMustNotBeFname;
  private $passwordMustNotBeLname;
  private $machineNameOfFname;
  private $machineNameOfLname;

  public function __construct() {
    $this->enable2Factor                = variable_get('mo_auth_enable_two_factor', TRUE);
    $this->enforceInlineRegistration    = variable_get('mo_auth_enforce_inline_registration', FALSE);
    $this->enableOTP_instead_password   = variable_get('mo_auth_two_factor_instead_password', FALSE);
    $this->enablePasswordChecks         = variable_get('mo_auth_enable_password_checks',FALSE);
    $this->lastNUniquePassword          = variable_get('mo_2fa_unique_password',0);
    $this->passwordMinLength            = variable_get('mo_2fa_password_min_length',5);
    $this->passwordMaxLength            = variable_get('mo_2fa_password_max_length',10);
    $this->passwordMustHaveLowChar      = variable_get('mo_2fa_password_password_variation_low_char',TRUE);
    $this->passwordMustHaveUpChar       = variable_get('mo_2fa_password_password_variation_up_char',TRUE);
    $this->passwordMustHaveNumChar      = variable_get('mo_2fa_password_password_variation_num_char',TRUE);
    $this->passwordMustHaveSpecialChar  = variable_get('mo_2fa_password_password_variation_special_char',TRUE);
    $this->passwordMustNotBeEmail       = variable_get('mo_2fa_password_must_not_be_email',FALSE);
    $this->passwordMustNotBeFname       = variable_get('mo_2fa_password_must_not_be_firstname',FALSE);
    $this->passwordMustNotBeLname       = variable_get('mo_2fa_password_must_not_lastname',FALSE);
    $this->machineNameOfFname           = variable_get('mo_2fa_password_must_not_be_fname_text','');
    $this->machineNameOfLname           = variable_get('mo_2fa_password_must_not_be_lname_text','');
  }

  public static function withValues($enable2Factor, $enforceInlineRegistration, $enableOTP_instead_password) {
    $instance = new MoAuthLoginSettings();
    $instance->setEnable2Factor($enable2Factor);
    $instance->setEnforceInlineRegistration($enforceInlineRegistration);
    $instance->setEnableOTPinsteadPassword($enableOTP_instead_password);
    return $instance;
  }

  public function updateLoginSettings() {
    variable_set('mo_auth_enable_two_factor', $this->enable2Factor);
    variable_set('mo_auth_enforce_inline_registration', $this->enforceInlineRegistration);
    variable_set('mo_auth_two_factor_instead_password', $this->enableOTP_instead_password);
  }

  public function getEnable2Factor() {
    return $this->enable2Factor;
  }

  private function setEnable2Factor($enable2Factor) {
    $this->enable2Factor = $enable2Factor;
  }

  public function getEnforceInlineRegistration() {
    return $this->enforceInlineRegistration;
  }

  private function setEnforceInlineRegistration($enforceInlineRegistration) {
    $this->enforceInlineRegistration = $enforceInlineRegistration;
  }

    public function getEnableOTPinsteadPassword() {
        return $this->enableOTP_instead_password;
    }

    private function setEnableOTPinsteadPassword($enableOTP_instead_password) {
        $this->enableOTP_instead_password = $enableOTP_instead_password;
    }

  /**
   * @return |null
   */
  public function getEnablePasswordChecks()
  {
    return $this->enablePasswordChecks;
  }

  /**
   * @return |null
   */
  public function getLastNUniquePassword()
  {
    return $this->lastNUniquePassword;
  }

  /**
   * @return |null
   */
  public function getPasswordMaxLength()
  {
    return $this->passwordMaxLength;
  }

  /**
   * @return |null
   */
  public function getPasswordMinLength()
  {
    return $this->passwordMinLength;
  }

  /**
   * @return |null
   */
  public function getPasswordMustHaveLowChar()
  {
    return $this->passwordMustHaveLowChar;
  }

  /**
   * @return |null
   */
  public function getPasswordMustHaveUpChar()
  {
    return $this->passwordMustHaveUpChar;
  }

  /**
   * @return |null
   */
  public function getPasswordMustHaveNumChar()
  {
    return $this->passwordMustHaveNumChar;
  }

  /**
   * @return |null
   */
  public function getPasswordMustHaveSpecialChar()
  {
    return $this->passwordMustHaveSpecialChar;
  }

  /**
   * @return |null
   */
  public function getPasswordMustNotBeEnabled()
  {
    return $this->passwordMustNotBeEnabled;
  }

  /**
   * @return |null
   */
  public function getPasswordMustNotBeRules()
  {
    return $this->passwordMustNotBeRules;
  }

  /**
   * @return |null
   */
  public function getPasswordMustNotBeEmail()
  {
    return $this->passwordMustNotBeEmail;
  }

  /**
   * @return |null
   */
  public function getPasswordMustNotBeFname()
  {
    return $this->passwordMustNotBeFname;
  }

  /**
   * @return |null
   */
  public function getPasswordMustNotBeLname()
  {
    return $this->passwordMustNotBeLname;
  }

  /**
   * @return |null
   */
  public function getMachineNameOfFname()
  {
    return $this->machineNameOfFname;
  }

  /**
   * @return |null
   */
  public function getMachineNameOfLname()
  {
    return $this->machineNameOfLname;
  }




}
