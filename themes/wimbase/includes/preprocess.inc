<?php
/**
 * @file
 * The primary PHP file for the Drupal Wim theme.
 *
 * This file contain implementations of the template_preprocess_HOOK() only.
 */

/**
 * Implements template_preprocess_node().
 */
function wimbase_preprocess_node(&$variables) {
  $node = $variables['node'];
  $view_mode = $variables['view_mode'];
  $content_type = $variables['type'];

  // Hook suggestion node--view_mode.tpl.php.
  $variables['theme_hook_suggestions'][] = 'node__' . strtr($view_mode, '-', '_');
  // Hook suggestion node--content_type--view_mode.tpl.php.
  $variables['theme_hook_suggestions'][] = 'node__' . $node->type . '__' . strtr($view_mode, '-', '_');

  // Add read more link variable to template.
  $variables['read_more_link'] = l(t('Read more'), $variables['node_url']);

  // Preprocess FAQ node.
  if ($content_type === 'faq') {
    $parameters = drupal_get_query_parameters();
    $variables['product_link'] = NULL;
    if (isset($parameters['product']) && is_numeric($parameters['product'])) {
      $variables['product_link'] = l(t('Back to product'), '/node/' . $parameters['product'], array('attributes' => array('class' => array('back-link'))));
    }
  }

  $variables['classes_array'][] = drupal_html_class('node-view-mode-' . $view_mode);

}

/**
 * Pre-processes variables for the "region" theme hook.
 *
 * See template for list of available variables.
 *
 * Calculate felix blocks placement.
 *
 * @see region.tpl.php
 *
 * @ingroup theme_preprocess
 */
function wimbase_preprocess_region(&$variables) {
  $theme_region = $variables['region'];
  $process_regions = array();

  $felix_regions = _felix_get_regions();
  // Fetch regions which we will process.
  foreach ($felix_regions as $felix_region) {
    $process_regions[] = $felix_region->region;
  }

  if (in_array($theme_region, $process_regions)) {
    $output = '';
    $total_col = 0;
    $rows = array();
    $row_id = 0;
    foreach (element_children($variables['elements']) as $element_id) {
      if (isset($variables['elements'][$element_id]['#block'])) {
        $block = $variables['elements'][$element_id]['#block'];

        // Place element in a new  row.
        if ($block->new_row) {
          $row_id++;
          $rows[$row_id][] = $variables['elements'][$element_id]['#children'];
          $total_col = $block->bootstrap_layout;

          // Override a position of block in the list if is set a weight row.
          if (isset($block->row_weight)) {
            unset($rows[$row_id]);
            $rows[$block->row_weight][] = $variables['elements'][$element_id]['#children'];
          }
        }
        else {
          $total_col += $block->bootstrap_layout;
          if ($total_col > WIM_BLOCK_MANAGEMENT_BOOTSTRAP_FULL_WIDTH) {
            $total_col = $block->bootstrap_layout;
            $row_id++;
            $rows[$row_id][] = $variables['elements'][$element_id]['#children'];
            // Next element can be placed in the same row with current.
            $same_row = TRUE;
          }
          // Add elements together in the same row.
          else {
            $rows[$row_id][] = $variables['elements'][$element_id]['#children'];
          }
        }
      }

    }

    ksort($rows);

    foreach ($rows as $row) {
      $output .= '<div class="row">' . implode("", $row) . '</div>';
    }

    $variables['content'] = $output;
  }
}

/**
 * Pre-processes variables for the "block" theme hook.
 *
 * See template for list of available variables.
 *
 * @see block.tpl.php
 *
 * @ingroup theme_preprocess
 */
function wimbase_preprocess_block(&$variables) {
  $block = &$variables['block'];
  $has_image_class = 'has-image';
  // Be default we show all blocks in a new row.
  $block->new_row = TRUE;
  $block->bootstrap_layout = WIM_BLOCK_MANAGEMENT_BOOTSTRAP_FULL_WIDTH;
  $bean_view_mode = NULL;

  // Process Bean blocks.
  if ($block->module === 'bean' && $bean = bean_load_delta($block->delta)) {
    $variables['title_url'] = NULL;
    $variables['classes_array'][] = drupal_html_class($bean->type);
    $variables['theme_hook_suggestions'][] = 'block__bean_' . strtr($bean->type, '_', '-');
    $bean_view_mode = $bean->view_mode;

    if (isset($bean->field_link) && $bean->field_link) {
      $variables['title_url'] = $bean->field_link[LANGUAGE_NONE][0]['url'];
    }
    if ($bean_view_mode === 'default' && isset($bean->field_image) && $bean->field_image) {
      $variables['classes_array'][] = $has_image_class;
    }

    // Set empty aria-label
    // so log will not create notices about not being defined.
    $variables['aria_label'] = '';
    if (isset($bean->field_aria_label) && !empty($bean->field_aria_label[LANGUAGE_NONE][0]['value'])) {
      $variables['aria_label'] = $bean->field_aria_label[LANGUAGE_NONE][0]['value'];
    }
  }

  // If block in the Felix region add corresponding classes.
  if (isset($block->felix_region, $block->data['config'])) {
    $config = $block->data['config'];
    // Add bootstrap class to block output.
    if (isset($config['bootstrap_layout'])) {
      $variables['classes_array'][] = 'col-md-' . $config['bootstrap_layout'];
      $block->bootstrap_layout = $config['bootstrap_layout'];
    }
    // If new row config exist then use it otherwise move it in a new row.
    $block->new_row = isset($config['new_row']) ? $config['new_row'] : TRUE;
    $block->row_weight = isset($config['row_weight']) ? $config['row_weight'] : 0;

    if ($block->module === 'bean' && $bean) {
      if (isset($config['bean_view_mode']) && $config['bean_view_mode']) {
        $bean_view_mode = $config['bean_view_mode'];
        // Build entity bean view.
        if (entity_access('view', 'bean', $bean) && $bean) {
          $content = $bean->view($bean_view_mode);
          if (!is_array($content)) {
            $content = array(
              '#markup' => $content,
            );
          }
          $variables['content'] = drupal_render($content);
        }

        // Process Editorial.
        if ($bean->type === 'editorial') {
          // Editorial added via Felix we process according to settings.
          if ($config['bean_view_mode'] === 'default' && $bean->field_image) {
            $variables['classes_array'][] = $has_image_class;
          }
        }
      }
    }
  }
  else {
    $variables['classes_array'][] = 'col-md-' . WIM_BLOCK_MANAGEMENT_BOOTSTRAP_FULL_WIDTH;
  }

  // Add class for menus blocks.
  if ($block->module === 'menu') {
    $variables['classes_array'][] = drupal_html_class($block->delta);
  }

  // Build class for the Bean block view mode.
  if ($bean_view_mode) {
    $variables['classes_array'][] = 'bean-view-mode-' . drupal_html_class($bean_view_mode);
  }

  // Add theme suggestion for node blocks.
  if ($block->module === 'node' && isset($block->data['viewmode'])) {
    $variables['theme_hook_suggestions'][] = 'block__node_' . strtr($block->data['viewmode'], '_', '-');
    $variables['title_url'] = url($block->detail_path);
    $node = node_load($block->delta);
    if (isset($node->field_image) && !empty($node->field_image)) {
      $variables['classes_array'][] = $has_image_class;
    }
  }
}

/**
 * Implements hook_preprocess_field().
 */
function wimbase_preprocess_field(&$variables, $hook) {
  $element = $variables['element'];
  $field_name = $element['#field_name'];

  // Add product id parameter to FAQ links.
  if ($field_name === 'field_related_faq' && $element['#bundle'] === 'product' && $element['#view_mode'] === 'full') {
    $product_id = $element['#object']->nid;
    foreach ($element['#items'] as $id => $item) {
      $faq = $item['entity'];
      if ($uri = entity_uri('node', $item['entity'])) {
        $options = array('query' => array('product' => $product_id));
        $variables['items'][$id] = array(
          '#markup' => l($faq->title, $uri['path'], $options),
        );
      }
    }
  }

  // Override field image output for Editorial.
  if ($field_name === 'field_image' && $element['#entity_type'] === 'bean') {
    if ($element['#bundle'] === 'editorial' && $element['#view_mode'] === 'default') {
      $bean = $element['#object'];
      if ($bean->field_link) {
        foreach ($element['#items'] as $id => $item) {
          $variables['items'][$id]['#path']['path'] = $bean->field_link[LANGUAGE_NONE][0]['url'];
        }
      }
    }
  }
}

/**
 * Implements hook_preprocess_page().
 */
function wimbase_preprocess_page(&$variables) {
  $menu_item = menu_get_item();

  // All FAQ pages should has title FAQ.
  if (is_array($menu_item) && $menu_item['path'] === 'faq/%') {
    $variables['title'] = t('FAQ');
  }

  // Set title for search page.
  if (is_array($menu_item) && $menu_item['path'] === 'search/site/%') {
    drupal_set_title(t('Search'));
  }

  // Add readspeaker to page template.
  if (module_exists('readspeaker')) {
    $variables['readspeaker'] = readspeaker_build_player();
  }

  // Set bootstrap classes.
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    _wimbase_culc_content_cols($variables, 3, 3);
  }
  elseif (!empty($variables['page']['sidebar_first']) && empty($variables['page']['sidebar_second'])) {
    _wimbase_culc_content_cols($variables, 3, 0);
  }
  elseif (empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    _wimbase_culc_content_cols($variables, 0, 3);
  }
  else {
    _wimbase_culc_content_cols($variables, 3);
  }
}

/**
 * Template preprocess for apachesolr search results.
 */
function wimbase_preprocess_search_result(&$variables) {
  $result = $variables['result'];

  // Add source url.
  wimbase_result_source_site($result['link'], $variables);
  $keyword_highlight = variable_get('keyword_highlighting_search', 0);

  if ($result['entity_type'] === 'node') {
    if (isset($result['node']) && $node = node_load($result['node']->entity_id)) {
      $content_types_labels = array(
        'page' => t('General information'),
      );

      $variables['node_content'] = node_view($node, 'search_result');

      // Keyword highlighting for node.
      if ($keyword_highlight == 1) {
        if (isset($variables['node_content']['body'][0]['#markup'])) {
          $variables['node_content']['body'][0]['#markup'] = strip_tags($variables['node_content']['body'][0]['#markup']);
          if ($search_string = arg(2)) {
            $variables['node_content']['body'][0]['#markup'] = _wimbase_highlight_words($variables['node_content']['body'][0]['#markup'], $search_string);
          }
        }
        elseif ($variables['snippet']) {
          $variables['snippet'] = strip_tags($variables['snippet']);
          if ($search_string = arg(2)) {
            $variables['snippet'] = _wimbase_highlight_words($variables['snippet'], $search_string);
          }
        }
      }

      // Add content type label.
      $variables['content_type'] = isset($content_types_labels[$node->type]) ? $content_types_labels[$node->type] : ucfirst($node->type);

      if ($result['bundle'] === 'linked_keywords') {
        global $base_url;
        $referenced_content = $node->field_referenced_content[LANGUAGE_NONE][0];

        // Get the node where we are referring to.
        $referenced_node = explode($base_url . '/' , $referenced_content['url']);
        $referenced_node = explode('node/', drupal_get_normal_path($referenced_node[1]));
        $referenced_node = node_load($referenced_node[1]);

        // Override an output of linked_keywords data and replace with link of
        // linked content in the search result.
        $variables['url'] = $referenced_content['url'];
        $variables['title'] = $referenced_node->title;

        // Set label of entity bundle in result output.
        $variables['content_type'] = t('Promoted');

        // Set empty string to hide a body and prevent of rendering in the
        // default mode. @see: search-result.tpl.php.
        $variables['node_content'] = '';

        $variables['classes_array'][] = 'promoted';
      }
    }
  }
  elseif ($result['entity_type'] === 'file') {
    $variables['content_type'] = t('Document');
  }
  else {
    // Keyword highlighting for non node.
    if ($keyword_highlight == 1) {
      if (isset($variables['node_content']['body'][0]['#markup'])) {
        $variables['node_content']['body'][0]['#markup'] = strip_tags($variables['node_content']['body'][0]['#markup']);
        if ($search_string = arg(2)) {
          $variables['node_content']['body'][0]['#markup'] = _wimbase_highlight_words($variables['node_content']['body'][0]['#markup'], $search_string);
        }
      }
      elseif ($variables['snippet']) {
        $variables['snippet'] = strip_tags($variables['snippet']);
        if ($search_string = arg(2)) {
          $variables['snippet'] = _wimbase_highlight_words($variables['snippet'], $search_string);
        }
      }
    }
  }
}

/**
 * Template preprocess for apachesolr search results.
 */
function wimbase_preprocess_search_results(&$variables) {
  // Display additional label for promoted elements in the search results.
  if (variable_get('wim_linked_keywords_promoted')) {
    if (isset($variables['results'][0]['bundle']) && $variables['results'][0]['bundle'] === 'linked_keywords') {
      $variables['promoted'] = TRUE;
    }
  }
}

/**
 * Highlight words.
 */
function _wimbase_highlight_words($string, $words) {
  $words = check_plain(urldecode($words));
  $string = strip_tags($string);
  preg_match_all('~\w+~', $words, $m);
  if (!$m) {
    return $string;
  }
  $re = '~\\b(' . implode('|', $m[0]) . ')\\b~';
  return preg_replace($re, '<strong>$0</strong>', $string);
}

/**
 * Build a result source link.
 */
function wimbase_result_source_site($result_link, &$variables) {
  // Add source url.
  $parsed_url = parse_url($result_link);
  $source_url = $parsed_url['scheme'] . '://' . $parsed_url['host'];
  $variables['source'] = l($source_url, $source_url, array(
    'absolute' => TRUE,
    'attributes' => array(
      'class' => array('source'),
    ),
  ));

  // Gives opportunity alter result source link.
  drupal_alter('wimbase_result_source_site', $result_link, $variables);
}

/**
 * Implements template_preprocess_bootstrap_tabs().
 */
function wimbase_preprocess_bootstrap_fieldgroup_nav(&$variables) {
  $variables['wrapper_classes'] .= ' tabnav';

  // Add aria-attributes and roles to tabs.
  if (!empty($variables['panes']) && !empty($variables['navs'])) {
    foreach ($variables['navs'] as $key => &$nav) {
      $aria_control = 'aria-controls="' . $variables['panes'][$key]['id'] . '"';
      $nav['content'] = str_replace('<a ', '<a ' . $aria_control . ' role="tab"', $nav['content']);
    }

    $variables['nav_role'] = 'tablist';
    $variables['pane_role'] = 'tabpanel';
    drupal_add_library('system', 'ui');
  }
}

/**
 * Implements hook_preprocess_views_exposed_form().
 */
function wimbase_preprocess_views_exposed_form(&$vars) {
  $form = $vars['form'];

  // Fix date views issue with same ids for multiple elements.
  $prefix = '';
  $counter = 1;
  foreach ($form['#info'] as $key => $filter) {
    if (!empty($form[$filter['value']]['value']) && $form[$filter['value']]['value']['#type'] == 'date_popup') {
      $value = $form[$filter['value']]['value'];

      // Add new widget property so we can know which labels to replace.
      $vars['widgets'][$key]->remove_label = TRUE;

      if ($value['#prefix'] != $prefix) {
        $prefix = $value['#prefix'];
      }
      else {
        $adjusted_widget = preg_replace('/date-value-value-wrapper/', "date-value-value-wrapper-{$counter}", $vars['widgets'][$key]->widget);
        $adjusted_widget = preg_replace('/date-value-value-inside-wrapper/', "date-value-value-inside-wrapper-{$counter}", $adjusted_widget);
        $vars['widgets'][$key]->widget = $adjusted_widget;

        $counter++;
      }
    }
  }
}

/**
 * Calculate bootstrap classes for content and sidebars.
 *
 * @param array $variables
 *    - Page variables.
 * @param int $primary_cols
 *    - Primary sidebar cols number.
 * @param int $secondary_cols
 *    - Secondary sidebar cols number.
 * @param int $offset_primary
 *    - Offset number for content.
 */
function _wimbase_culc_content_cols(&$variables, $primary_cols = 0, $secondary_cols = 0, $offset_primary = 0) {
  $content_cols = 12 - $primary_cols - $secondary_cols;
  $variables['sidebar_first_classes'][] = 'col-sm-' . $primary_cols;
  $variables['content_column_classes'][] = 'col-sm-' . $content_cols;
  // Offset sidebar first.
  if ($offset_primary) {
    $variables['content_column_classes'][] = 'col-sm-offset-' . $offset_primary;
  }

  // Fix accessibility for primary region.
  if ($primary_cols && $content_cols !== 12) {
    $variables['content_column_classes'][] = 'col-md-push-' . $primary_cols;
    $variables['sidebar_first_classes'][] = 'col-md-pull-' . $content_cols;
  }

  $variables['content_column_class'] = ' class="' . implode(' ', $variables['content_column_classes']) . '"';
  $variables['sidebar_first_column_class'] = ' class="' . implode(' ', $variables['sidebar_first_classes']) . '"';
}
