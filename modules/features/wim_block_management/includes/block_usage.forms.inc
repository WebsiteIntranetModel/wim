<?php

/**
 * @file
 * Settings form for wim_block_management module.
 */

/**
 * Block Usage settings form.
 *
 * @return array
 *   An associative array that defines the form to be built.
 */
function block_usage_settings() {
  $form = [];

  $form['block_usage_results'] = [
    '#type' => 'fieldset',
    '#title' => t('Block usage settings'),
    '#weight' => 0,
    '#collapsible' => FALSE,
  ];

  $form['block_usage_results']['block_usage_results_per_page'] = [
    '#title' => t('Results per page'),
    '#description' => t('How many results display per page on the block usage page'),
    '#type' => 'select',
    '#options' => drupal_map_assoc(range(5, 50, 5)),
    '#default_value' => variable_get('block_usage_results_per_page', 30),
  ];

  $form['block_usage_results']['block_usage_results_type'] = [
    '#title' => t('Usage block modules'),
    '#description' => t('Select modules which blocks should be displayed in the common usage list'),
    '#type' => 'select',
    '#multiple' => TRUE,
    '#options' => get_modules_usage_blocks(),
    '#default_value' => variable_get('block_usage_results_type'),
  ];

  return system_settings_form($form);
}

/**
 * Filter form for block usage view.
 *
 * @return array
 *    An associative array that defines the form filters.
 */
function block_usage_filters() {
  $filters = drupal_get_query_parameters();
  $form = [];

  $form['block_usage_filter'] = [
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#weight' => 0,
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  ];

  $options = variable_get('block_usage_results_type', get_modules_usage_blocks());

  asort($options);
  $multiple = TRUE;

  $form['block_usage_filter']['block_usage_filter_type'] = [
    '#type' => 'select',
    '#prefix' => '<div style="margin-right:10px; position:relative; float:left;">',
    '#suffix' => '</div>',
    '#multiple' => $multiple,
    '#size' => $multiple ? min(4, count($options)) : 0,
    '#title' => t('Filter type'),
    '#description' => t('Choose the block types to filter the list of results.'),
    '#options' => $options,
    '#default_value' => empty($filters['type']) ? '' : explode(',', $filters['type']),
  ];
  $form['block_usage_filter']['block_usage_status'] = [
    '#type' => 'radios',
    '#prefix' => '<div style="margin-right:10px; position:relative; float:left;">',
    '#suffix' => '</div>',
    '#title' => t('Usage status'),
    '#title_display' => 'before',
    '#options' => [
      1 => t('All'),
      2 => t('Used'),
      3 => t('Not used'),
    ],
    '#default_value' => !empty($filters['status']) ? $filters['status'] : 1,
  ];
  $form['block_usage_filter']['block_usage_filter_title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#prefix' => '<div style="margin-right:10px; position:relative; float:left;">',
    '#suffix' => '</div>',
    '#default_value' => !empty($filters['title']) ? $filters['title'] : '',
  ];
  $form['block_usage_filter']['block_usage_filter_delta'] = [
    '#type' => 'textfield',
    '#title' => t('Delta'),
    '#prefix' => '<div style="margin-right:10px; position:relative; float:left;">',
    '#suffix' => '</div>',
    '#default_value' => !empty($filters['delta']) ? $filters['delta'] : '',
  ];

  $form['block_usage_filter']['actions'] = [
    '#type' => 'actions',
    '#prefix' => '<div style="position:relative; float:left;">',
    '#suffix' => '</div>',
  ];

  $form['block_usage_filter']['actions']['apply'] = [
    '#type' => 'submit',
    '#value' => t('Apply'),
    '#name' => 'apply_filter',
  ];

  $form['block_usage_filter']['actions']['reset'] = [
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#name' => 'reset_filter',
  ];

  return $form;
}

/**
 * Submit function for block_usage_filters()
 *
 * Applies the filter via a redirect back to the block usage view page with the
 * added filter query param.
 *
 * @param array $form
 *   The filters form.
 * @param array $form_state
 *   The form state array.
 */
function block_usage_filters_submit(&$form, &$form_state) {
  // Get the query string parameters minus the drupal url and filter param.
  $params = drupal_get_query_parameters($_GET, ['q', 'filter']);

  // Add the filters to the query string.
  $filters = [
    'type' => implode(',', $form_state['values']['block_usage_filter_type']),
    'title' => $form_state['values']['block_usage_filter_title'],
    'delta' => $form_state['values']['block_usage_filter_delta'],
    'status' => $form_state['values']['block_usage_status'],
  ];

  if ($form_state['values']['apply_filter']) {
    foreach ($filters as $filter_name => $filter_value) {
      if (!empty($filter_value)) {
        $params[$filter_name] = $filter_value;
      }
    }
  }

  if ($form_state['values']['reset_filter']) {
    $params = [];
  }

  // Redirect back to block usage view with added filter query string param.
  drupal_goto($_GET['q'], ['query' => $params]);
}
