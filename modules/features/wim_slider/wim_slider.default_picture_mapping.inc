<?php
/**
 * @file
 * wim_slider.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function wim_slider_default_picture_mapping() {
  $export = array();

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Slider';
  $picture_mapping->machine_name = 'slider';
  $picture_mapping->breakpoint_group = 'wim';
  $picture_mapping->mapping = array(
    'breakpoints.theme.wim.wide' => array(
      '1x' => array(
        'mapping_type' => '_none',
      ),
    ),
    'breakpoints.theme.wim.desktop' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'slider_desktop',
      ),
    ),
    'breakpoints.theme.wim.tablet' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'slider_tablet',
      ),
    ),
    'breakpoints.theme.wim.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'slider_mobile',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'slider_tablet',
      ),
    ),
  );
  $export['slider'] = $picture_mapping;

  return $export;
}
