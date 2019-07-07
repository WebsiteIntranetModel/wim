<?php
/**
 * @file
 * Administration pages code.
 */

/**
 * Admin settings form.
 */
function content_reminder_admin_form($form, &$form_state) {

  module_load_include('inc', 'content_reminder', 'content_reminder');
  $types = node_type_get_types();

  $form['description'] = [
    '#type' => 'item',
    '#title' => t('A form to configure content reminders for each content types.'),
  ];
  $form['content_reminder_reminder_subject'] = [
    '#type' => 'textfield',
    '#title' => t('Subject for content reminder mails'),
    '#default_value' => variable_get('content_reminder_reminder_subject', 'Je moet @count item(s) bekijken'),
    '#description' => t('The token %token will be replaced by the number of nodes.', ['%token' => '@count']),
  ];
  $form['content_reminder_reminder_text'] = [
    '#type' => 'textarea',
    '#title' => t('Text for content reminder mails'),
    '#default_value' => variable_get('content_reminder_reminder_text', 'Inhoud die verlopen is of binnenkort verloopt.'),
  ];
  $form['content_reminder_expire_subject'] = [
    '#type' => 'textfield',
    '#title' => t('Subject for expired content mails'),
    '#default_value' => variable_get('content_reminder_expire_subject', '@count item(s) zijn verlopen en offline geplaatst'),
    '#description' => t('The token %token will be replaced by the number of nodes.', ['%token' => '@count']),
  ];
  $form['content_reminder_expire_text'] = [
    '#type' => 'textarea',
    '#title' => t('Text for expired content mails'),
    '#default_value' => variable_get('content_reminder_expire_text', 'Inhoud die verlopen is of binnenkort verloopt.'),
  ];
  $form['description'] = [
    '#type' => 'item',
    '#title' => t('A form to configure content reminders for each content types.'),
  ];
  foreach ($types as $type) {
    $form['tab_cr_' . $type->type] = [
      '#type' => 'fieldset',
      '#title' => $type->name,
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    ];
    $form['tab_cr_' . $type->type]['content_reminder_types_' . $type->type] = [
      '#type' => 'checkbox',
      '#title' => t('Send reminder e-mail?'),
      '#default_value' => variable_get('content_reminder_types_' . $type->type, 0),
    ];
    $form['tab_cr_' . $type->type]['content_reminder_types_' . $type->type . '_days'] = [
      '#type' => 'textfield',
      '#title' => t('Days to e-mail reminder'),
      '#default_value' => variable_get('content_reminder_types_' . $type->type . '_days', 182),
      '#maxlength' => 255,
      '#element_validate' => ['element_validate_number'],
    ];
    $form['tab_cr_' . $type->type]['content_reminder_types_' . $type->type . '_depub_box'] = [
      '#type' => 'checkbox',
      '#title' => t('Unpublish content when expired?'),
      '#default_value' => variable_get('content_reminder_types_' . $type->type . '_depub_box', 0),
    ];
    $form['tab_cr_' . $type->type]['content_reminder_types_' . $type->type . '_depub'] = [
      '#type' => 'textfield',
      '#title' => t('Days to expired content.'),
      '#default_value' => variable_get('content_reminder_types_' . $type->type . '_depub', 213),
      '#maxlength' => 255,
      '#element_validate' => ['element_validate_number'],
    ];
  }

  return system_settings_form($form);
}
