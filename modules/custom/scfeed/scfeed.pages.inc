<?php

/**
 * @file
 * Page and form callbacks.
 */

/**
 * Form callback for settings form.
 */
function scfeed_settings_form($form, &$form_state) {
  $query = db_select('queue', 'q')->condition('q.name', 'scfeed');
  $query->addExpression('COUNT(*)');
  $queue_items = $query->execute()->fetchField();
  $form['info'] = [
    '#markup' => '<p>' . t('There are currently <strong>@count item(s)</strong> in the queue.', ['@count' => $queue_items]) . '</p>',
  ];

  $form['scfeed_authority'] = [
    '#type' => 'select',
    '#title' => t('Authority'),
    '#options' => scfeed_get_authorities(),
    '#description' => t('Select the authority used in the exported feed.'),
    '#default_value' => variable_get('scfeed_authority', ''),
    '#required' => TRUE,
  ];

  $form['#submit'][] = 'scfeed_rebuild';

  return system_settings_form($form);
}

/**
 * Form callback for rebuild form.
 */
function scfeed_rebuild_form($form, &$form_state) {
  $form = confirm_form($form, t('Are you sure you want to rebuild all items?'), 'admin/config/services/scfeed');

  $form['delete'] = [
    '#type' => 'checkbox',
    '#title' => t('Delete existing items before rebuilding'),
  ];

  return $form;
}

/**
 * Submit hamdler for rebuild form.
 */
function scfeed_rebuild_form_submit($form, &$form_state) {
  $delete = !empty($form_state['values']['delete']);
  scfeed_rebuild($delete);
  drupal_set_message(t('All products are queued for rebuilding XML representation.'));
  $form_state['redirect'] = 'admin/config/services/scfeed';
}

/**
 * Menu callback for /sc-feed.
 */
function scfeed_feed_page() {
  $items = [];

  $query = db_select('node', 'n')
    ->condition('n.status', 1)
    ->condition('n.type', 'product');
  $i = $query->join('scfeed_item', 'i', 'n.nid = i.nid');
  $query->addField($i, 'xml');
  $query->addTag('node_access');
  $nodes = $query->execute();
  while ($node = $nodes->fetchObject()) {
    $items[] = $node->xml;
  }

  drupal_add_http_header('Content-Type', 'text/xml');
  print scfeed_feed_wrap_items($items);
}

/**
 * Wrap items in a full XML document.
 *
 * @param array $items
 *    Items.
 *
 * @return string
 *    XML string.
 */
function scfeed_feed_wrap_items($items) {
  $ns_sc = 'http://standaarden.overheid.nl/product/terms/';
  $ns_overheid = 'http://standaarden.overheid.nl/owms/terms/';
  $ns_dcterms = 'http://purl.org/dc/terms/';
  $ns_xsi = 'http://www.w3.org/2001/XMLSchema-instance';

  $dom = new DOMDocument('1.0', 'utf-8');
  $dom->formatOutput = TRUE;
  $products = $dom->createElement('scproducten');
  $products->setAttribute('xmlns', $ns_sc);
  $products->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:dcterms', $ns_dcterms);
  $products->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:overheid', $ns_overheid);
  $products->setAttributeNS($ns_xsi, 'xsi:schemaLocation', 'http://standaarden.overheid.nl/product/terms/ http://standaarden.overheid.nl/sc/4.0/xsd/sc.xsd');
  $dom->appendchild($products);

  $placeholder = $dom->createElement('placeholder');
  $products->appendChild($placeholder);

  $xml = $dom->saveXML();
  return str_replace('<placeholder/>', implode($items), $xml);
}

/**
 * Get list of authorities.
 *
 * @return array
 *    List of authorities.
 */
function scfeed_get_authorities() {
  $values = [];

  $dom = new DOMDocument();
  $dom->load(drupal_get_path('module', 'scfeed') . '/assets/authorities.xml');
  $child = $dom->documentElement->firstChild;
  do {
    $item = scfeed_read_authority_value($child);
    $values[$item->value . '|' . $item->key] = $item->key;
  } while ($child = $child->nextSibling);

  return $values;
}

/**
 * Read <value> tag from authorities.xml.
 *
 * @param DOMElement $element
 *    DOM Element.
 *
 * @return object
 *    Object.
 */
function scfeed_read_authority_value(DOMElement $element) {
  $output = new stdClass();
  $child = $element->firstChild;
  do {
    switch ($child->tagName) {
      case 'prefLabel':
        $output->key = $child->nodeValue;
        break;

      case 'resourceIdentifier':
        $output->value = $child->nodeValue;
        break;
    }
  } while ($child = $child->nextSibling);
  return $output;
}
