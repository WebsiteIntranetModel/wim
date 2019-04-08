<?php

/**
 * @file
 * Functions to generate XML representation for node.
 */

/**
 * Generate XML representation for item.
 *
 * @param object $node
 *    Node object.
 */
function scfeed_generate_item($node) {
  $ns_sc = 'http://standaarden.overheid.nl/product/terms/';
  $ns_overheid = 'http://standaarden.overheid.nl/owms/terms/';
  $ns_dcterms = 'http://purl.org/dc/terms/';
  $ns_xsi = 'http://www.w3.org/2001/XMLSchema-instance';

  $dom = new DOMDocument();
  $dom->formatOutput = TRUE;
  $products = $dom->createElement('scproducten');
  $products->setAttribute('xmlns', $ns_sc);
  $products->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:dcterms', $ns_dcterms);
  $products->setAttributeNS('http://www.w3.org/2000/xmlns/', 'xmlns:overheid', $ns_overheid);
  $products->setAttributeNS($ns_xsi, 'xsi:schemaLocation', 'http://standaarden.overheid.nl/product/terms/ http://standaarden.overheid.nl/sc/4.0/xsd/sc.xsd');
  $dom->appendchild($products);

  $product = $dom->createElement('scproduct');
  $product->setAttribute('owms-version', '4.0');
  $products->appendChild($product);

  $meta = $dom->createElement('meta');
  $product->appendChild($meta);
  $body = $dom->createElement('body');
  $product->appendChild($body);

  $owmskern = $dom->createElement('owmskern');
  $meta->appendChild($owmskern);

  $element = $dom->createElementNS($ns_dcterms, 'dcterms:identifier', url('node/' . $node->nid, array('absolute' => TRUE)));
  $owmskern->appendChild($element);

  $element = $dom->createElementNS($ns_dcterms, 'dcterms:title');
  $element->appendChild($dom->createCDATASection($node->title));
  $owmskern->appendChild($element);

  $element = $dom->createElementNS($ns_dcterms, 'dcterms:language', 'nl');
  $owmskern->appendChild($element);

  $element = $dom->createElementNS($ns_dcterms, 'dcterms:type', 'productbeschrijving');
  $element->setAttribute('scheme', 'overheid:Informatietype');
  $owmskern->appendChild($element);

  $element = $dom->createElementNS($ns_dcterms, 'dcterms:modified', format_date($node->changed, 'custom', 'Y-m-d'));
  $owmskern->appendChild($element);

  list($authority_value, $authority_label) = explode('|', variable_get('scfeed_authority', ''));
  $element = $dom->createElementNS($ns_dcterms, 'dcterms:spatial', $authority_label);
  $element->setAttribute('scheme', 'overheid:Gemeente');
  $element->setAttribute('resourceIdentifier', $authority_value);
  $owmskern->appendChild($element);

  list($authority_value, $authority_label) = explode('|', variable_get('scfeed_authority', ''));
  $element = $dom->createElementNS($ns_overheid, 'overheid:authority', $authority_label);
  $element->setAttribute('scheme', 'overheid:Gemeente');
  $element->setAttribute('resourceIdentifier', $authority_value);
  $owmskern->appendChild($element);

  $element = $dom->createElement('productHTML');
  $generate_body = scfeed_generate_body($node);
  $element->appendChild($dom->createCDATASection($generate_body));
  $body->appendChild($element);

  // Create owmsmantel.
  $owmsmantel = $dom->createElement('owmsmantel');
  $meta->appendChild($owmsmantel);

  // Set the value of owmsmantel audience.
  if (!empty($node->field_sc_audience)) {
    foreach ($node->field_sc_audience[LANGUAGE_NONE] as $item) {
      $element = $dom->createElementNS($ns_dcterms, 'dcterms:audience', $item['value']);
      $element->setAttribute('scheme', 'overheid:Doelgroep');
      $owmsmantel->appendChild($element);
    }
  }
  else {
    // If empty don't generate the record.
    return;
  }

  // Get tags for owmsmantel subject.
  if (!empty($node->field_tags[LANGUAGE_NONE])) {
    $tags = $node->field_tags[LANGUAGE_NONE];
    $tags_end = end($tags);
    $subject = '';
    foreach ($tags as $item) {
      $term = taxonomy_term_load($item['tid']);
      if ($item['tid'] == $tags_end['tid']) {
        $subject .= $term->name;
      }
      else {
        $subject .= $term->name . ', ';
      }
    }
  }
  else {
    $subject = $node->title;
  }

  // Set the value of owmsmantel subject.
  $element = $dom->createElementNS($ns_dcterms, 'dcterms:subject');
  $element->appendChild($dom->createCDATASection($subject));
  $owmsmantel->appendChild($element);

  // Set the value of owmsmantel abstract.
  $teaser = text_summary($generate_body, 'full_html', 200);
  $teaser = preg_replace('/\\<(p|li|table|h)/si', ' <\\1', $teaser);
  $teaser = trim(strip_tags($teaser));
  // Remove "Beschrijving ", which comes from the first inline tab.
  $teaser = preg_replace('/^Beschrijving /s', '', $teaser);
  $element = $dom->createElementNS($ns_dcterms, 'dcterms:abstract');
  $element->appendChild($dom->createCDATASection($teaser));
  $owmsmantel->appendChild($element);

  // Create scmeta.
  $overheidproduct = $dom->createElement('scmeta');
  $meta->appendChild($overheidproduct);

  $element = $dom->createElement('productID', $node->nid);
  $overheidproduct->appendChild($element);

  $element = $dom->createElement('onlineAanvragen', 'nee');
  $overheidproduct->appendChild($element);

  if (isset($node->field_product_upl) && !empty($node->field_product_upl[LANGUAGE_NONE][0])) {
    $field_product_upl = $node->field_product_upl[LANGUAGE_NONE][0];

    $element = $dom->createElement('uniformeProductnaam', $field_product_upl['title']);
    $element->setAttribute('scheme', 'overheid:UniformeProductnaam');
    $element->setAttribute('resourceIdentifier', $field_product_upl['url']);
    $overheidproduct->appendChild($element);
  }

  $xml = $dom->saveXML($product);
  db_merge('scfeed_item')
    ->key(array('nid'), array($node->nid))
    ->fields(array('xml' => $xml))
    ->execute();
}

/**
 * Generate body text for node.
 *
 * @param object $node
 *    Node object.
 *
 * @return string
 *    Body text.
 */
function scfeed_generate_body($node) {
  $view_mode  = 'full';
  if (!isset($langcode)) {
    $langcode = $GLOBALS['language_content']->language;
  }
  field_attach_prepare_view('node', array($node->nid => $node), $view_mode, $langcode);
  entity_prepare_view('node', array($node->nid => $node), $langcode);
  $content = field_attach_view('node', $node, $view_mode, $langcode);
  $body = drupal_render($content);
  if (!empty($body)) {
    $body = preg_replace('/(\\<h[1-6]\\>)\\*\\*/si', '\\1', $body);
    $body = filter_xss($body, explode(',', 'p,strong,em,a,h1,h2,h3,h4,h5,h6,ul,ol,li,table,thead,td,tr,th,tbody,abbr'));
  }

  return $body;
}
