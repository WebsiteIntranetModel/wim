<?php

/**
 * @file
 * Describe hooks provided by the Cookie Consent module.
 */

/**
 * This hook lets you provide your own categories for Cookie Consent.
 */
function hook_cookie_consent_categories() {
  $cookies = [];

  // Make sure that the key does not contain spaces.
  $cookies['mycategory'] = [
    'title' => t('My Category Title'),
    'description' => t('My Category Description.'),
  ];

  return $cookies;
}
