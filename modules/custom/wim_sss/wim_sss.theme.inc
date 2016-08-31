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
    'google' => array(
      'url' => 'https://plus.google.com/share',
      'query' => array(
        'url' => $url,
      ),
      'title' => t('Share this on Google+'),
      'class' => 'fa-google-plus-square',
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
        'summary' => '',
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

  $content['#prefix'] = '<div class="social-links">';
  $content['#suffix'] = '</div>';

  $def = _default_networks($node);
  foreach ($def as $name => $value) {
    $href = url($value['url'], array(
      'query' => $value['query'],
      'external' => TRUE,
    ));
    $content['networks'][$name] = '<a href="' . $href . '" title="' . $value['title'] . '" class="' . $value['class'] . '" rel="nofollow" target="_blank"><span>' . $value['title'] . '</span></a>';
  }

  $content['networks'] = array(
    '#type' => 'markup',
    '#markup' => theme('item_list', array(
      'items' => $content['networks'],
      'attributes' => array('class' => array('social')),
      'title' => t('Share'),
      'type' => 'ul',
    )),
  );

  return drupal_render($content);
}
