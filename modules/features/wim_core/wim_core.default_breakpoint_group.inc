<?php
/**
 * @file
 * wim_core.default_breakpoint_group.inc
 */

/**
 * Implements hook_default_breakpoint_group().
 */
function wim_core_default_breakpoint_group() {
  $export = [];

  $breakpoint_group = new stdClass();
  $breakpoint_group->disabled = FALSE; /* Edit this to true to make a default breakpoint_group disabled initially */
  $breakpoint_group->api_version = 1;
  $breakpoint_group->machine_name = 'wim';
  $breakpoint_group->name = 'WIM base theme';
  $breakpoint_group->breakpoints = [
    0 => 'breakpoints.theme.wim.wide',
    1 => 'breakpoints.theme.wim.desktop',
    2 => 'breakpoints.theme.wim.tablet',
    3 => 'breakpoints.theme.wim.mobile',
  ];
  $breakpoint_group->type = 'theme';
  $breakpoint_group->overridden = 0;
  $export['wim'] = $breakpoint_group;

  return $export;
}
