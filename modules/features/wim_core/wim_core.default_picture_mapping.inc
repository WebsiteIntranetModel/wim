<?php
/**
 * @file
 * wim_core.default_picture_mapping.inc
 */

/**
 * Implements hook_default_picture_mapping().
 */
function wim_core_default_picture_mapping() {
  $export = array();

  $picture_mapping = new PictureMapping();
  $picture_mapping->disabled = FALSE; /* Edit this to true to make a default picture_mapping disabled initially */
  $picture_mapping->api_version = 2;
  $picture_mapping->label = 'Teaser Responsive';
  $picture_mapping->machine_name = 'teaser_responsive';
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
        'image_style' => 'teaser',
      ),
    ),
    'breakpoints.theme.wim.tablet' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser',
      ),
    ),
    'breakpoints.theme.wim.mobile' => array(
      '1x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_mobile',
      ),
      '2x' => array(
        'mapping_type' => 'image_style',
        'image_style' => 'teaser_mobile_retina',
      ),
    ),
  );
  $export['teaser_responsive'] = $picture_mapping;

  return $export;
}
