<?php
/**
 * @file
 * wim_slider.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function wim_slider_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "bean_admin_ui" && $api == "bean") {
    return ["version" => "5"];
  }
  if ($module == "picture" && $api == "default_picture_mapping") {
    return ["version" => "2"];
  }
}

/**
 * Implements hook_paragraphs_info().
 */
function wim_slider_paragraphs_info() {
  $items = [
    'slider_item' => [
      'name' => 'Slider item',
      'bundle' => 'slider_item',
      'locked' => '1',
    ],
  ];
  return $items;
}
