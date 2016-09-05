<?php
/**
 * @file
 * The file for overriding theme functions for the Drupal Wim theme.
 */

/**
 * Returns HTML for a form element label and required marker.
 *
 * Form element labels include the #title and a #required marker. The label is
 * associated with the element itself by the element #id. Labels may appear
 * before or after elements, depending on theme_form_element() and
 * #title_display.
 *
 * This function will not be called for elements with no labels, depending on
 * #title_display. For elements that have an empty #title and are not required,
 * this function will output no label (''). For required elements that have an
 * empty #title, this will output the required marker alone within the label.
 * The label will use the #id to associate the marker with the field that is
 * required. That is especially important for screenreader users to know
 * which field is required.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #required, #title, #id, #value, #description.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see bootstrap_form_element_label()
 *
 * @ingroup theme_functions
 */
function wim_form_element_label(&$variables) {
  $element = $variables['element'];

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // Extract variables.
  $output = '';
  $title = isset($element['#title']) ? filter_xss_admin($element['#title']) . ' ' : '';
  if ($title && ($required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '')) {
    $title .= $required;
  }
  $display = isset($element['#title_display']) ? $element['#title_display'] : 'before';
  $type = !empty($element['#type']) ? $element['#type'] : FALSE;
  $checkbox = $type && $type === 'checkbox';
  $radio = $type && $type === 'radio';

  // Immediately return if the element is not a checkbox or radio and there is
  // no label to be rendered.
  if (!$checkbox && !$radio && ($display === 'none' || !$title)) {
    return '';
  }

  // Retrieve the label attributes array.
  $attributes = &_bootstrap_get_attributes($element, 'label_attributes');

  // Add Bootstrap label class.
  $attributes['class'][] = 'control-label';

  // Add the necessary 'for' attribute if the element ID exists.
  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Checkboxes and radios must construct the label differently.
  if ($checkbox || $radio) {
    if ($display === 'before') {
      $output .= $title;
    }
    elseif ($display === 'none' || $display === 'invisible') {
      $output .= '<span class="element-invisible">' . $title . '</span>';
    }
    // Inject the rendered checkbox or radio element inside the label.
    if (!empty($element['#children'])) {
      $output .= $element['#children'];
    }
    if ($display === 'after') {
      $output .= $title;
    }
  }
  // Otherwise, just render the title as the label.
  else {
    // Show label only to screen readers to avoid disruption in visual flows.
    if ($display === 'invisible') {
      $attributes['class'][] = 'element-invisible';
    }
    $output .= $title;
  }

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <label' . drupal_attributes($attributes) . '>' . $output . "</label>\n";
}

/**
 * Returns HTML for a date element formatted as a single date.
 *
 * Wrap day and month.
 *
 * @see theme_date_display_single
 *
 * @return string
 *    A HTML for single date element.
 */
function wim_date_display_single($variables) {
  $date = $variables['date'];
  $timezone = $variables['timezone'];
  $attributes = $variables['attributes'];
  $format = $variables['dates']['format'];
  $single_day_format = variable_get('date_format_single_day', 'd M');
  $show_remaining_days = isset($variables['show_remaining_days']) ? $variables['show_remaining_days'] : '';

  if ($format === $single_day_format) {
    $date_timestamp = strtotime($date);
    $day = format_date($date_timestamp, 'custom', 'd');
    $month = format_date($date_timestamp, 'custom', 'M');
    $date = '<span class="day">' . $day . '</span><span class="month">' . $month . '</span>';
  }

  $output = '<span class="date-display-single"' . drupal_attributes($attributes) . '>' . $date . $timezone . '</span>';
  if (!empty($variables['add_microdata'])) {
    $output .= '<meta' . drupal_attributes($variables['microdata']['value']['#attributes']) . '/>';
  }

  // Add remaining message and return.
  return $output . $show_remaining_days;
}

/**
 * Bootstrap theme wrapper function for the primary menu links.
 *
 * @see bootstrap_menu_tree__primary()
 */
function wim_menu_tree__primary(&$variables) {
  return '<ul class="menu nav navbar-nav primary">' . $variables['tree'] . '</ul>';
}

/**
 * Returns HTML for a menu link and submenu.
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
function wim_menu_link__main_menu($variables) {
  $element = $variables['element'];
  $sub_menu = '';

  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Build parent item for mobile.
      $parent = '<li class="mobile parent-subitem">' . l($element['#title'], $element['#href']) . '</li>';

      unset($element['#below']['#theme_wrappers']);

      // Add our own wrapper.
      $sub_menu = '<ul class="dropdown-menu">' . $parent . drupal_render($element['#below']) . '</ul>';

      // Generate as standard dropdown.
      $element['#attributes']['class'][] = 'parent-dropdown';
      $element['#localized_options']['html'] = TRUE;
    }
    $element['#attributes']['class'] = array_diff($element['#attributes']['class'], array('expanded'));
  }

  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] == '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }

  $output = l($element['#title'], $element['#href'], $element['#localized_options']);

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Returns HTML for a menu link and submenu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_menu_link()
 *
 * @ingroup theme_functions
 */
function wim_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $icon = NULL;

  $menu_icon = isset($element['#localized_options']['menu_icon']) ? $element['#localized_options']['menu_icon'] : NULL;
  // Add menu item icon.
  if (is_array($menu_icon) && $menu_icon['enable'] && $menu_icon['path']) {
    $icon = '<span><img alt="' . $element['#title'] . '" class="item-icon" src="' . image_style_url($menu_icon['image_style'], $menu_icon['path']) . '"></span>';
    $element['#localized_options']['html'] = TRUE;
  }
  if ($element['#below']) {
    // Prevent dropdown functions from being added to management menu so it
    // does not affect the navbar module.
    if (($element['#original_link']['menu_name'] === 'management') && (module_exists('navbar'))) {
      $sub_menu = drupal_render($element['#below']);
    }
    elseif ((!empty($element['#original_link']['depth'])) && ($element['#original_link']['depth'] == 1)) {
      // Add our own wrapper.
      unset($element['#below']['#theme_wrappers']);
      $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
      // Generate as standard dropdown.
      $element['#attributes']['class'][] = 'dropdown';
      $element['#localized_options']['html'] = TRUE;

      // Set dropdown trigger element to # to prevent inadvertant page loading
      // when a submenu link is clicked.
      $element['#localized_options']['attributes']['data-target'] = '#';
      $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
      $element['#localized_options']['attributes']['data-toggle'] = 'dropdown';
    }
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] === '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $element['#attributes']['class'] = array_diff($element['#attributes']['class'], array('expanded'));

  $output = l($icon . $element['#title'], $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Returns HTML for a Top Tasks menu link and submenu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_menu_link()
 *
 * @ingroup theme_functions
 */
function wim_menu_link__menu_top_tasks(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $icon = NULL;

  $menu_icon = isset($element['#localized_options']['menu_icon']) ? $element['#localized_options']['menu_icon'] : NULL;
  // Add menu item icon.
  if (is_array($menu_icon) && $menu_icon['enable'] && $menu_icon['path']) {
    $icon = '<span><img alt="' . $element['#title'] . '" class="item-icon" src="' . image_style_url($menu_icon['image_style'], $menu_icon['path']) . '"></span>';
    $element['#localized_options']['html'] = TRUE;
  }
  if ($element['#below'] && !empty($element['#original_link']['depth']) && $element['#original_link']['depth'] == 1) {
    // Add our own wrapper.
    unset($element['#below']['#theme_wrappers']);
    $sub_menu = '<ul class="dropdown-menu">' . drupal_render($element['#below']) . '</ul>';
    // Generate as standard dropdown.
    $element['#attributes']['class'][] = 'dropdown';
    $element['#localized_options']['html'] = TRUE;

    // Set dropdown trigger element to # to prevent inadvertant page loading
    // when a submenu link is clicked.
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
  }
  // On primary navigation menu, class 'active' is not set on active menu item.
  // @see https://drupal.org/node/1896674
  if (($element['#href'] == $_GET['q'] || ($element['#href'] === '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
    $element['#attributes']['class'][] = 'active';
  }
  $element['#attributes']['class'] = array_diff($element['#attributes']['class'], array('expanded'));

  if ($element['#original_link']['depth'] == 1 && !$element['#below']) {
    $element['#localized_options']['attributes']['class'][] = 'dropdown-toggle';
    $element['#attributes']['class'][] = 'dropdown';
    $element['#localized_options']['attributes']['class'][] = 'nolink';
  }

  if ($element['#href'] === '<nolink>') {
    $element['#localized_options']['attributes']['class'][] = 'nolink';
    $output = '<a href="#" ' . drupal_attributes($element['#localized_options']['attributes']) . '>' . check_plain($element['#title']) . '</a>';
  }
  else {
    $output = l($icon . $element['#title'], $element['#href'], $element['#localized_options']);
  }

  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Returns HTML for a wrapper for a Top Tasks menu sub-tree.
 *
 * @param array $variables
 *   An associative array containing:
 *   - tree: An HTML string containing the tree's items.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see template_preprocess_menu_tree()
 * @see theme_menu_tree()
 *
 * @ingroup theme_functions
 */
function wim_menu_tree__menu_top_tasks($variables) {
  return '<div class="menu-wrapper"><ul class="menu nav">' . $variables['tree'] . '</ul></div>';
}

/**
 * Returns HTML for a breadcrumb trail.
 *
 * @param array $variables
 *   An associative array containing:
 *   - breadcrumb: An array containing the breadcrumb links.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_breadcrumb()
 *
 * @ingroup theme_functions
 */
function wim_breadcrumb($variables) {
  if (module_exists('hansel')) {
    $hansel_breadcrumb = hansel_get_breadcrumbs();
    $breadcrumb = $hansel_breadcrumb['breadcrumb'];
  }
  else {
    $breadcrumb = $variables['breadcrumb'];
  }

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $output .= '<div class="breadcrumb">' . implode(' / ', $breadcrumb) . '</div>';
    return $output;
  }
}

/**
 * Returns HTML for the Social media menu.
 *
 * @param array $variables
 *   An associative array containing:
 *   - element: Structured array data for a menu link.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_menu_link()
 *
 * @ingroup theme_functions
 */
function wim_menu_link__menu_social_media(array $variables) {
  $element = $variables['element'];
  $element['#localized_options']['html'] = TRUE;

  $output = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
}
