<?php
/**
 * @file
 * wim_breadcrumb.features.hansel.inc
 */

/**
 * Implements hook_hansel_default().
 */
function wim_breadcrumb_hansel_default() {
  $elements = [];
  $elements['config'] = [
    'version' => 1,
    'start_rid' => 1,
    'rules' => [
      1 => [
        'rid' => 1,
        'pid' => NULL,
        'name' => 'start',
        'crumb_action' => 'add single link',
        'crumb_action_arguments' => [
          'title' => 'Home',
          'translate' => 0,
          'remove_tokens' => 0,
          'path' => '<front>',
          'skipalias' => 0,
        ],
        'action' => 'switch',
        'handler' => 'url argument',
        'arguments' => [],
        'children' => [
          0 => 3,
          1 => 6,
        ],
      ],
      2 => [
        'rid' => 2,
        'pid' => 5,
        'name' => '<default>',
        'crumb_action' => 'add link to current page',
        'crumb_action_arguments' => [],
        'action' => 'leave',
        'restore' => FALSE,
        'children' => [],
      ],
      3 => [
        'rid' => 3,
        'pid' => 1,
        'name' => '<default>',
        'crumb_action' => '',
        'crumb_action_arguments' => [],
        'action' => 'switch',
        'handler' => 'node type',
        'arguments' => [],
        'children' => [
          0 => 5,
        ],
      ],
      4 => [
        'rid' => 4,
        'pid' => 4,
        'name' => '<default>',
        'crumb_action' => 'add parents',
        'crumb_action_arguments' => [],
        'action' => 'switch',
        'handler' => 'url argument',
        'arguments' => [],
        'children' => [
          0 => 4,
        ],
      ],
      5 => [
        'rid' => 5,
        'pid' => 3,
        'name' => '<default>',
        'crumb_action' => 'add parents',
        'crumb_action_arguments' => [],
        'action' => 'switch',
        'handler' => 'url argument',
        'arguments' => [],
        'children' => [
          0 => 2,
          1 => 8,
        ],
      ],
      6 => [
        'rid' => 6,
        'pid' => 1,
        'name' => 'faq',
        'crumb_action' => 'add single link',
        'crumb_action_arguments' => [
          'title' => 'FAQ',
          'translate' => 1,
          'remove_tokens' => 0,
          'path' => 'faq',
          'skipalias' => 0,
        ],
        'action' => 'switch',
        'handler' => 'request uri',
        'arguments' => [
          'mode' => 0,
          'cs' => 0,
        ],
        'children' => [
          0 => 7,
        ],
      ],
      7 => [
        'rid' => 7,
        'pid' => 6,
        'name' => 'faq/',
        'crumb_action' => 'add link to current page',
        'crumb_action_arguments' => [],
        'action' => 'leave',
        'restore' => FALSE,
        'children' => [],
      ],
      8 => [
        'rid' => 8,
        'pid' => 5,
        'name' => 'node',
        'crumb_action' => 'add link to node',
        'crumb_action_arguments' => [],
        'action' => 'leave',
        'restore' => FALSE,
        'children' => [],
      ],
    ],
    'nodetypes' => [
      'agenda' => [
        'path' => 'agenda',
        'title' => 'Agenda',
      ],
      'faq' => [
        'path' => 'faq',
        'title' => 'FAQ',
      ],
      'news' => [
        'path' => 'news',
        'title' => 'News',
      ],
    ],
  ];
  $elements['settings'] = [
    'variables' => [
      'hansel_breadcrumb_last_item_hide' => 0,
      'hansel_breadcrumb_last_item_link' => 1,
      'hansel_cache' => 0,
      'hansel_cache_whole' => 0,
      'hansel_max_item_count' => 0,
      'hansel_max_item_length' => 0,
      'hansel_nodetypes' => [
        'agenda' => [
          'path' => 'agenda',
          'title' => 'Agenda',
        ],
        'faq' => [
          'path' => 'faq',
          'title' => 'FAQ',
        ],
        'news' => [
          'path' => 'news',
          'title' => 'News',
        ],
      ],
      'hansel_parent_lookup_paths' => 0,
      'hansel_removed_items_replacement' => '(...)',
      'hansel_remove_first_token_item' => 1,
      'hansel_set_menu_item' => 1,
      'hansel_set_menu_item_skip_first' => 1,
      'hansel_set_menu_name' => 0,
      'hansel_trim_ellipsis' => '...',
      'hansel_trim_on_word_boundary' => 1,
    ],
  ];
  return $elements;
}
