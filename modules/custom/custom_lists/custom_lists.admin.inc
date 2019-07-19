<?php
/**
 * @file
 * Administration pages code.
 */

/**
 * Callback for 'admin/structure/lists'.
 */
function custom_lists_admin() {
  // Setup some default data.
  $types = node_type_get_names();
  $lists = custom_lists_get();

  // Setup the rows to show in the table.
  $rows = [];
  foreach ($lists as $list_key => $list) {
    $row = [];
    $row[] = $list['title'];
    $row[] = $list['provide-page'] ? l($list['path'], $list['path']) : t('No');
    $row[] = $list['provide-block'] ? t('Yes') : t('No');
    $row[] = ucfirst($list['type']);

    $data = [];
    if ($list['type'] == 'content') {
      if ($list['node-type'] != '_any') {
        $data[] = t('Type: !type', ['!type' => $types[$list['node-type']]]);
      }
      if (!empty($list['taxonomy'])) {
        $terms = [];
        foreach ($list['taxonomy'] as $term_id) {
          $term = taxonomy_term_load($term_id);
          $terms[] = l($term->name, 'taxonomy/term/' . $term->tid);
        }
        $data[] = t('Taxonomy: !terms', ['!terms' => implode($terms, ',')]);
      }
    }
    else {
      if ($list['type'] == 'menu') {
        $menu_item = menu_link_load($list['menu-item']);
        $data[] = t('Menu parent: !parent', ['!parent' => l($menu_item['link_title'], $menu_item['link_path'])]);
      }
    }
    $row[] = implode(',', $data);

    $row[] = l(t('Edit'), 'admin/structure/lists/edit/' . $list_key) . ' | ' . l(t('Delete'), 'admin/structure/lists/delete/' . $list_key);

    $rows[] = $row;
  }

  return theme('table', [
    'header' => [
      t('TItle'),
      t('Page'),
      t('Block'),
      t('Type'),
      t('Data'),
      t('Operations'),
    ],
    'rows' => $rows,
  ]);
}

/**
 * Callback for 'admin/structure/lists/delete/%id.
 */
function custom_lists_delete_form($form, &$form_state, $list_key) {
  $lists = custom_lists_get();
  $form['#listkey'] = $list_key;

  return confirm_form($form, t('Are you sure you want to delete the list !list?', ['!list' => $lists[$list_key]['path']]), 'admin/structure/lists');
}

/**
 * Delete callback for custom_list_delete_form.
 */
function custom_lists_delete_form_submit($form, &$form_state) {
  custom_lists_delete($form['#listkey']);
  drupal_set_message(t('The list has been removed.'));
  $form_state['redirect'] = 'admin/structure/lists';
}

/**
 * Form for the add list.
 */
function custom_lists_list_form($form, &$form_state, $list_key = NULL) {
  $list = [];
  if ($list_key) {
    $lists = custom_lists_get();
    $list = $lists[$list_key];
  }

  $form['general'] = [
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#tree' => FALSE,
    '#attached' => [
      'css' => [
        drupal_get_path('module', 'custom_lists') . '/custom_lists.css',
      ],
      'js' => [
        drupal_get_path('module', 'custom_lists') . '/custom_lists.js',
      ],
    ],
  ];

  $form['general']['title'] = [
    '#type' => 'textfield',
    '#title' => t('Administration title'),
    '#size' => 30,
    '#required' => TRUE,
    '#description' => t('This title is only used on admin pages to identify the custom list.'),
    '#default_value' => !empty($list['title']) ? $list['title'] : '',
  ];

  $form['general']['display_title'] = [
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 30,
    '#required' => TRUE,
    '#description' => t('This title is used as block and page title.'),
    '#default_value' => !empty($list['display_title']) ? $list['display_title'] : '',
  ];

  if (!empty($list_key)) {
    $form['general']['key'] = [
      '#type' => 'hidden',
      '#title' => t('Key'),
      '#required' => TRUE,
      '#default_value' => $list_key,
    ];
  }
  $form['general']['type'] = [
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => [
      'content' => t('Content'),
      'menu' => t('Menu'),
    ],
    '#default_value' => !empty($list['type']) ? $list['type'] : 'content',
  ];

  $form['type-settings'] = [
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => FALSE,
  ];

  // Node type data.
  $types = node_type_get_names();
  $form['type-settings']['node-type'] = [
    '#type' => 'select',
    '#title' => t('Nodetype'),
    '#options' => ['_any' => t('Any')] + node_type_get_names(),
    '#default_value' => !empty($list['node-type']) ? $list['node-type'] : '_any',
    '#attributes' => [
      'class' => [
        'type-setting',
        'type-setting-content',
      ],
    ],
  ];

  $queues_list = [];
  $queues = nodequeue_load_queues(nodequeue_get_all_qids());

  if ($queues) {
    foreach ($queues as $queue) {
      $queues_list[$queue->qid] = $queue->title;
    }
  }

  $form['type-settings']['node-queues'] = [
    '#type' => 'select',
    '#title' => t('Nodequeue'),
    '#options' => ['_any' => t('Any')] + $queues_list,
    '#default_value' => !empty($list['node-queues']) ? $list['node-queues'] : '_any',
    '#attributes' => [
      'class' => [
        'type-setting',
        'type-setting-content',
      ],
    ],
  ];

  $form['type-settings']['taxonomy'] = [
    '#type' => 'select',
    '#multiple' => TRUE,
    '#title' => t('Terms'),
    '#chosen' => TRUE,
    '#options' => _custom_lists_get_terms(),
    '#default_value' => isset($list['taxonomy']) ? $list['taxonomy'] : [],
    '#attributes' => [
      'class' => [
        'type-setting',
        'type-setting-content',
      ],
      'data-placeholder' => t('Select terms'),
    ],
  ];
  $form['type-settings']['extra-filters'] = [
    '#type' => 'select',
    '#title' => t('Filters'),
    '#default_value' => !empty($list['extra-filters']) ? $list['extra-filters'] : '_none',
    '#options' => [
      '_none' => t('No filter'),
      'node_type_agenda_upcoming' => t('Agenda: Upcoming'),
    ],
  ];

  $form['type-settings']['sort'] = [
    '#type' => 'select',
    '#title' => t('Sort'),
    '#options' => [
      'created_desc' => t('Post date: newest first'),
      'created_asc' => t('Post date: oldest first'),
      'changed_desc' => t('Changed date: newest first'),
      'changed_asc' => t('Changed date: oldest first'),
      'title_asc' => t('Title: ascending'),
      'title_desc' => t('Title: descending'),
      'queue_asc' => t('Nodequeue: ascending'),
      'queue_desc' => t('Nodequeue: descending'),
      'agenda_asc' => t('Agenda date: ascending'),
      'agenda_desc' => t('Agenda date: descending'),
      'weight_desc' => t('Weight: descending'),
      'weight_asc' => t('Weight: ascending'),
    ],
    '#default_value' => !empty($list['sort']) ? $list['sort'] : '',
    '#attributes' => [
      'class' => [
        'type-setting',
        'type-setting-content',
      ],
    ],
  ];

  // Setup view modes.
  $modes = ['titles' => t('Titles as link')];
  $entity_info = entity_get_info('node');

  // Filter out view modes like rss and search result.
  $view_modes = _custom_lists_filter_view_modes($entity_info['view modes']);
  foreach ($view_modes as $view_mode => $data) {
    $modes[$view_mode] = $data['label'];
  }

  // Menu type data.
  // Generate a list of possible parents.
  $options = _custom_lists_menu_options();
  $form['type-settings']['menu-item'] = [
    '#type' => 'select',
    '#title' => t('Menu Parent'),
    '#options' => $options,
    '#default_value' => !empty($list['menu-item']) ? $list['menu-item'] : '',
    '#attributes' => [
      'class' => [
        'type-setting',
        'type-setting-menu',
        'menu-title-select',
      ],
    ],
  ];

  // Provide Block.
  $form['block'] = [
    '#type' => 'fieldset',
    '#title' => t('Block'),
    '#tree' => FALSE,
  ];
  $form['block']['provide-block'] = [
    '#type' => 'checkbox',
    '#title' => t('Provide block'),
    '#default_value' => isset($list['provide-block']) ? $list['provide-block'] : FALSE,
  ];
  $form['block']['block-view-mode'] = [
    '#type' => 'select',
    '#title' => t('View mode'),
    '#options' => $modes,
    '#default_value' => !empty($list['block-view-mode']) ? $list['block-view-mode'] : 'titles',
    '#attributes' => [
      'class' => [
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ],
    ],
  ];
  $form['block']['block-items'] = [
    '#type' => 'textfield',
    '#title' => t('# Items'),
    '#required' => TRUE,
    '#default_value' => !empty($list['block-items']) ? $list['block-items'] : 5,
    '#size' => 5,
    '#attributes' => [
      'class' => [
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ],
    ],
  ];
  $form['block']['show-more-link'] = [
    '#type' => 'select',
    '#title' => t('Show more link'),
    '#options' => [
      'hide' => t('Hide'),
      'default' => t('Default (Links to page)'),
      'custom' => t('Custom (Provide custom uri)'),
    ],
    '#default_value' => !empty($list['show-more-link']) ? $list['show-more-link'] : 'default',
    '#attributes' => [
      'class' => [
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ],
    ],
  ];
  $form['block']['more-link'] = [
    '#type' => 'textfield',
    '#title' => t('Custom more link'),
    '#description' => t("Fill in the Drupal URL for the 'more' link."),
    '#default_value' => !empty($list['more-link']) ? $list['more-link'] : '',
    '#attributes' => [
      'class' => [
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ],
    ],
  ];

  // Provide page.
  $form['page'] = [
    '#type' => 'fieldset',
    '#title' => t('Page'),
    '#tree' => FALSE,
  ];
  $form['page']['provide-page'] = [
    '#type' => 'checkbox',
    '#title' => t('Provide page'),
    '#default_value' => isset($list['provide-page']) ? $list['provide-page'] : TRUE,
  ];
  $form['page']['path'] = [
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#required' => empty($form_state['input']) ? !empty($form['page']['provide-page']) : !empty($form_state['input']['provide-page']),
    '#size' => 30,
    '#default_value' => (!empty($list['path']) && $list['path'] !== '<none>') ? $list['path'] : '',
    '#attributes' => [
      'class' => [
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ],
    ],
  ];
  $form['page']['page-view-mode'] = [
    '#type' => 'select',
    '#title' => t('View mode'),
    '#options' => $modes,
    '#default_value' => !empty($list['page-view-mode']) ? $list['page-view-mode'] : 'teaser',
    '#attributes' => [
      'class' => [
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ],
    ],
  ];
  $form['page']['page-items'] = [
    '#type' => 'textfield',
    '#title' => t('# Items'),
    '#required' => TRUE,
    '#default_value' => !empty($list['page-items']) ? $list['page-items'] : 10,
    '#size' => 5,
    '#attributes' => [
      'class' => [
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ],
    ],
  ];
  $form['page']['intro-text'] = [
    '#type' => 'text_format',
    '#title' => t('Intro text'),
    '#format' => 'filtered_html',
    '#default_value' => !empty($list['intro-text']) ? $list['intro-text'] : '',
    '#attributes' => [
      'class' => [
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ],
    ],
  ];

  $form['metainfo'] = [
    '#type' => 'fieldset',
    '#title' => t('Metadata info'),
    '#tree' => FALSE,
  ];

  $form['metainfo']['meta_description'] = [
    '#type' => 'textarea',
    '#title' => t('Metadata description'),
    '#default_value' => !empty($list['meta-description']) ? $list['meta-description'] : '',
  ];

  $form['actions'] = [
    '#type' => 'actions',
  ];
  $form['actions']['submit'] = [
    '#type' => 'submit',
    '#value' => t('Save'),
  ];
  $form['actions']['cancel'] = [
    '#type' => 'markup',
    '#markup' => l(t('Cancel'), 'admin/structure/lists'),
  ];

  return $form;
}

/**
 * Validate handler.
 */
function custom_lists_list_form_validate($form, &$form_state) {
  // Don't try to create or update a list using a router path that
  // already exists.
  // Updating a existing list with the same router path is allowed.
  $error = FALSE;
  if ($form_state['values']['provide-page']) {
    if (empty($form_state['values']['path'])) {
      form_set_error('path', t('The field %field is required.', ['%field' => 'pad']));
    }
    $sql = 'SELECT path FROM {menu_router} WHERE path=:path';
    $existing = db_query($sql, [':path' => $form_state['values']['path']])->fetchField();
    if ($existing) {
      if (isset($form_state['values']['key'])) {
        $list = custom_lists_get($form_state['values']['key']);
        if (strtolower($list['path']) != strtolower($existing)) {
          $error = TRUE;
        }
      }
      else {
        $error = TRUE;
      }
    }
  }
  if ($error) {
    form_set_error('path', t('Path already exists.'));
  }
}

/**
 * Submit handler.
 */
function custom_lists_list_form_submit($form, &$form_state) {

  // Empty some useless data.
  if ($form_state['values']['type'] == 'content') {
    $form_state['values']['menu-item'] = NULL;
  }
  else {
    if ($form_state['values']['type'] == 'menu') {
      $form_state['values']['node-type'] = NULL;
    }
  }

  // Setup list data.
  $list = [
    'path' => $form_state['values']['path'],
    'title' => $form_state['values']['title'],
    'display_title' => $form_state['values']['display_title'],
    'page-items' => $form_state['values']['page-items'],
    'block-items' => $form_state['values']['block-items'],
    'type' => $form_state['values']['type'],
    'provide-block' => $form_state['values']['provide-block'],
    'show-more-link' => $form_state['values']['show-more-link'],
    'more-link' => $form_state['values']['more-link'],
    'provide-page' => $form_state['values']['provide-page'],
    'node-type' => $form_state['values']['node-type'],
    'extra-filters' => $form_state['values']['extra-filters'],
    'node-queues' => $form_state['values']['node-queues'],
    'taxonomy' => $form_state['values']['taxonomy'],
    'sort' => $form_state['values']['sort'],
    'block-view-mode' => $form_state['values']['block-view-mode'],
    'page-view-mode' => $form_state['values']['page-view-mode'],
    'menu-item' => $form_state['values']['menu-item'],
    'intro-text' => $form_state['values']['intro-text']['value'],
    'meta-description' => $form_state['values']['meta_description'],
  ];

  $list_key = md5(serialize($list));
  if (isset($form_state['values']['key'])) {
    $old_key = $form_state['values']['key'];

    drupal_set_message(t('The list has been updated.'));
    custom_lists_add($old_key, $list);
    $form_state['redirect'] = 'admin/structure/lists';

  }
  else {
    drupal_set_message(t('The list has been added.'));
    custom_lists_add($list_key, $list);
    $form_state['redirect'] = 'admin/structure/lists';
  }
}

/**
 * Page callback: Outputs JSON for taxonomy autocomplete suggestions.
 *
 * This is copied from taxonomy_autocomplete but rewritten so it doesn't
 * need a field to exists.
 */
function custom_lists_taxonomy_autocomplete($term_search = '', $node_type = '') {
  $query = db_select('taxonomy_term_data', 't');
  $query->addTag('translatable');
  $query->addTag('term_access');

  // Select rows that match by term name.
  $tags_return = $query
    ->fields('t', ['tid', 'name'])
    ->condition('t.name', '%' . db_like($term_search) . '%', 'LIKE')
    ->range(0, 10)
    ->execute()
    ->fetchAllKeyed();

  $term_matches = [];
  foreach ($tags_return as $tid => $name) {
    $n = $name;
    // Term names containing commas or quotes must be wrapped in quotes.
    if (strpos($name, ',') !== FALSE || strpos($name, '"') !== FALSE) {
      $n = '"' . str_replace('"', '""', $name) . '"';
    }
    $term_matches[$n] = check_plain($name);
  }

  drupal_json_output($term_matches);
}

/**
 * Helper function to retrieve all menu item options.
 *
 * Which should atleast have one child.
 *
 * @return array
 *    Array of menu options.
 */
function _custom_lists_menu_options() {
  $options = [];

  $menus = menu_get_menus();
  foreach ($menus as $menu_name => $menu) {
    if (in_array($menu_name, variable_get('custom_lists_exclude_menus', [
      'management',
      'navigation',
      'user-menu',
    ]))) {
      continue;
    }

    $options[$menu] = [];

    $tree = menu_tree_all_data($menu_name, NULL);
    foreach ($tree as $link) {
      $options[$menu] += _custom_lists_menu_options_filter($link);
    }

    if (empty($options[$menu])) {
      unset($options[$menu]);
    }
  }

  return $options;
}

/**
 * Helper function for _custom_lists_menu_options().
 *
 * To be able to filter recursively.
 */
function _custom_lists_menu_options_filter($link, $prefix = '') {
  if (empty($link['below'])) {
    // If we do not have any childs we are not an option.
    return [];
  }

  $options = [];
  $options[$link['link']['mlid']] = $prefix . $link['link']['link_title'] . ' (' . count($link['below']) . ')';

  $sub_prefix = $prefix . $link['link']['link_title'] . '--';

  foreach ($link['below'] as $sublink) {
    $options += _custom_lists_menu_options_filter($sublink, $sub_prefix);
  }

  return $options;
}

/**
 * Fetch all terms on the site.
 */
function _custom_lists_get_terms() {
  $terms = [];
  $vocabularies = taxonomy_get_vocabularies();
  foreach ($vocabularies as $voc) {
    $tree = taxonomy_get_tree($voc->vid);
    foreach ($tree as $term) {
      $terms[$voc->name][$term->tid] = $term->name;
    }
  }

  return $terms;
}

/**
 * Helper function to filter out view modes from the list.
 *
 * @param array $view_modes
 *   View modes, as returned from entity_get_info().
 *
 * @return array
 *   Filtered list of view modes.
 */
function _custom_lists_filter_view_modes($view_modes) {

  // Define view modes to remove from the list rather then the ones to keep.
  $filter_list = [
    'rss',
    'search_index',
    'search_result',
    'diff_standard',
    'felix',
    'token',
    'short',
  ];

  foreach ($view_modes as $key => $view_mode) {
    if (in_array($key, $filter_list)) {
      unset($view_modes[$key]);
    }
  }

  return $view_modes;
}
