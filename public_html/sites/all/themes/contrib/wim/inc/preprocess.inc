<?php

/**
 * Implements hook_preprocess_html().
 * - Use Drupal 8 way of processing attributes for <html> and <body>.
 */
function dimpact_preprocess_html(&$vars) {
  global $_domain;

  // Create a variable for the path to the theme.
  $vars['path'] = drupal_get_path('theme', 'dimpact');

  // Initializes attributes which are specific to the html and body elements.
  $vars['html_attributes_array'] = array();
  $vars['body_attributes_array'] = array();

  // HTML element attributes.
  $vars['html_attributes_array']['lang'] = $GLOBALS['language']->language;
  $vars['html_attributes_array']['dir'] = $GLOBALS['language']->direction ? 'rtl' : 'ltr';

  if (module_exists('rdf')) {
    // Adds RDF namespace prefix bindings in the form of an RDFa 1.1 prefix
    // attribute inside the html element.
    $prefixes = array();
    foreach (rdf_get_namespaces() as $prefix => $uri) {
      $vars['html_attributes_array']['prefix'][] = $prefix . ': ' . $uri . "\n";
    }
  }

  // Add body classes indicating tabs.
  if (menu_primary_local_tasks() && menu_secondary_local_tasks()) {
    $vars['classes_array'][] = 'with-tabs';
  }
  elseif (menu_primary_local_tasks()) {
    $vars['classes_array'][] = 'with-tabs tabs-primary';
  }
  elseif (menu_secondary_local_tasks()) {
    $vars['classes_array'][] = 'with-tabs tabs-secondary';
  }
  else {
    $vars['classes_array'][] = 'no-tabs';
  }

  if (module_exists('views')) {
    if ($vars['view'] = views_get_page_view()) {
      $display = $vars['view']->current_display;
      $vars['classes_array'][] = 'page-view-' . drupal_html_class($vars['view']->name) . '-' . $display;
    }
  }

  // The default body classes are way too verbose for what we need here.
  // This should really be optional, but since it's not, need to rebuild in
  // in order to remove them.
  $suggestion_classes = array();
  if ($suggestions = theme_get_suggestions(arg(), 'page', '-')) {
    foreach ($suggestions as $suggestion) {
      if ($suggestion != 'page-front') {
        $suggestion_classes[] = drupal_html_class($suggestion);
      }
    }
  }
  $vars['classes_array'] = array_diff($vars['classes_array'], $suggestion_classes);
  $vars['classes_array'][] = theme_get_setting('color_swatch_internet');

  global $_domain;

  if (domain_conf_variable_get($_domain['domain_id'], 'font_killswitch') == 0) {
    drupal_add_css('https://fonts.googleapis.com/css?family=Droid+Sans:400,700%7CRoboto+Slab:400,700');
  }
  drupal_add_js(drupal_get_path('theme', 'dimpact') . '/js/dimpact.js');
  drupal_add_js(drupal_get_path('theme', 'dimpact') . '/js/libraries/jquery.carouFredSel-6.2.1-packed.js');
}

/**
 * Implements template_preprocess_page().
 */
function dimpact_preprocess_page(&$vars) {
  // Add a template suggestion for views pages, and allow the header of the
  // view to be printed in page.tpl.php
  if (module_exists('views')) {
    if ($vars['view'] = views_get_page_view()) {
      array_unshift($vars['theme_hook_suggestions'], 'page__view');
      // Make the view header available. This will print in page.tpl.php.
      $display = $vars['view']->current_display;
      if (!empty($vars['view']->display[$display]->display_options['header']['area']['content'])) {
        $vars['view_header'] = filter_xss_admin($vars['view']->display[$display]->display_options['header']['area']['content']);
      }
    }
  }

  $vars['hidecontent'] = FALSE;
  $vars['pagetype'] = NULL;
  if (arg(0) == 'search') {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'searchpage';
  }
  else if (arg(0) == 'node' && arg(1) == 'add') {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'node-add-page';
  }
  else if (arg(0) == 'bekendmakingen') {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'bekendmakingen';
  }
  else if (arg(0) == 'bestemmingsplannen') {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'bestemmingsplannen';
  }
  else if (arg(0) == 'foto-album' && arg(1) == 'tag' && is_numeric(arg(2))) {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'fotoalbum';
    if (isset($vars['page']['region_363_first']['submenutree_2'])) {
      $vars['page']['region_39_first']['submenutree_2'] = $vars['page']['region_363_first']['submenutree_2'];
      unset($vars['page']['region_363_first']['submenutree_2']);
    }
  }
  if (arg(0) == 'forum') {
    $vars['hidecontent'] = TRUE;
    $vars['pagetype'] = 'forum';
    if (isset($vars['page']['region_363_first']['submenutree_2'])) {
      $vars['page']['region_39_first']['submenutree_2'] = $vars['page']['region_363_first']['submenutree_2'];
      unset($vars['page']['region_363_first']['submenutree_2']);
    }
  }

  if (arg(0) == 'fotoalbums') {
    if (isset($vars['page']['region_363_first']['submenutree_2'])) {
      $vars['page']['region_39_first']['submenutree_2'] = $vars['page']['region_363_first']['submenutree_2'];
      unset($vars['page']['region_363_first']['submenutree_2']);
    }
  }

  if ($status = drupal_get_http_header("status")) {
    switch ($status) {
      case '403 Forbidden':
        $vars['theme_hook_suggestions'][] = 'page__403';
        break;
      case '404 Not Found':
        $vars['theme_hook_suggestions'][] = 'page__404';
        break;
    }
  }

  if (isset($vars['node']) && $vars['node']->type == 'subject') {
    if (isset($vars['page']['region_363_first']['submenutree_2'])) {
      unset($vars['page']['region_363_first']['submenutree_2']);
    }
  }

  if (arg(0) == 'user' && is_numeric(arg(1))) {
    $user = user_load(arg(1));
    if ($full_name = field_get_items('user', $user, 'field_volledige_naam')) {
      $name = reset($full_name);
      drupal_set_title($name['value']);
    }
  }

}

/**
 * Implements template_preprocess_block().
 */
function dimpact_preprocess_block(&$vars) {
  // Add the block ID as a class.
  $vars['classes_array'][] = $vars['block_html_id'];

  if (module_exists('block_class')) {
    $block = block_load($vars['block']->module, $vars['block']->delta);
    if (isset($block->css_class)) {
      $vars['classes_array'][] = $block->css_class;
    }
  }

  // Hide the block titles in the header and navigation regions by default.
  // if ($vars['block']->region == 'header' || $vars['block']->region == 'navigation') {
  //   $vars['title_attributes_array']['class'][] = 'visuallyhidden';
  // }

  // Add default "content" class to the block template. Removing this in a sub-theme
  // for example, will prevent a div from printing, unless there are RDF attributes.
  // @see block.tpl.php provided by this theme.
  // $vars['content_attributes_array']['class'][] = 'content';

  // Add ARIA roles to core blocks.
  $roles = array(
    'complementary' => array(
      'aggregator',
      'help',
      'locale',
      'poll',
      'profile',
      'node' => array('syndicate'),
      'system' => array('powered-by', 'help'),
      'user' => array('new', 'online'),
    ),
    'navigation' => array(
      'blog',
      'book',
      'comment',
      'forum',
      'menu',
      'menu_block',
      'node' => array('recent'),
      'shortcut',
      'statistics',
      'system' => array_keys(menu_list_system_menus()),
    ),
    'search' => array(
      'search',
    ),
    'form' => array(
      'user' => array('login'),
    ),
  );

  // Loop through the roles defined above and apply them to the necessary blocks.
  // @todo Figure out why this isn't working properly.
  foreach ($roles as $role => $module) {
    if (!is_array($role) && in_array($vars['block']->module, $module)) {
      $vars['attributes_array']['role'] = "$role";
    }
    elseif (is_array($role)) {
      foreach ($role as $module => $delta) {
        if ($vars['block']->module == $module && in_array($vars['block']->delta, $delta)) {
          $vars['attributes_array']['role'] = "$role";
        }
      }
    }

  // Provide some template suggestions based on ARIA roles.
  switch (isset($vars['attributes_array']['role'])) {
    case 'navigation':
       array_unshift($vars['theme_hook_suggestions'], 'block__nav');
      break;
    case 'form':
    case 'search':
      array_unshift($vars['theme_hook_suggestions'], 'block__plain');
      break;
    }
  }

  if ($vars['block']->module == 'views' && $vars['is_admin']) {
    $remove = array();
    $vars['classes_array'][] = 'admin-only-wrapper';
    $vars['classes_array'] = array_diff($vars['classes_array'], $remove);
  }
  $vars['title_attributes_array']['class'][] = 'block-title';

}

/**
 * Implements template_preprocess_node().
 */
function dimpact_preprocess_node(&$vars) {
  $node = $vars['node'];

  if ($vars['view_mode']) {
    // Add a class indicating the current view mode.
    $vars['classes_array'][] = 'view-mode-' . drupal_html_class($vars['view_mode']);
    // Allow different templates per view mode.
    $vars['theme_hook_suggestions'][] = 'node__' . $vars['view_mode'];
  }

  // Add article ARIA role.
  $vars['attributes_array']['role'] = 'article';

  // Remove the default classes. This is all IE6 stuff.
  $classes_to_remove = array(drupal_html_class('node-' . $node->type), 'node-promoted', 'node-sticky', 'node-unpublished', 'node-teaser', 'node-preview');
  $vars['classes_array'] = array_diff($vars['classes_array'], $classes_to_remove);

  // Recreate some of them without the 'node-' prefix.
  // Gather node classes.
  $vars['classes_array'][] = drupal_html_class($node->type);
  if (isset($vars['preview'])) {
    $vars['classes_array'][] = 'preview';
  }
  if ($vars['sticky']) {
    $vars['classes_array'][] = 'sticky';
  }
  if ($vars['teaser']) {
    $vars['classes_array'][] = 'teaser';
  }
  if (!$vars['status']) {
    $vars['classes_array'][] = 'unpublished';
  }

  if (isset($node->field_image) && !empty($node->field_image)) {
    $vars['classes_array'][] = 'has-image';
  }

  // Create a timestamp suitable for the datetime attribute.
  $vars['timestamp'] = date_iso8601($node->created);

  $vars['tabs'] = '';
  if (isset($vars['field_tabtitel']) && isset($vars['field_tabcontent']) && module_exists('quicktabs')) {
    $tabs = array();
    foreach ($vars['field_tabtitel'] as $i => $tabtitle) {
      $tabs[$i] = array(
        'title' => $tabtitle['value'],
        'contents' => array(
          '#markup' => '<h2>' . $tabtitle['value'] . '</h2>' . $vars['field_tabcontent'][$i]['value'],
        ),
        'weight' => $i,
      );
    }
    $vars['tabs'] = quicktabs_build_quicktabs($node->nid, $settings = array(), $tabs);
  }

  if ($node->type == 'spatial_plan' && $vars['view_mode'] == 'teaser') {
    if (!empty($node->field_spatial_plan_id[LANGUAGE_NONE])) {
      $plannen_url = variable_get('spatial_plan_uri', 'http://www.ruimtelijkeplannen.nl/web-roo/roo/bestemmingsplannen?planidn=');
      $plan_id = $node->field_spatial_plan_id[LANGUAGE_NONE][0]['value'];
      $vars['node_url'] = $plannen_url . $plan_id;
    }
  }

  if ($node->type == 'tile' && $vars['view_mode'] == 'teaser') {
    // Override node_url var so that title will link to same url as given
    // by user on field_link.
    if (isset($node->field_link)) {
      $vars['node_url'] = $node->field_link['und'][0]['url'];
    }
  }

  // Show date and author on certain node types and only when the type is shown on a intranet subsite
  $types_to_show_submitted = array(
    'message',
    'blog',
    'marketplace',
    'file',
    'news',
  );

  // Check type and if submitted is set
  if (in_array($vars['type'], $types_to_show_submitted) && $vars['submitted']) {

    // Check if current domain has a 'intranet' or 'team' blueprint.
    $subsite = dominion_get_info();
    if ($subsite->blueprint == 'intranet' || $subsite->blueprint == 'team') {
      $vars['submitted'] = t('!datetime | door: !username', array(
          '!datetime' => format_date($vars['node']->created, 'custom', 'd F Y'),
          '!username' => $vars['name'],
        )
      );
    }
    else if ($subsite->blueprint == 'internet' || $subsite->blueprint == 'default' && $vars['type'] == 'news') {
      $vars['submitted'] = t('!datetime', array(
          '!datetime' => format_date($vars['node']->created, 'custom', 'd F Y'),
        )
      );
    }
    else
    {
      $vars['submitted'] = '';
    }
  }
}

/**
 * Implements template_preprocess_field().
 */
function dimpact_preprocess_field(&$vars) {
  // Default field wrapper.
  $vars['tag'] = 'div';
	// $heading is used in field.tpl.php and
	// field--fences-div_view_mode_dependant_heading.tpl.php
  $vars['heading'] = ($vars['element']['#view_mode'] == 'full') ? 'h2' : 'h3';

  // Add a less verbose field name class: .field-NAME
  $vars['classes_array'][] = drupal_html_class($vars['element']['#field_name']);

  // Use .field-body instead of .body
  if ($vars['element']['#field_name'] == 'body') {
    $vars['classes_array'][] = 'field-body';
  }

  // Remove some classes from the wrapper <div>.
  $classes_to_remove = array(
    'field-label-' . drupal_html_class($vars['element']['#label_display']),
    'field-type-' . drupal_html_class($vars['element']['#field_type']),
    'field-name-' . drupal_html_class($vars['element']['#field_name']),
    'body',
    'clearfix',
  );
  $vars['classes_array'] = array_diff($vars['classes_array'], $classes_to_remove);

  if ($vars['element']['#field_name'] == 'field_ris_agendaitems') {
    if ($vars['element']['#items']) {
      foreach ($vars['element']['#items'] as $delta => $target) {
        if ($node = node_load($target['target_id'])) {
          $vars['files'][$delta] = field_view_field('node', $node, 'field_ris_attachments');
        }
      }
    }
  }
}

/**
 * Implements template_preprocess_views_view().
 */
function dimpact_preprocess_views_view(&$vars) {
  $vars['tag'] = 'section';
  $vars['header_tag'] = 'header';
  $vars['footer_tag'] = 'footer';

  if (!empty($vars['view_empty'])) {
    // Add a class to the view. We're not wrapping this in yet another div.
    $vars['classes_array'][] = 'view-empty';
  }
  elseif (empty($vars['empty'])) {
    // Give it an empty string so it can just be printed. Simpler template.
    $vars['empty'] = '';
  }

  // Remove some classes!
  $remove[] = 'view-id-' . $vars['name'];
  $remove[] = 'view-display-id-' . $vars['display_id'];
  if (!empty($vars['dom_id'])) {
    $remove[] = 'view-dom-id-' . $vars['dom_id'];
  }

  // Add the display class back, but with the human name.
  $vars['classes_array'][] = 'view-' . $vars['name'] . '-display-' . $vars['display_id'];

  // $did = $vars['display_id'];
  // if (!empty($vars['view']->display[$did]->display_title)) {
  //   $vars['display_title'] = drupal_html_class($vars['view']->display[$did]->display_title);
  //   $vars['classes_array'][] = 'view-' . $vars['name'] . '-display-' . $vars['display_title'];
  // }

  $vars['classes_array'] = array_diff($vars['classes_array'], $remove);

}

/**
 * Implements template_preprocess_views_view_list().
 */
function dimpact_preprocess_views_view_list(&$vars) {

  // Provide simple helper classes for views.
  foreach ($vars['classes'] as $key => $value) {
    // Give each row and .item class.
    $vars['classes'][$key][] = 'item';

    // Provide even/odd classes since IE8 doesn't support nth-child.
    if (in_array('views-row-even', $value)) {
      $vars['classes'][$key][] = 'even';
    }
    if (in_array('views-row-odd', $value)) {
      $vars['classes'][$key][] = 'odd';
    }

    // Keep a simplified .last class because IE8 doesn't support :last-child.
    if (in_array('views-row-last', $value)) {
      $vars['classes'][$key][] = 'last';
    }

    // Get ready to remove a crap load of views classes.
    $remove = array();

    // Recreate a list of possible views-row-x results (up to 50 here) so
    // they can be removed below.
    for ($i=0; $i < 51; $i++) {
     $remove[] = 'views-row-' . $i;
    }

    // Add first/last/odd/even classes to this of those to remove.
    $remove[] = 'views-row';
    $remove[] = 'views-row-first';
    $remove[] = 'views-row-last';
    $remove[] = 'views-row-odd';
    $remove[] = 'views-row-even';

    // Get rid of them once and for all!
    $vars['classes_array'][$key] = implode(' ', array_diff($vars['classes'][$key], $remove));
  }
}

function dimpact_preprocess_homebox(&$variables) {
  $classes = array_flip($variables['classes_array']);
  if (isset($classes['column-count-3'])) {
    unset($variables['classes_array'][$classes['column-count-3']]);
  }
}

/**
 * Implements template_preprocess_user_profile().
 * @param $variables
 */
function dimpact_preprocess_user_profile(&$variables) {
  unset($variables['user_profile']['user_picture']);
}

function dimpact_preprocess_search_results(&$variables) {
  $variables['search_results'] = '';
  foreach ($variables['results'] as $result) {
    if ($result['entity_type'] == 'node' && isset($result['node']->bundle) && $result['node']->bundle == 'person') {
      $person_node = node_load($result['node']->entity_id);
      $variables['search_results'] .= '<li class="search-result">' . drupal_render(node_view($person_node, 'search_result')) . '</li>';
    }
    else {
      $variables['search_results'] .= theme('search_result', array('result' => $result, 'module' => $variables['module']));
    }
  }
}

function dimpact_preprocess_search_result(&$variables) {
  if (isset($variables['info_split']['user'])) {
    unset($variables['info_split']['user']);
  }
  if (isset($variables['info_split']['date'])) {
    unset($variables['info_split']['date']);
  }
  $variables['info'] = implode(' - ', $info);
}
