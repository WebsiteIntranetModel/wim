<?php
/**
 * @file
 * wim_product.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_product_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return ["version" => "1"];
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return ["version" => "1"];
  }
}

/**
 * Implements hook_node_info().
 */
function wim_product_node_info() {
  $items = [
    'product' => [
      'name' => t('Product'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ],
  ];
  drupal_alter('node_info', $items);
  return $items;
}
