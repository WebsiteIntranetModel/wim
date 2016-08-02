<?php
/**
 * Callback for 'admin/structure/lists'.
 */
function custom_lists_admin() {
  // Setup some default data.
  $types = node_type_get_names();
  $lists = custom_lists_get();

  // Setup the rows to show in the table.
  $rows = array();
  foreach ($lists as $list_key => $list) {
      $row = array();
      $row[] = $list['title'];
      $row[] = $list['provide-page'] ? l($list['path'], $list['path']) : t('No');
      $row[] = $list['provide-block'] ? t('Yes') : t('No');
      $row[] = ucfirst($list['type']);

      $data = array();
      if ($list['type'] == 'content') {
        if ($list['node-type'] != '_any') {
          $data[] = t('Type: !type', array('!type' => $types[$list['node-type']]));
        }
        if (!empty($list['taxonomy'])) {
          $term = taxonomy_term_load($list['taxonomy']);
          $data[] = t('Taxonomy: !term', array('!term' => l($term->name, 'taxonomy/term/' . $term->tid)));
        }
      }
      else if ($list['type'] == 'menu') {
        $menu_item = menu_link_load($list['menu-item']);
        $data[] = t('Menu parent: !parent', array('!parent' => l($menu_item['link_title'], $menu_item['link_path'])));
      }
      $row[] = implode(',', $data);

      $row[] = l(t('Edit'), 'admin/structure/lists/edit/' . $list_key) . ' | ' . l(t('Delete'), 'admin/structure/lists/delete/' . $list_key);

      $rows[] = $row;
  }

  return theme('table', array('header' => array(t('TItle'), t('Page'), t('Block'), t('Type'), t('Data'), t('Operations')), 'rows' => $rows));
}

/**
 * Callback for 'admin/structure/lists/delete/%id
 */
function custom_lists_delete_form($form, &$form_state, $list_key) {
  $lists = custom_lists_get();
  $form['#listkey'] = $list_key;

  return confirm_form($form, t('Are you sure you want to delete the list !list?', array('!list' => $lists[$list_key]['path'])), 'admin/structure/lists');
}

function custom_lists_delete_form_submit($form, &$form_state) {
  custom_lists_delete($form['#listkey']);
  drupal_set_message(t('The list has been removed.'));
  $form_state['redirect'] = 'admin/structure/lists';
}

/**
 * Form for the add list.
 *
 * @param $form
 * @param $form_state
 * @return mixed
 */
function custom_lists_list_form($form, &$form_state, $list_key = NULL) {
  $list = array();
  if ($list_key) {
    $lists = custom_lists_get();
    $list = $lists[$list_key];
  }

  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General'),
    '#tree' => FALSE,
    '#attached' => array(
      'css' => array(
        drupal_get_path('module', 'custom_lists') . '/custom_lists.css',
      ),
      'js' => array(
        drupal_get_path('module', 'custom_lists') . '/custom_lists.js',
      ),
    ),
  );

  $form['general']['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Administration title'),
    '#size' => 30,
    '#required' => TRUE,
    '#description' => t('This title is only used on admin pages to identify the custom list.'),
    '#default_value' => !empty($list['title']) ? $list['title']: '',
  );

  $form['general']['display_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#size' => 30,
    '#required' => TRUE,
    '#description' => t('This title is used as block and page title.'),
    '#default_value' => !empty($list['display_title']) ? $list['display_title']: '',
  );

  if (!empty($list_key)){
  $form['general']['key'] = array(
    '#type' => 'hidden',
    '#title' => t('Key'),
    '#required' => TRUE,
    '#default_value' => $list_key,
  );
  }
  $form['general']['type'] = array(
    '#type' => 'select',
    '#title' => t('Type'),
    '#options' => array(
      'content' => t('Content'),
      'menu' => t('Menu'),
    ),
    '#default_value' => !empty($list['type']) ? $list['type']: 'content',
  );
  $form['general']['css_class'] = array(
    '#type' => 'textfield',
    '#title' => t('CSS class'),
    '#size' => 30,
    '#required' => FALSE,
    '#description' => t('The CSS class to use for both the block and page display.'),
    '#default_value' => !empty($list['css_class']) ? $list['css_class']: '',
  );

  $form['type-settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings'),
    '#tree' => FALSE,
  );

  // Node type data.
  $types = node_type_get_names();
  $form['type-settings']['node-type'] = array(
    '#type' => 'select',
    '#title' => t('Nodetype'),
    '#options' => array('_any' => t('Any')) + node_type_get_names(),
    '#default_value' => !empty($list['node-type']) ? $list['node-type']: '_any',
    '#attributes' => array(
      'class' => array(
        'type-setting',
        'type-setting-content',
      ),
    ),
  );

  $queues = nodequeue_get_all_qids();
  $form['type-settings']['node-queues'] = array(
    '#type' => 'select',
    '#title' => t('Nodequeue'),
    '#options' => array('_any' => t('Any')) + $queues,
    '#default_value' => !empty($list['node-queues']) ? $list['node-queues']: '_any',
    '#attributes' => array(
      'class' => array(
        'type-setting',
        'type-setting-content',
      ),
    ),
  );

  $def_taxonomy = '';
  if (!empty($list['taxonomy'])) {
    $term = taxonomy_term_load($list['taxonomy']);
    $def_taxonomy = $term->name;
  }
  $form['type-settings']['taxonomy'] = array(
    '#type' => 'textfield',
    '#title' => t('Term'),
    '#autocomplete_path' => 'custom_lists/taxonomy/autocomplete',
    '#maxlength' => 255,
    '#default_value' => $def_taxonomy,
    '#attributes' => array(
      'class' => array(
        'type-setting',
        'type-setting-content',
      ),
    ),
  );
  $form['type-settings']['extra-filters'] = array(
    '#type' => 'select',
    '#title' => t('Filters'),
    '#default_value' => !empty($list['extra-filters']) ? $list['extra-filters']: '_none',
    '#options' => array(
      '_none' => t('No filter'),
      'node_type_agenda_upcoming' => t('Agenda: Upcoming'),
    ),
  );

  $form['type-settings']['sort'] = array(
    '#type' => 'select',
    '#title' => t('Sort'),
    '#options' => array(
      'created_desc' => t('Post date: newest first'),
      'created_asc' => t('Post date: oldest first'),
      'changed_desc' => t('Changed date: newest first'),
      'changed_asc' => t('Changed date: oldest first'),
      'title_asc' => t('Title: ascending'),
      'title_desc' => t('Title: descending'),
      'queue_asc' => t('Nodequeue: ascending'),
      'queue_desc' => t('Nodequeue: descending'),
      'weight_asc' => t('Weight: ascending'),
      'weight_desc' => t('Weight: descending'),
      'agenda_asc' => t('Agenda date: ascending'),
      'agenda_desc' => t('Agenda date: descending'),
    ),
    '#default_value' => !empty($list['sort']) ? $list['sort']: '',
    '#attributes' => array(
      'class' => array(
        'type-setting',
        'type-setting-content',
      ),
    ),
  );

  // Setup view modes.
  $modes = array('titles' => t('Titles as link'));
  $entity_info = entity_get_info('node');
  foreach ($entity_info['view modes'] as $view_mode => $data) {
    $modes[$view_mode] = $data['label'];
  }

  // Menu type data.
  // Generate a list of possible parents (not including this link or descendants).
  $options = _custom_lists_menu_options();
  $form['type-settings']['menu-item'] = array(
    '#type' => 'select',
    '#title' => t('Menu Parent'),
    '#options' => $options,
    '#attributes' => array('class' => array('menu-title-select')),
    '#default_value' => !empty($list['menu-item']) ? $list['menu-item']: '',
    '#attributes' => array(
      'class' => array(
        'type-setting',
        'type-setting-menu',
      ),
    ),
  );

  /**
   * Provide Block
   */
  $form['block'] = array(
    '#type' => 'fieldset',
    '#title' => t('Block'),
    '#tree' => FALSE,
  );
  $form['block']['provide-block'] = array(
    '#type' => 'checkbox',
    '#title' => t('Provide block'),
    '#default_value' => isset($list['provide-block']) ? $list['provide-block']: FALSE,
  );
  $form['block']['block-view-mode'] = array(
    '#type' => 'select',
    '#title' => t('View mode'),
    '#options' => $modes,
    '#default_value' => !empty($list['block-view-mode']) ? $list['block-view-mode']: 'titles',
    '#attributes' => array(
      'class' => array(
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ),
    ),
  );
  $form['block']['block-items'] = array(
    '#type' => 'textfield',
    '#title' => t('# Items'),
    '#required' => TRUE,
    '#default_value' => !empty($list['block-items']) ? $list['block-items']: 5,
    '#size' => 5,
    '#attributes' => array(
      'class' => array(
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ),
    ),
  );
  $form['block']['show-more-link'] = array(
    '#type' => 'select',
    '#title' => t('Show more link'),
    '#options' => array(
      'hide' => t('Hide'),
      'default' => t('Default (Links to page)'),
      'custom' => t('Custom (Provide custom uri)'),
    ),
    '#default_value' => !empty($list['show-more-link']) ? $list['show-more-link']: 'default',
    '#attributes' => array(
      'class' => array(
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ),
    ),
  );
  $form['block']['more-link'] = array(
    '#type' => 'textfield',
    '#title' => t('Custom more link'),
    '#description' => t('Fill in the Drupal URL for the \'more\' link.'),
    '#default_value' => !empty($list['more-link']) ? $list['more-link'] : '',
    '#attributes' => array(
      'class' => array(
        'block-setting',
        'block-setting-content',
        'block-setting-menu',
      ),
    ),
  );

  /**
   * Provide page
   */
  $form['page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Page'),
    '#tree' => FALSE,
  );
  $form['page']['provide-page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Provide page'),
    '#default_value' => isset($list['provide-page']) ? $list['provide-page']: TRUE,
  );
  $form['page']['path'] = array(
    '#type' => 'textfield',
    '#title' => t('Path'),
    '#required' => empty($form_state['input']) ? !empty($form['page']['provide-page']) : !empty($form_state['input']['provide-page']),
    '#size' => 30,
    '#default_value' => (!empty($list['path']) && $list['path'] !== '<none>') ? $list['path']: '',
    '#attributes' => array(
      'class' => array(
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ),
    ),
  );
  $form['page']['page-view-mode'] = array(
    '#type' => 'select',
    '#title' => t('View mode'),
    '#options' => $modes,
    '#default_value' => !empty($list['page-view-mode']) ? $list['page-view-mode']: 'teaser',
    '#attributes' => array(
      'class' => array(
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ),
    ),
  );
  $form['page']['page-items'] = array(
    '#type' => 'textfield',
    '#title' => t('# Items'),
    '#required' => TRUE,
    '#default_value' => !empty($list['page-items']) ? $list['page-items']: 10,
    '#size' => 5,
    '#attributes' => array(
      'class' => array(
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ),
    ),
  );
  $form['page']['intro-text'] = array(
    '#type' => 'text_format',
    '#title' => t('Intro text'),
    '#format' => 'filtered_html',
    '#default_value' => !empty($list['intro-text']) ? $list['intro-text']: '',
    '#attributes' => array(
      'class' => array(
        'page-setting',
        'page-setting-content',
        'page-setting-menu',
      ),
    ),
  );

  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['actions']['cancel'] = array(
    '#type' => 'markup',
    '#markup' => l(t('Cancel'), 'admin/structure/lists'),
  );

  return $form;
}

/**
 * Validate handler.
 */
function custom_lists_list_form_validate($form, &$form_state) {
  // Don't try to create or update a list using a router path that already exists.
  // Updating a existing list with the same router path is allowed.
  $error = FALSE;
  if ($form_state['values']['provide-page']) {
    if (empty($form_state['values']['path'])) {
      form_set_error('path', t('The field %field is required.', array('%field' => 'pad')));
    }
    $sql = 'SELECT path FROM {menu_router} WHERE path=:path';
    $existing = db_query($sql, array(':path' => $form_state['values']['path']))->fetchField();
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

  // Get taxonomy term id.
  if (!empty($form_state['values']['taxonomy'])) {
    $terms = taxonomy_get_term_by_name($form_state['values']['taxonomy']);
    $form_state['values']['taxonomy'] = key($terms);
  }

  // Empty some useless data.
  if ($form_state['values']['type'] == 'content') {
    $form_state['values']['menu-item'] = NULL;
  }
  else if ($form_state['values']['type'] == 'menu') {
    $form_state['values']['node-type'] = NULL;
  }

  // Setup list data.
  $list = array(
    'path' => $form_state['values']['path'],
    'title' => $form_state['values']['title'],
    'display_title' => $form_state['values']['display_title'],
    'css_class' => $form_state['values']['css_class'],
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
  );

  $list_key = md5(serialize($list));
  if (isset($form_state['values']['key'])) {
    $old_key = $form_state['values']['key'];

    drupal_set_message(t('The list has been updated.'));
    custom_lists_add($old_key, $list);
    $form_state['redirect'] = 'admin/structure/lists';

  } else {
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
    ->fields('t', array('tid', 'name'))
    //  ->condition('t.vid', $vids)
    ->condition('t.name', '%' . db_like($term_search) . '%', 'LIKE')
    ->range(0, 10)
    ->execute()
    ->fetchAllKeyed();

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
 * Helper function to retrieve all menu item options which should atleast
 * have one child.
 *
 * @return array
 */
function _custom_lists_menu_options() {
  $options = array();

  $menus = menu_get_menus();
  foreach ($menus as $menu_name => $menu) {
    if (in_array($menu_name, variable_get('custom_lists_exclude_menus', array('management', 'navigation', 'user-menu')))) {
      continue;
    }

    $options[$menu] = array();

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
 * Helper function for _custom_lists_menu_options() to be able to filter
 * recursively.
 *
 * @param $link
 * @param string $prefix
 * @return array
 */
function _custom_lists_menu_options_filter($link, $prefix = '') {
  if (empty($link['below'])) {
    // If we do not have any childs we are not an option.
    return array();
  }

  $options = array();
  $options[$link['link']['mlid']] = $prefix . $link['link']['link_title'] . ' (' . count($link['below']) . ')';

  $sub_prefix = $prefix . $link['link']['link_title'] . '--';

  foreach ($link['below'] as $sublink) {
    $options += _custom_lists_menu_options_filter($sublink, $sub_prefix);
  }

  return $options;
}
