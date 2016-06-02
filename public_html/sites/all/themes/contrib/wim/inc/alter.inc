<?php

/**
 * Implements hook_html_head_alter().
 */
function dimpact_html_head_alter(&$head_elements) {
  global $theme;
  // Get the path to the active theme (not necessarily this theme).
  $path = drupal_get_path('dimpact', $theme);

  // Simplify the meta charset element.
  $head_elements['system_meta_content_type']['#attributes'] = array(
    'charset' => 'utf-8',
  );

  // Simplify the meta charset element.
  $head_elements['system_meta_content_type_full'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#weight' => -100,
    '#attributes' => array(
      'http-equiv' => 'Content-type',
      'content' => 'text/html; charset=utf-8',
    ),
  );

  // Use Chrome Frame.
  $head_elements['dimpact_chrome_frame'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'X-UA-Compatible',
      'content' => 'IE=edge',
    ),
  );

  // Mobile-friendly Viewport settings.
  $head_elements['dimpact_handheld_friendly'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'HandheldFriendly',
      'content' => 'True',
    ),
  );
  $head_elements['dimpact_mobile_optimized'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'MobileOptimized',
      'content' => 'width',
    ),
  );
  $head_elements['dimpact_viewport'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'name' => 'viewport',
      'content' => 'width=device-width,initial-scale=1.0',
    ),
  );

  // Activate ClearType for Mobile IE.
  $head_elements['dimpact_cleartype'] = array(
    '#type' => 'html_tag',
    '#tag' => 'meta',
    '#attributes' => array(
      'http-equiv' => 'cleartype',
      'content' => 'on',
    ),
    '#prefix' => '<!--[if IE]>',
    '#suffix' => '<![endif]-->',
  );

  // Apple Touch Icons. See: http://mathiasbynens.be/notes/touch-icons
  // Note: When a subtheme is active, this pulls the icons from the subtheme,
  // not the base theme. Make sure these files exist.

  // For third-generation iPad with high-resolution Retina display.
//  $head_elements['dimpact_apple_touch_144'] = array(
//    '#type' => 'html_tag',
//    '#tag' => 'link',
//    '#attributes' => array(
//      'rel' => 'apple-touch-icon-precomposed',
//      'sizes' => '144x144',
//      'href' => $path . '/img/apple/apple-touch-icon-144x144-precomposed.png'
//    ),
//  );
  // iPhone 4 with high-resolution Retina display.
//  $head_elements['dimpact_apple_touch_114'] = array(
//    '#type' => 'html_tag',
//    '#tag' => 'link',
//    '#attributes' => array(
//      'rel' => 'apple-touch-icon-precomposed',
//      'sizes' => '114x114',
//      'href' => $path . '/img/apple/apple-touch-icon-114x114-precomposed.png'
//    ),
//  );
  // First and second generation iPads.
//  $head_elements['dimpact_apple_touch_72'] = array(
//    '#type' => 'html_tag',
//    '#tag' => 'link',
//    '#attributes' => array(
//      'rel' => 'apple-touch-icon-precomposed',
//      'sizes' => '72x72',
//      'href' => $path . '/img/apple/apple-touch-icon-72x72-precomposed.png'
//    ),
//  );
  // Fallback...
  // Non-Retina iPhone, iPod Touch, and Android 2.1+ devices.
  // Also be sure to include apple-touch-icon.png. iOS 1 and Blackberry don't
  // support the precomposed option,
//  $head_elements['dimpact_apple_touch'] = array(
//    '#type' => 'html_tag',
//    '#tag' => 'link',
//    '#attributes' => array(
//      'rel' => 'apple-touch-icon-precomposed',
//      'href' => $path . '/img/apple/apple-touch-icon-precomposed.png'
//    ),
//  );
}

/**
 * Implements hook_css_alter().
 */
function dimpact_css_alter(&$css) {
  $theme = drupal_get_path('theme', 'dimpact');

  // Remove some stylesheets.
  unset(
    $css['modules/user/user.css'],
    $css['misc/ui/jquery.ui.theme.css'],
    $css['modules/comment/comment.css'],
    $css['modules/field/theme/field.css'],
    $css['modules/filter/filter.css'],
    $css['modules/node/node.css'],
    $css['modules/search/search.css'],
    $css['modules/system/system.menus.css'],
    $css['modules/system/system.messages.css'],
    $css['modules/system/system.theme.css'],
    $css[drupal_get_path('module', 'ctools') . '/css/ctools.css'],
    $css[drupal_get_path('module', 'views') . '/css/views.css'],
    $css[drupal_get_path('module', 'context') . '/plugins/context_reaction_block.css']
  );

  // Use the theme's reset instead of system.base.css.
  if (isset($css['modules/system/system.base.css'])) {
    $css['modules/system/system.base.css']['data'] = $theme . '/css/global.css';
    $css['modules/system/system.base.css']['group'] = CSS_SYSTEM;
  }

  // Set the default media type to screen.
  foreach ($css as $path => $value) {
    if ($css[$path]['media'] == 'all') {
      $css[$path]['media'] = 'screen';
    }
  }

  // Load the Contextual CSS last, whether overridden or not.
  if (isset($css['modules/contextual/contextual.css'])) {
    $css['modules/contextual/contextual.css']['group'] = CSS_THEME;
    $css['modules/contextual/contextual.css']['weight'] = 100;
  }
}

/**
 * Implements hook_page_alter().
 */
function dimpact_page_alter(&$page) {
  // Remove all the region wrappers, except for page_top and page_bottom.
  foreach (element_children($page) as $key => $region) {
    if (!empty($page[$region]['#theme_wrappers']) && !in_array($region, array('page_top', 'page_bottom'))) {
      $page[$region]['#theme_wrappers'] = array_diff($page[$region]['#theme_wrappers'], array('region'));
    }
  }
  // Remove the wrapper from the main content block.
  if (!empty($page['content']['system_main'])) {
    $page['content']['system_main']['#theme_wrappers'] = array_diff($page['content']['system_main']['#theme_wrappers'], array('block'));
  }

}

/**
 * Implements hook_node_view_alter().
 */
function dimpact_node_view_alter(&$build) {
  // If teaser and there are links to be rendered, have node.tpl.php render node teaser link and no other link.
  if ($build['#view_mode'] == 'teaser' && isset($build['#theme']) && $build['#theme'] == 'node') {
    // Hide all groups except node.
    if (isset($build['links'])) {
      array_walk(
        $build['links'],
        function(&$element, $key, $children_keys) {
          if (in_array($key, $children_keys, TRUE) && $key != 'node') {
            $element['#access'] = FALSE;
          }
        },
        element_children($build['links'])
      );
    }
    // Preserve node teaser read more, kill all other node links.
    if (isset($build['links']['node']['#links']['node-readmore'])) {
      $build['links']['node']['#links'] = array('node-readmore' => $build['links']['node']['#links']['node-readmore']);
    }
    else {
      $build['links']['node']['#access'] = FALSE;
    }
  }
}
