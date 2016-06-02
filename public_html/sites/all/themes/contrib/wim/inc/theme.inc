<?php

/**
 * Overrides theme_breadcrumb().
 * - Add <nav> wrapper.
 * - Add heading.
 */
function dimpact_breadcrumb($vars) {
  if (!empty($vars['breadcrumb']) && count($vars['breadcrumb']) > 1) {
    $heading = t('Breadcrumb Navigation');
    return '<nav class="breadcrumbs"><h2 class="visuallyhidden">' . $heading . "</h2>\n" . implode(' / ', $vars['breadcrumb']) . '</nav>';
  }
  return NULL;
}

/**
 * Overrides theme_mark().
 * - Use <mark> element.
 */
function dimpact_mark($vars) {
  global $user;
  $type = $vars['type'];

  if ($user->uid) {
    if ($type == MARK_NEW) {
      return ' <mark class="new">' . t('new') . '</mark>';
    }
    elseif ($type == MARK_UPDATED) {
      return ' <mark class="updated">' . t('updated') . '</mark>';
    }
  }
  return NULL;
}

/**
 * Overrides theme_menu_local_tasks().
 */
function dimpact_menu_local_tasks(&$vars) {
  $output = '';

  if (!empty($vars['primary'])) {
    $vars['primary']['#prefix'] = '<h2 class="visuallyhidden">' . t('Primary tabs') . '</h2>';
    $vars['primary']['#prefix'] .= '<ul class="tabs primary">';
    $vars['primary']['#suffix'] = '</ul>';
    $output .= render($vars['primary']);
  }
  if (!empty($vars['secondary'])) {
    $vars['secondary']['#prefix'] = '<h2 class="visuallyhidden">' . t('Secondary tabs') . '</h2>';
    $vars['secondary']['#prefix'] = '<ul class="tabs secondary">';
    $vars['secondary']['#suffix'] = '</ul>';
    $output .= render($vars['secondary']);
  }

  if ($output) {
    return '<nav class="tabs" role="navigation">' . $output . '</nav>';
  }
  return NULL;
}

/**
 * Overrides theme_tablesort_indicator().
 */
function dimpact_tablesort_indicator($vars) {
  if ($vars['style'] == 'asc') {
    return ' <span class="sort ascending">' . t('sort ascending') . '</span>';
  }
  else {
    return ' <span class="sort descending">' . t('sort descending') . '</span>';
  }
}

/**
 * Overrides theme_links().
 * This version is from the Edge module. The patch was RTBC for Drupal 7, but it
 * was "too late." In addition to being more efficient it fixes a couple bugs.
 */
function dimpact_links($vars) {
  global $language_url;

  $links = $vars['links'];
  $attributes = $vars['attributes'];
  $heading = $vars['heading'];
  $output = '';

  if (!empty($links)) {
    // Prepend the heading to the list, if any.
    if (!empty($heading)) {
      // Convert a string heading into an array, using a H2 tag by default.
      if (is_string($heading)) {
        $heading = array('text' => $heading);
      }
      // Merge in default array properties into $heading.
      $heading += array(
        'level' => 'h2',
        'attributes' => array(),
      );
      // @todo Remove backwards compatibility for $heading['class'].
      if (isset($heading['class'])) {
        $heading['attributes']['class'] = $heading['class'];
      }

      $output .= '<' . $heading['level'] . drupal_attributes($heading['attributes']) . '>';
      $output .= check_plain($heading['text']);
      $output .= '</' . $heading['level'] . '>';
    }

    $output .= '<ul' . drupal_attributes($attributes) . '>';

    $num_links = count($links);
    $i = 0;
    foreach ($links as $key => $link) {
      $i++;

      $class = array();

      // This fixes a bug caused by running drupal_html_class($key), which
      // could potentially be something like "menu-345 active". Running
      // drupal_html_class() on that turns it into menu-345-active, which is
      // wrong. We need "menu-123 active". This may break stuff elsewhere, so
      // need to test it out a bit.
      $class_friendly_key = explode(' ', $key);
      if (is_array($class_friendly_key)) {
        $class = array_merge($class_friendly_key, $class);
      }
      else {
        // Use the array key as class name.
        $class[] = drupal_html_class($key);
      }


      // Add odd/even, first, and last classes.
      $class[] = ($i % 2 ? 'odd' : 'even');
      if ($i == 1) {
        $class[] = 'first';
      }
      if ($i == $num_links) {
        $class[] = 'last';
      }

      // Handle links.
      if (isset($link['href'])) {
        $is_current_path = ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()));
        $is_current_language = (empty($link['language']) || $link['language']->langcode == $language_url->langcode);
        if ($is_current_path && $is_current_language) {
          $class[] = 'active';
        }
        // Pass in $link as $options, they share the same keys.
        $item = l($link['title'], $link['href'], $link);
      }
      // Handle title-only text items.
      else {
        // Merge in default array properties into $link.
        $link += array(
          'html' => FALSE,
          'attributes' => array(),
        );
        $item = '<span' . drupal_attributes($link['attributes']) . '>';
        $item .= ($link['html'] ? $link['title'] : check_plain($link['title']));
        $item .= '</span>';
      }

      $output .= '<li' . drupal_attributes(array('class' => $class)) . '>';
      $output .= $item;
      $output .= '</li>';
    }

    $output .= '</ul>';
  }

  return $output;
}

/**
 * Overrides theme_more_link().
 * - Removes the wrapping DIV and adds to class to the link itself.
 * - Made the text and title attribute configurable.
 * @todo Make Views use this.
 */
function dimpact_more_link($vars) {
  $title = !empty($vars['title']) ? t($vars['title']) : t('More');
  return l($title, $vars['url'], array(
    'attributes' => array(
      'title' => !empty($vars['title']) ? $vars['title'] : t('More'),
      'class' => array('more-link ' . drupal_html_class($vars['title'])),
      )
    )
  );
}

/**
 * Overrides theme_form().
 * - Removes the wrapper DIV.
 */
function dimpact_form($vars) {
  $element = $vars['element'];
  if (isset($element['#action'])) {
    $element['#attributes']['action'] = drupal_strip_dangerous_protocols($element['#action']);
  }
  element_set_attributes($element, array('method', 'id'));
  if (empty($element['#attributes']['accept-charset'])) {
    $element['#attributes']['accept-charset'] = "UTF-8";
  }
  return '<form' . drupal_attributes($element['#attributes']) . '>' . $element['#children'] . '</form>';
}

/**
 * Overrides theme_item_list().
 * - Use an early D8 version of this. It includes bug fixes.
 * - Remove the div.item-list wrapper.
 */
function dimpact_item_list($variables) {
  $items = $variables['items'];
  $title = (string) $variables['title'];
  $type = $variables['type'];
  $list_attributes = $variables['attributes'];

  $output = '';
  if ($items) {
    $output .= '<' . $type . drupal_attributes($list_attributes) . '>';

    $num_items = count($items);
    $i = 0;
    foreach ($items as $key => $item) {
      $i++;
      $attributes = array();

      if (is_array($item)) {
        $value = '';
        if (isset($item['data'])) {
          $value .= $item['data'];
        }
        $attributes = array_diff_key($item, array('data' => 0, 'children' => 0));

        // Append nested child list, if any.
        if (isset($item['children'])) {
          // HTML attributes for the outer list are defined in the 'attributes'
          // theme variable, but not inherited by children. For nested lists,
          // all non-numeric keys in 'children' are used as list attributes.
          $child_list_attributes = array();
          foreach ($item['children'] as $child_key => $child_item) {
            if (is_string($child_key)) {
              $child_list_attributes[$child_key] = $child_item;
              unset($item['children'][$child_key]);
            }
          }
          $value .= theme('item_list', array(
            'items' => $item['children'],
            'type' => $type,
            'attributes' => $child_list_attributes,
          ));
        }
      }
      else {
        $value = $item;
      }

      $attributes['class'][] = ($i % 2 ? 'odd' : 'even');
      if ($i == 1) {
        $attributes['class'][] = 'first';
      }
      if ($i == $num_items) {
        $attributes['class'][] = 'last';
      }

      $output .= '<li' . drupal_attributes($attributes) . '>' . $value . '</li>';
    }
    $output .= "</$type>";
  }

  // Only output the list container and title, if there are any list items.
  // Check to see whether the block title exists before adding a header.
  // Empty headers are not semantic and present accessibility challenges.
  if ($output !== '') {
    if ($title !== '') {
      $title = '<h3>' . $title . '</h3>';
    }
    $output = $title . $output;
  }

  return $output;
}

/**
 * Overrides dimpact_pager().
 * - Simplify the list item classes.
 * - Remove the arrows from the labels.
 * - Add rel="next/prev" attributes.
 * - Add an empty <a> element to the active link.
 * - Change the "current" class to "active".
 * - Remove first/last classes. theme_item_list() handles this already.
 */
function dimpact_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('First')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('Previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('Next')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => (isset($tags[4]) ? $tags[4] : t('Last')), 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_first) {
      $items[] = array(
        'data' => $li_first,
      );
    }
    if ($li_previous) {
      $items[] = array(
        'class' => array('previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        $items[] = array(
          'class' => array('ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('active'),
            'data' => '<a>' . $i . '</a>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('ellipsis'),
          'data' => '…',
        );
      }
    }
    // End generation.
    if ($li_next) {
      $items[] = array(
        'class' => array('next'),
        'data' => $li_next,
      );
    }
    if ($li_last) {
      $items[] = array(
        'data' => $li_last,
      );
    }
    return '<div class="pagination" role="navigation"><h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
      'items' => $items,
      'attributes' => array('class' => array('pager')),
    )) . '</div>';
  }
}

/**
 * Overrides theme_pager_next().
 * - Adds rel="next" to the link.
 */
function dimpact_pager_next($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  global $pager_page_array, $pager_total;
  $output = '';

  // If we are anywhere but the last page
  if ($pager_page_array[$element] < ($pager_total[$element] - 1)) {
    $page_new = pager_load_array($pager_page_array[$element] + $interval, $element, $pager_page_array);
    // If the next page is the last page, mark the link as such.
    if ($page_new[$element] == ($pager_total[$element] - 1)) {
      $output = theme('pager_last', array('text' => $text, 'element' => $element, 'parameters' => $parameters));
    }
    // The next page is not the last page.
    else {
      $output = theme('pager_link', array('text' => $text, 'page_new' => $page_new, 'element' => $element, 'parameters' => $parameters));
    }
  }

  return $output;
}

/**
 * Overrides theme_pager_previous().
 * - Adds rel="prev" to the link.
 */
function dimpact_pager_previous($variables) {
  $text = $variables['text'];
  $element = $variables['element'];
  $interval = $variables['interval'];
  $parameters = $variables['parameters'];
  global $pager_page_array;
  $output = '';

  // If we are anywhere but the first page
  if ($pager_page_array[$element] > 0) {
    $page_new = pager_load_array($pager_page_array[$element] - $interval, $element, $pager_page_array);

    // If the previous page is the first page, mark the link as such.
    if ($page_new[$element] == 0) {
      $output = theme('pager_first', array('text' => $text, 'element' => $element, 'parameters' => $parameters));
    }
    // The previous page is not the first page.
    else {
      $output = theme('pager_link', array('text' => $text, 'page_new' => $page_new, 'element' => $element, 'parameters' => $parameters));
    }
  }

  return $output;
}

/**
 * Returns HTML for a date element formatted as a single date.
 */
function dimpact_date_display_single($variables) {
  $date = $variables['date'];
  $timezone = $variables['timezone'];
  $attributes = $variables['attributes'];

  if (preg_match("|([a-z]{3})\s([0-9]{2,3})|", $date, $matches)) {
    $date = '<span class="day">' . $matches[2] . '</span><span class="month">' . $matches[1] . '</span>';
  }

  // Wrap the result with the attributes.
  return '<span class="date-display-single"' . drupal_attributes($attributes) . '>' . $date . $timezone . '</span>';
}


/**
 * Format the items shown in the node.
 */
function dimpact_service_links_node_format($variables) {
  $dimpact_service_links_display_style = variable_get('dimpact_service_links_display_style');
  // if display style is overlay
  if ($dimpact_service_links_display_style == 1) {
    $dimpact_share_this_link_widget = '<div class="dimpact_service_links_share_this">' . t('Share this') . '</div>';
    $dimpact_share_this_hide_class = 'dimpact_hide_service_links';
  }
  else {
    $dimpact_share_this_link_widget = '';
    $dimpact_share_this_hide_class = '';
  }

  $links = $variables['links'];
  $label = $variables['label'];
  $view_mode = $variables['view_mode'];
  $node_type = $variables['node_type'];

  if ($view_mode == 'rss') {
    $result = array();
    foreach($links as $l) {
      $result[] = l($l['title'], $l['href'], $l);
    }

    return $dimpact_share_this_link_widget . '<div class="service-links ' . $dimpact_share_this_hide_class . '">' . implode(' ', $result) . '</div>';
  }

  if (isset($label) && !empty($label)) {
    return $dimpact_share_this_link_widget . '<div class="service-links ' . $dimpact_share_this_hide_class . '"><div class="service-label">'. t('@label', array('@label' => $label)) .' </div>'. theme('links', array('links' => $links)) .'</div>';
  }
  else {
    return $dimpact_share_this_link_widget . '<div class="service-links ' . $dimpact_share_this_hide_class . '">'. theme('links', array('links' => $links)) .'</div>';
  }
}

function dimpact_site_map_box($variables) {
  $title = '';
  $content = $variables['content'];
  $attributes = $variables['attributes'];

  $output = '';
  if (!empty($title) || !empty($content)) {
    $output .= '<div' . drupal_attributes($attributes) . '>';
    if (!empty($title)) {
      $output .= '<h2 class="title">' . $title . '</h2>';
    }
    if (!empty($content)) {
      $output .= '<div class="content">' . $content . '</div>';
    }
    $output .= '</div>';
  }

  return $output;
}


function dimpact_menu_link(array $variables) {
  $element = $variables['element'];
  $sub_menu = '';

  $element['#attributes']['class'][] = 'depth-' . $element['#original_link']['depth'];

  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }

  // Toptaken menus are treated differently.
  if (strpos($element['#theme'], 'toptaken') !== FALSE) {
    if (isset($element['#localized_options']['content']) && ($file = file_load($element['#localized_options']['content']['image']))) {
      $image = '<span><img src="' . image_style_url('origineel', $file->uri). '" alt="' . check_plain($file->alt) . '" title="' . check_plain($file->title) . '"></span>';
      $element['#localized_options']['html'] = TRUE;
      $output = l($image . check_plain($element['#title']), $element['#href'], $element['#localized_options']);
    }
    else {
      $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    }
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
  }
  else {
    $output = l($element['#title'], $element['#href'], $element['#localized_options']);
    return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
  }
}

/**
 * Theme function to output content for classic Quicktabs style tabs.
 *
 * @ingroup themeable
 */
function dimpact_qt_quicktabs($variables) {
  $element = $variables['element'];

  $list = array(
    'attributes' => array(
      'class' => 'quicktabs-tabs',
    ),
    'items' => array(),
  );

  foreach (element_children($element['tabs']['tablinks']) as $key) {
    $item = array();
    if (is_array($element['tabs']['tablinks'][$key])) {
      $tab = $element['tabs']['tablinks'][$key];
      if ($key == $element['tabs']['#options']['active']) {
        $item['class'] = array('active');
      }
      $item['data'] = drupal_render($tab) . drupal_render($element['container']['divs'][$key]);
			// $item['data'] = drupal_render($tab);
      $list['items'][] = $item;
    }
  }
  // return theme('item_list', $list);

  $output = '<div '. drupal_attributes($element['#options']['attributes']) .'>';
  // $output .= drupal_render($element['tabs']);
  $output .= theme('item_list', $list);
  // $output .= drupal_render($element['container']);
  $output .= '</div>';
  return $output;
}


/**
 * Override or insert javascript on the site.
 *
 * @param $js
 *   An array of all JavaScript being presented on the page.
 */
function dimpact_js_alter(&$javascript) {
	// Use our own vesion of quicktabs.js
	$old_path = drupal_get_path('module', 'quicktabs');
	$new_path = drupal_get_path('theme', 'dimpact');
	$file = '/js/quicktabs.js';
	$javascript[$old_path . $file] = drupal_js_defaults($new_path . $file);
}

/**
 * Override required asterisk on forms
 *
 * @param $variables
 */
function dimpact_form_required_marker($variables) {
  // This is also used in the installer, pre-database setup.
  $t = get_t();
  $attributes = array(
    'class' => 'form-required',
    'title' => $t('This field is required.'),
  );
  return '<span' . drupal_attributes($attributes) . '>verplicht</span>';
}
