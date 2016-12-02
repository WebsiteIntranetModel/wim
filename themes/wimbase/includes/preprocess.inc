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
          $total_col = 0;
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
}

/**
 * Template preprocess for apachesolr search results.
 */
function wimbase_preprocess_search_result(&$variables) {
  $result = $variables['result'];

  // Add source url.
  $result_link = $result['link'];
  $parsed_url = parse_url($result_link);
  $source_url = $parsed_url['scheme'] . '://' . $parsed_url['host'];
  $variables['source'] = l($source_url, $source_url, array(
    'absolute' => TRUE,
    'attributes' => array(
      'class' => array('source'),
    ),
  ));

  if (isset($result['node']) && $node = node_load($result['node']->entity_id)) {
    $content_types_labels = array(
      'page' => t('General information'),
    );
    $variables['node_content'] = node_view($node, 'search_result');
    // Add content type label.
    $variables['content_type'] = isset($content_types_labels[$node->type]) ? $content_types_labels[$node->type] : ucfirst($node->type);
  }
}

/**
 * Implements hook_preprocess_views_exposed_form().
 */
function wimbase_news_preprocess_views_exposed_form(&$vars) {
  $form = $vars['form'];

  // Fix date views issue with same ids for multiple elements
  $prefix = '';
  $counter = 1;
  foreach ($form['#info'] as $key => $filter) {
    if (!empty($form[$filter['value']]['value']) && $form[$filter['value']]['value']['#type'] == 'date_popup') {
      $value = $form[$filter['value']]['value'];

      // Add new widget property so we can know which labels to replace
      $vars['widgets'][$key]->remove_label = TRUE;

      if ($value['#prefix'] != $prefix) {
        $prefix = $value['#prefix'];
      }
      else {
        $adjusted_prefix = preg_replace('/date-value-value-wrapper/', "date-value-value-wrapper-{$counter}", $value['#prefix']);
        $adjusted_prefix = preg_replace('/date-value-value-inside-wrapper/', "date-value-value-inside-wrapper-{$counter}", $adjusted_prefix);
        $vars['form'][$filter['value']]['value']['#prefix'] = $adjusted_prefix;

        $counter++;
      }
    }
  }
}
