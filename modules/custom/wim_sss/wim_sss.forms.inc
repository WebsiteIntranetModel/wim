<?php
/**
 * @file
 * Contains node form alters.
 */

/**
 * Add option for each content type to render social sharing links.
 *
 * @param array $form
 *    Node settings form.
 */
function _wim_sss_process_node_settings_form(&$form) {

  // Do not process node form if it do not contain node type.
  if (empty($form['#node_type']->type)) {
    return;
  }

  $node_type = $form['#node_type']->type;

  $form['wim_sss'] = array(
    '#type'   => 'fieldset',
    '#title'  => t('Social share links'),
    '#group'  => 'additional_settings',
  );

  // Enable render.
  $form['wim_sss']['wim_sss_node_enabled'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Enable social sharing links'),
    '#default_value' => variable_get('wim_sss_node_enabled_' . $node_type),
    '#description'   => t('Enable or disable output for this node type.'),
  );
}
