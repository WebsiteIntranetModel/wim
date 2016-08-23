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
function wim_preprocess_node(&$variables) {
  $node = $variables['node'];
  $view_mode = $variables['view_mode'];
  $content_type = $variables['type'];

  // Hook suggestion node--view_mode.tpl.php.
  $variables['theme_hook_suggestions'][] = 'node__' . strtr($view_mode, '_', '-');
  // Hook suggestion node--content_type--view_mode.tpl.php.
  $variables['theme_hook_suggestions'][] = 'node__' . $node->type . '__' . strtr($view_mode, '_', '-');

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
function wim_preprocess_region(&$variables) {
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
    $same_row = FALSE;
    foreach (element_children($variables['elements']) as $element_id) {
      if (isset($variables['elements'][$element_id]['#block'])) {
        $block = $variables['elements'][$element_id]['#block'];

        // Place element in a new  row.
        if ($block->new_row) {
          $row_id++;
          $rows[$row_id][] = $variables['elements'][$element_id]['#children'];
          $total_col = 0;
          // Next element can't be placed in the same row with current.
          $same_row = FALSE;
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
            if (!$same_row) {
              $row_id++;
              $same_row = TRUE;
            }
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
function wim_preprocess_block(&$variables) {
  $block = &$variables['block'];
  // Be default we show all blocks in a new row.
  $block->new_row = TRUE;
  $block->bootstrap_layout = WIM_BLOCK_MANAGEMENT_BOOTSTRAP_FULL_WIDTH;
  $bean_view_mode = NUll;

  // Process Bean blocks.
  if ($block->module === 'bean') {
    $variables['title_url'] = NULL;
    $bean = bean_load_delta($block->delta);
    $variables['theme_hook_suggestions'][] = 'block__bean_' . strtr($bean->type, '_', '-');
    $bean_view_mode = $bean->view_mode;

    if ($bean->view_mode === 'link_title' && $bean->field_link) {
      $variables['title_url'] = $bean->field_link[LANGUAGE_NONE][0]['url'];
    }
  }

  // If block in the Felix region add corresponding classes.
  if (isset($block->felix_region)) {
    if (isset($block->data['config'])) {
      $config = $block->data['config'];
      // Add bootstrap class to block output.
      if (isset($config['bootstrap_layout'])) {
        $variables['classes_array'][] = 'col-md-' . $config['bootstrap_layout'];
        $block->bootstrap_layout = $config['bootstrap_layout'];
      }
      // If new row config exist then use it otherwise move it in a new row.
      $block->new_row = isset($config['new_row']) ? $config['new_row'] : TRUE;

      if ($block->module === 'bean') {
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
            $variables['title_url'] = NULL;
            if ($config['bean_view_mode'] === 'link_title' && $bean->field_link) {
              $variables['title_url'] = $bean->field_link[LANGUAGE_NONE][0]['url'];
            }
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
}

/**
 * Implements hook_preprocess_field().
 */
function wim_preprocess_field(&$variables, $hook) {
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

}
