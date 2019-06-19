<?php
/**
 * @file
 * wim_slider.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function wim_slider_default_picture_mapping() {
  $export = [];

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Slider';
  $picture_mapping->machine_name = 'slider';
  $picture_mapping->breakpoint_group = 'wim';
  $picture_mapping->mapping = [
    'breakpoints.theme.wim.wide' => [
      '1x' => [
        'mapping_type' => '_none',
      ],
    ],
    'breakpoints.theme.wim.desktop' => [
      '1x' => [
        'mapping_type' => 'image_style',
        'image_style' => 'slider_desktop',
      ],
    ],
    'breakpoints.theme.wim.tablet' => [
      '1x' => [
        'mapping_type' => 'image_style',
        'image_style' => 'slider_tablet',
      ],
    ],
    'breakpoints.theme.wim.mobile' => [
      '1x' => [
        'mapping_type' => 'image_style',
        'image_style' => 'slider_mobile',
      ],
      '2x' => [
        'mapping_type' => 'image_style',
        'image_style' => 'slider_tablet',
      ],
    ],
  ];
  $export['slider'] = $picture_mapping;

  return $export;
}
