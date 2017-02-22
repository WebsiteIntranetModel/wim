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
function wimbase_form_element_label(&$variables) {
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
function wimbase_date_display_single($variables) {
  $date = $variables['date'];
  $timezone = $variables['timezone'];
  $attributes = $variables['attributes'];
  $format = $variables['dates']['format'];
  $single_day_format = variable_get('date_format_single_day', 'd M');
  $show_remaining_days = isset($variables['show_remaining_days']) ? $variables['show_remaining_days'] : '';

  if ($format === $single_day_format) {
    $date = $variables['dates']['value']['formatted_iso'];
    $date_timestamp = (int) strtotime($date);
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
function wimbase_menu_tree__primary(&$variables) {
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
function wimbase_menu_link__main_menu($variables) {
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
  if (($element['#href'] == $_GET['q'] || ($element['#href'] === '<front>' && drupal_is_front_page())) && (empty($element['#localized_options']['language']))) {
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
function wimbase_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $icon = NULL;

  $menu_icon = isset($element['#localized_options']['menu_icon']) ? $element['#localized_options']['menu_icon'] : NULL;
  // Add menu item icon.
  if (is_array($menu_icon) && $menu_icon['enable'] && $menu_icon['path']) {
    $icon = '<span><img alt="' . $element['#title'] . '" class="item-icon rs_skip" src="' . image_style_url($menu_icon['image_style'], $menu_icon['path']) . '"></span>';
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
function wimbase_menu_link__menu_top_tasks(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';
  $icon = NULL;

  $menu_icon = isset($element['#localized_options']['menu_icon']) ? $element['#localized_options']['menu_icon'] : NULL;
  // Add menu item icon.
  if (is_array($menu_icon) && $menu_icon['enable'] && $menu_icon['path']) {
    $icon = '<span><img alt="' . $element['#title'] . '" class="item-icon rs_skip" src="' . image_style_url($menu_icon['image_style'], $menu_icon['path']) . '"></span>';
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
function wimbase_menu_tree__menu_top_tasks($variables) {
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
function wimbase_breadcrumb($variables) {
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
    $title = '<p id="breadcrums-nav-title" class="element-invisible">'
      . t('You are here') . '</p>';
    $output = '<nav class="breadcrumb" aria-labelledby="breadcrums-nav-title" role="navigation">'
      . $title . implode(' / ', $breadcrumb) . '</nav>';
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
function wimbase_menu_link__menu_social_media(array $variables) {
  $element = $variables['element'];
  $element['#localized_options']['html'] = TRUE;

  $output = l('<span>' . $element['#title'] . '</span>', $element['#href'], $element['#localized_options']);
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . "</li>\n";
}

/**
 * Returns HTML for an active facet item.
 *
 * @see theme_facetapi_link_active()
 *
 * @ingroup themeable
 */
function wimbase_facetapi_link_active($variables) {
  // Sanitizes the link text if necessary.
  $sanitize = empty($variables['options']['html']);
  $link_text = ($sanitize) ? check_plain($variables['text']) : $variables['text'];

  // Theme function variables fro accessible markup.
  // @see http://drupal.org/node/1316580
  $accessible_vars = array(
    'text' => $variables['text'],
    'active' => TRUE,
  );

  // Builds link, passes through t() which gives us the ability to change the
  // position of the widget on a per-language basis.
  $replacements = array(
    '!facetapi_deactivate_widget' => theme('facetapi_deactivate_widget', $variables),
    '!facetapi_accessible_markup' => theme('facetapi_accessible_markup', $accessible_vars),
    '!link_text' => $link_text,
  );
  $variables['text'] = t('!facetapi_accessible_markup !link_text', $replacements);
  $variables['options']['html'] = TRUE;
  return theme_link($variables);
}

/**
 * Returns HTML for an image with an appropriate icon for the given file.
 *
 * @param array $variables
 *   An associative array containing:
 *   - file: A file object for which to make an icon.
 *   - icon_directory: (optional) A path to a directory of icons to be used for
 *     files. Defaults to the value of the "file_icon_directory" variable.
 *   - alt: (optional) The alternative text to represent the icon in text-based
 *     browsers. Defaults to an empty string.
 *
 * @ingroup themeable
 */
function wimbase_file_icon($variables) {
  $file = $variables['file'];
  $alt = $variables['alt'];
  $icon_directory = $variables['icon_directory'];

  $icon_url = file_icon_url($file, $icon_directory);
  return '<img class="file-icon" alt="' . check_plain($alt) . '" src="' . $icon_url . '" />';
}

/**
 * Returns HTML for a link to a file.
 *
 * @param array $variables
 *   An associative array containing:
 *   - file: A file object to which the link will be created.
 *   - icon_directory: (optional) A path to a directory of icons to be used for
 *     files. Defaults to the value of the "file_icon_directory" variable.
 *
 * @ingroup themeable
 */
function wimbase_file_link($variables) {
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $url = file_create_url($file->uri);

  // Human-readable names, for use as text-alternatives to icons.
  $mime_name = array(
    'application/msword' => t('Microsoft Office document'),
    'application/vnd.ms-excel' => t('Office spreadsheet'),
    'application/vnd.ms-powerpoint' => t('Office presentation'),
    'application/pdf' => t('PDF'),
    'video/quicktime' => t('Movie'),
    'audio/mpeg' => t('Audio'),
    'audio/wav' => t('Audio'),
    'image/jpeg' => t('Image'),
    'image/png' => t('Image'),
    'image/gif' => t('Image'),
    'application/zip' => t('Package'),
    'text/html' => t('HTML'),
    'text/plain' => t('Plain text'),
    'application/octet-stream' => t('Binary Data'),
  );

  $mimetype = file_get_mimetype($file->uri);

  $icon = theme('file_icon', array(
    'file' => $file,
    'icon_directory' => $icon_directory,
    'alt' => !empty($mime_name[$mimetype]) ? $mime_name[$mimetype] : t('File'),
  ));

  // Set options as per anchor format described at
  // http://microformats.org/wiki/file-format-examples
  $options = array(
    'attributes' => array(
      'type' => $file->filemime . '; length=' . $file->filesize,
    ),
  );

  // Use the description as the link text if available.
  if (empty($file->description)) {
    $link_text = $file->filename;
  }
  else {
    $link_text = $file->description;
    $options['attributes']['title'] = check_plain($file->filename);
  }

  return '<span class="file">' . $icon . ' ' . l($link_text, $url, $options) . '</span>';
}

/**
 * Returns HTML for files search results.
 */
function wimbase_apachesolr_search_snippets__file($vars) {
  $snippets = $vars['flattened_snippets'];

  return implode(' ... ', $snippets);
}

/**
 * Returns HTML for status and/or error messages, grouped by type.
 *
 * An invisible heading identifies the messages for assistive technology.
 * Sighted users see a colored box. See http://www.w3.org/TR/WCAG-TECHS/H69.html
 * for info.
 *
 * @param array $variables
 *   An associative array containing:
 *   - display: (optional) Set to 'status' or 'error' to display only messages
 *     of that type.
 *
 * @return string
 *   The constructed HTML.
 *
 * @see theme_status_messages()
 *
 * @ingroup theme_functions
 */
function wimbase_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Informative message'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'danger',
    'warning' => 'warning',
    // Not supported, but in theory a module could send any type of message.
    // @see drupal_set_message()
    // @see theme_status_messages()
    'info' => 'info',
  );

  // Retrieve messages.
  $message_list = drupal_get_messages($display);

  // Allow the disabled_messages module to filter the messages, if enabled.
  if (module_exists('disable_messages') && variable_get('disable_messages_enable', '1')) {
    $message_list = disable_messages_apply_filters($message_list);
  }

  foreach ($message_list as $type => $messages) {
    $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    $output .= "<div class=\"alert alert-block$class messages $type\">\n";
    $output .= "  <a class=\"close\" data-dismiss=\"alert\" href=\"#\">&times;</a>\n";

    if (!empty($status_heading[$type])) {
      $output .= '<h4 class="element-invisible">' . _bootstrap_filter_xss($status_heading[$type]) . "</h4>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $attributes = drupal_attributes(array('id' => md5($message)));
        $output .= '  <li ><span ' . $attributes . '>' . _bootstrap_filter_xss($message) . "</span></li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $attributes = drupal_attributes(array('id' => md5($messages[0])));
      $output .= '<span ' . $attributes . '>' . _bootstrap_filter_xss($messages[0]) . '</span>';
    }

    $output .= "</div>\n";
  }
  return $output;
}
