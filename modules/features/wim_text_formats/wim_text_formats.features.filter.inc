<?php
/**
 * @file
 * wim_text_formats.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function wim_text_formats_filter_default_formats() {
  $formats = [];

  // Exported format: Filtered HTML.
  $formats['filtered_html'] = [
    'format' => 'filtered_html',
    'name' => 'Filtered HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => [
      'filter_html' => [
        'weight' => -10,
        'status' => 1,
        'settings' => [
          'allowed_html' => '<a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <th> <td> <thead> <tbody> <tfoot> <caption> <h2> <h3> <h4> <h5> <h6> <p> <br> <b> <i> <u> <abbr> <acronym> <object> <embed> <param> <span> <iframe> <area> <map> <img>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ],
      ],
      'filter_url' => [
        'weight' => 0,
        'status' => 1,
        'settings' => [
          'filter_url_length' => 72,
        ],
      ],
      'filter_autop' => [
        'weight' => 2,
        'status' => 1,
        'settings' => [],
      ],
      'media_filter' => [
        'weight' => 2,
        'status' => 1,
        'settings' => [],
      ],
      'filter_htmlcorrector' => [
        'weight' => 10,
        'status' => 1,
        'settings' => [],
      ],
    ],
  ];

  // Exported format: Full HTML.
  $formats['full_html'] = [
    'format' => 'full_html',
    'name' => 'Full HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => [
      'filter_url' => [
        'weight' => -47,
        'status' => 1,
        'settings' => [
          'filter_url_length' => 72,
        ],
      ],
      'filter_autop' => [
        'weight' => -42,
        'status' => 1,
        'settings' => [],
      ],
      'media_filter' => [
        'weight' => -41,
        'status' => 1,
        'settings' => [],
      ],
      'filter_html' => [
        'weight' => -10,
        'status' => 1,
        'settings' => [
          'allowed_html' => '<div> <a> <em> <strong> <cite> <blockquote> <code> <ul> <ol> <li> <dl> <dt> <dd> <table> <tr> <th> <td> <thead> <tbody> <tfoot> <caption> <h2> <h3> <h4> <h5> <h6> <p> <br> <b> <i> <u> <abbr> <acronym> <object> <embed> <param> <span> <iframe> <area> <map> <img>',
          'filter_html_help' => 1,
          'filter_html_nofollow' => 0,
        ],
      ],
      'filter_htmlcorrector' => [
        'weight' => 10,
        'status' => 1,
        'settings' => [],
      ],
    ],
  ];

  // Exported format: Plain text.
  $formats['plain_text'] = [
    'format' => 'plain_text',
    'name' => 'Plain text',
    'cache' => 1,
    'status' => 1,
    'weight' => 10,
    'filters' => [
      'filter_html_escape' => [
        'weight' => 0,
        'status' => 1,
        'settings' => [],
      ],
      'filter_url' => [
        'weight' => 1,
        'status' => 1,
        'settings' => [
          'filter_url_length' => 72,
        ],
      ],
      'filter_autop' => [
        'weight' => 2,
        'status' => 1,
        'settings' => [],
      ],
    ],
  ];

  return $formats;
}
