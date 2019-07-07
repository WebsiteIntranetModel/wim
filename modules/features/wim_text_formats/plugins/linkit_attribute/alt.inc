<?php
/**
 * @file
 * Define Linkit alt attribute plugin.
 */

$plugin = [
  'name' => t('Alt'),
  'callback' => 'linkit_attribute_plugin_alt',
];

/**
 * Create a FAPI element.
 *
 * @param array $plugin
 *   This is the plugin definition.
 * @param array $settings
 *   An array of settings for this attribute. This is from the profile settings.
 *
 * @return array
 *   An FAPI element.
 *
 * @see LinkitProfile::setAttributes()
 */
function linkit_attribute_plugin_alt($plugin, $settings = []) {
  return [
    '#type' => 'textfield',
    '#title' => $plugin['name'],
    '#maxlength' => 255,
    '#size' => 40,
    '#default_value' => '',
    '#weight' => isset($settings['weight']) ? $settings['weight'] : 0,
  ];
}
