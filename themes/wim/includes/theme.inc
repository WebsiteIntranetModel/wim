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
