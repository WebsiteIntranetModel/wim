<?php

require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
class MoAuthPasswordValidator
{

  private $numberOfUniquePasswords;
  private $plainPassword;
  private $user;

  function __construct($plainPassword,$account)
  {
    $this->numberOfUniquePasswords = variable_get('MoAuthnumberOfUniquePasswords',0);
    $this->user = $account;
    $this->plainPassword = $plainPassword;
  }


  function isPasswordUnique(){
    $lastNPasswords = $this->lastNPasswordsInDB();
    foreach ($lastNPasswords as $key=>$value){
      $tempuser = $this->user;
      $tempuser->pass = $value->pass;
      if(user_check_password($this->plainPassword,$tempuser))
        return FALSE;
    }
    return TRUE;
  }
  function insertTheNewPassword($password){

  }

  function lastNPasswordsInDB(){

    $result = db_query('Select * from {mo_auth_user_track} where uid='.$this->user->uid)->fetchAllAssoc('id');


    if(!$this->isLastPasswordInserted($result)){
      // insert the last password
      $loginSettings = new MoAuthLoginSettings();
      // remove last password
      $minId = db_query('select min(id) from {mo_auth_user_track} where uid='.$this->user->uid )->fetchCol();

      if(count($result)>=$loginSettings->getLastNUniquePassword()){
        db_query('delete from {mo_auth_user_track} where uid='.$this->user->uid.' and id='.$minId[0])->execute();
      }
      db_insert('mo_auth_user_track')
        ->fields(array(
          'uid' => $this->user->uid,
          'pass' => $this->user->pass,
        ))
        ->execute();
      $currentPassword = new stdClass();
      $currentPassword->id  = -1;
      $currentPassword->uid = $this->user->uid;
      $currentPassword->pass  = $this->user->pass;
      array_push($result,$currentPassword);

    }

    return $result;
  }

  function isLastPasswordInserted($result){
    foreach ($result as $key=>$value){
      if($value->pass == $this->user->pass){
        return TRUE;
      }
    }
    return FALSE;
  }


  function passwordMustNotBeRules(){
    $loginSettings = new MoAuthLoginSettings();
    $rulesResult = array();
    if( $loginSettings->getPasswordMustNotBeEnabled() ){
      $rules = explode(';',$loginSettings->getPasswordMustNotBeRules());
      foreach ($rules as $rule){
        $rulesResult[] = $this->getRuleValue($rule);
      }
    }
    return $rulesResult;
  }

  function getRuleValue( $rule ){
    $ruleParts = explode("+",$rule);
    $cUser = user_load($this->user->uid);
    $labels = array();
    $value  = "";

    foreach ($ruleParts as $rule){
      if(strpos($rule,"field_")!==FALSE){
        $label = str_replace("_","",str_replace("field_","",$rule));
      }
      else{
        $label = $rule;
      }
      $labels[] = $label;
      $ruleValue = isset($cUser->$rule)?$cUser->$rule:FALSE;

      if($ruleValue!==FALSE && isset($ruleValue['und'][0]['value'])){
        $value = $value.strval($ruleValue['und'][0]['value']);
      }

    }
    $ruleName = "Password must not be same as ";
    if(count($labels)>1){
      $ruleName .= "concatenation of ";
    }
    $ruleName = $ruleName. implode(',',$labels);
    return array($ruleName,strcasecmp($value,$this->plainPassword)===0);

  }








}
