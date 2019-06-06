<?php
/**
 * @file
 * File for theme functions wim_sss.theme.inc.
 */

/**
 * Default social link providers.
 *
 * @param \stdClass $node
 *    Node object.
 *
 * @return array
 *    Array of filled items.
 */
function _default_networks(stdClass $node) {
  $url = url('node/' . $node->nid, array('absolute' => TRUE));
  $teaser = field_view_field('node', $node, 'body', array(
    'label' => 'hidden',
    'type' => 'text_summary_or_trimmed',
    'settings' => array(),
  ));

  return array(
    'facebook' => array(
      'url' => 'http://www.facebook.com/sharer.php',
      'query' => array(
        'u' => $url,
        't' => $node->title,
      ),
      'title' => t('Share this on Facebook'),
      'class' => 'fa-facebook-square',
    ),
    'linkedin' => array(
      'url' => 'http://www.linkedin.com/shareArticle',
      'query' => array(
        // Max 1024.
        'url' => $url,
        'mini' => 'TRUE',
        // Max 200.
        'title' => truncate_utf8($node->title, 200),
        // Max 256.
        'summary' => truncate_utf8(strip_tags(render($teaser)), 256),
      ),
      'title' => t('Share this on LinkedIn'),
      'class' => 'fa-linkedin-square',
    ),
    'twitter' => array(
      'url' => 'http://twitter.com/share',
      'query' => array(
        'url' => $url,
        // Max 140.
        'text' => truncate_utf8($node->title, 140),
      ),
      'title' => t('Share this on Twitter'),
      'class' => 'fa-twitter-square',
    ),
  );
}

/**
 * Theme function to render a container full of share links (for a node).
 */
function theme_wim_sss_links($variables) {
  $node = $variables['node'];
  if (!$node) {
    return array();
  }

  $content = array();

  $content['#prefix'] = '<div class="social-links" role="navigation">';
  $content['#suffix'] = '</div>';

  $def = _default_networks($node);
  foreach ($def as $name => $value) {
    $href = url($value['url'], array(
      'query' => $value['query'],
      'external' => TRUE,
    ));
    $content['networks'][$name] = '<a href="' . $href . '" title="' . $value['title'] . '" class="' . $value['class'] . '" rel="nofollow" target="_blank"><span>' . $value['title'] . '</span></a>';
  }

  // Add title separately instead of using item_list to ensure accessibility.
  $content['title'] = [
    '#theme' => 'html_tag',
    '#tag' => 'div',
    '#weight' => 0,
    '#value' => t('Share'),
    '#attributes' => array(
      'class' => array('field-label'),
      'id' => 'social-links-label',
    ),
  ];

  $content['networks'] = array(
    '#type' => 'markup',
    '#weight' => 1,
    '#markup' => theme('item_list', array(
      'items' => $content['networks'],
      'attributes' => array(
        'class' => array('social'),
        'aria-labelledby' => 'social-links-label',
      ),
      'type' => 'ul',
    )),
  );

  return drupal_render($content);
}
