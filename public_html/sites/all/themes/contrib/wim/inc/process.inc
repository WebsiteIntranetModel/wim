<?php

/**
 * Implements template_process().
 */
function dimpact_process(&$vars) {
  // Use one variable for attributes!
  if ($vars['classes']) {
    $vars['attributes'] = ' class="' . $vars['classes'] . '"' . $vars['attributes'];
  }
}

/**
 * Implements hook_process_html().
 */
function dimpact_process_html(&$vars) {
  // Flatten out html_attributes and body_attributes, which are defined
  // in dimpact_preprocess_html().
  $vars['html_attributes'] = drupal_attributes($vars['html_attributes_array']);
  if ($vars['classes']) {
    $vars['body_attributes'] = $vars['attributes'];
  }

  if (module_exists('domain_scss')) {
    _domain_scss_html_alter($vars);
  }
}

/**
 * Implements hook_process_page().
 */
function dimpact_process_page(&$vars) {
  if (isset($vars['suppress_node_title'])) {
    // Prevent the title from being printed in both the node and page template
    // when a full node is being viewed. In order to have properly sectioned HTML5
    // markup for nodes, we must ensure the title is printed inside the node
    // template, as opposed to the page.tpl.php template.
    if (!empty($vars['node']) && $vars['page'] && !arg(2)) {
      unset($vars['title']);
    }
  }
}


/**
 * Implements hook_process_html_tag().
 */
function dimpact_process_html_tag(&$vars) {
  $element = &$vars['element'];

  // Remove type attribute and CDATA comments from script/link/style tags.
  if (in_array($element['#tag'], array('script', 'link', 'style'))) {
    unset($element['#attributes']['type']);
    unset($element['#value_prefix']);
    unset($element['#value_suffix']);
  }
}
