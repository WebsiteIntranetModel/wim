<?php
module_load_include('inc', 'external_crawler');

function _xml_crawler_get_xml_types($type = NULL) {
  $xml_types = array(
    'cvdr' => 'CVDR',
    'gvop' => 'GVOP',
    'durp' => 'DURP',
  );
  return $type ? $xml_types[$type] : $xml_types;
}

function _xml_crawler_crawle_xml($site) {
  $response = drupal_http_request($site->url);
  if ($response->code === '200') {
    $dom = new DOMDocument();
    $dom->loadXML($response->data);
    $xpath = new DOMXpath($dom);

    // Process CVDR.
    if ($site->xml_type === 'cvdr') {
      foreach ($dom->getElementsByTagName('gzd') as $record) {
        $page_url = $record->getElementsByTagName('publicatieurl_xhtml')->item(0)->nodeValue;
        if (valid_url($page_url)) {
          _external_crawler_index_page($page_url, $site);
        }
      }
    }

    // Process GVOP.
    if ($site->xml_type === 'gvop') {
      foreach ($dom->getElementsByTagName('gzd') as $record) {
        $page_url = $xpath->query('.//dcterms:identifier', $record)->item(0)->nodeValue;
        if (valid_url($page_url)) {
          _external_crawler_index_page($page_url, $site);
        }
      }

    }
  }
}