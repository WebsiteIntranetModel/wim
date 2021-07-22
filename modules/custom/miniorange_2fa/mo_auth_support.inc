<?php
/**
 * @file
 * Contains support form for miniOrange 2FA Login Module.
 */

 /**
 *  Showing Support form info.
 */
function mo_auth_support($form, &$form_state) {

    drupal_add_js(drupal_get_path('module', 'mo_auth') . '/includes/js/Phone.js', 'file');
    drupal_add_css( drupal_get_path('module', 'mo_auth'). '/includes/css/phone.css' , array('group' => CSS_DEFAULT, 'every_page' => FALSE));

    $form['markup_1'] = array(
        '#markup' => '<div class="mo2f_table_layout_1"><div class="mo2f_table_layout mo2f_container"><h3>Support/New feature Request </h3><hr><div><br/>Need any help? Just send us a query so we can help you.<br /><br /></div>',
    );

    $form['miniorange_2fa_email_address'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#attributes' => array('placeholder' => 'Enter your email'),
        '#required' => TRUE,
        '#default_value' => variable_get('mo_auth_customer_admin_email', ''),
    );

    $form['miniorange_2fa_phone_number'] = array(
        '#type' => 'textfield',
        '#title' => t('Phone'),
        '#id' => 'query_phone',
        '#attributes' => array('class'=>array('query_phone'),),
        '#default_value' => variable_get('mo_auth_customer_admin_phone', ''),
    );

    $form['miniorange_2fa_support_query'] = array(
        '#type' => 'textarea',
        '#title' => t('Query'),
        '#attributes' => array('placeholder' => 'Write your query here'),
        '#required' => TRUE,
        '#prefix' => '<div style="width:60%">',
        '#suffix' => '</div>'
    );

    $form['miniorange_2fa_support_submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit Query'),
        '#submit' => array('mo_auth_support_submit'),
    );

    $form['miniorange_2fa_support_note'] = array(
        '#markup' => '<div><br/>If you want custom features in the module, just drop an email to <a href="mailto:drupalsupport@xecurify.com">drupalsupport@xecurify.com</a></div>'
    );

    return $form;
 }

 /**
  *  Send support query.
  */
function mo_auth_support_submit($form, &$form_state) {
    $email = $form['miniorange_2fa_email_address']['#value'];
    $phone = $form['miniorange_2fa_phone_number']['#value'];
    $query = $form['miniorange_2fa_support_query']['#value'];
    MoAuthUtilities::send_support_query($email, $phone, $query);
}