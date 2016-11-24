<?php
/**
 * @file
 * The file for overriding theme functions for the WIM STARTERKIT theme.
 */

/**
 * Implements template_preprocess_block().
 */
function coe_preprocess_block(&$variables) {
  $block = $variables['block'];
  $block_module = $block->module;

  if ($block_module === 'bean' && $bean = bean_load_delta($block->delta)) {
    if ($block->data['config']['bean_view_mode'] === 'header_image') {
      // Remove title from block.tpl.php if view mode is header_image.
      $variables['block']->subject = '';
    }
  }
}

/**
 * Implements template_preprocess_entity().
 */
function coe_preprocess_entity(&$variables) {
  // Make title linkable for bean blocks with header_image as view mode.
  if ($variables['entity_type'] === 'bean' && $variables['view_mode'] === 'header_image') {
    $bean = $variables['bean'];
    if (!empty($bean->field_link) && isset($variables['content']['title'])) {
      $title_link = $bean->field_link[LANGUAGE_NONE][0]['url'];
      $title = $variables['content']['title']['#value'];

      // Build the link.
      $title_linked = l($title, $title_link);

      // Replace current values with processed value.
      $variables['content']['title']['#value'] = $title_linked;
      $variables['content']['title']['#attributes']['class'] .= ' block-title';
    }
  }
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * Coevorden mod: do not render submenu's for main menu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see bootstrap_menu_link()
 *
 * @ingroup theme_functions
 */
function coe_menu_link__main_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}
