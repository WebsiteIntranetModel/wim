<?php
/**
 * @file
 * The primary PHP file for the WIM STARTERKIT theme.
 *
 * This file should only contain light helper functions and point to stubs in
 * other files containing more complex functions.
 */

$includes = drupal_get_path('theme', 'STARTERKIT') . '/includes/';

// Include preprocess.
require_once $includes . 'preprocess.inc';
// Include alter.
require_once $includes . 'alter.inc';
// Include theme.
require_once $includes . 'theme.inc';
