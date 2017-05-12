<?php
/**
 * @file
 * Implementation XML Crawler.
 */

module_load_include('inc', 'external_crawler');

/**
 * XML types which we support.
 */
function _xml_crawler_get_xml_types($type = NULL) {
  $xml_types = array(
    'cvdr' => 'CVDR',
    'gvop' => 'GVOP',
    'durp' => 'DURP',
  );

  if ($new_types = module_invoke_all('xml_crawler_xml_types')) {
    $xml_types = array_merge($xml_types, $new_types);
  }

  return $type ? $xml_types[$type] : $xml_types;
}

/**
 * Crawling XML page.
 *
 * @param \stdClass $site
 *    Site object.
 */
function _xml_crawler_crawle_xml(stdClass $site) {
  $pages = array();

  // Replace tokens.
  $url = token_replace($site->url);

  $response = drupal_http_request($url);
  if ($response->code === '200') {
    $dom = new DOMDocument();
    $dom->loadXML($response->data);

    // Get pages from CVDR.
    if ($site->xml_type === 'cvdr') {
      $pages = _xml_crawler_cvdr_get_pages($dom);
    }

    // Get pages from GVOP.
    if ($site->xml_type === 'gvop') {
      $pages = _xml_crawler_gvop_get_pages($dom);
    }

    // Get pages from DURP.
    if ($site->xml_type === 'durp') {
      $pages = _xml_crawler_durp_get_pages($dom);
    }

    // Allow other modules alter pages before they will be indexed.
    drupal_alter('xml_crawler_pages', $pages, $dom, $site);
    // Crawle pages.
    foreach ($pages as $page_url) {
      _external_crawler_index_page($page_url, $site);
    }
  }
}

/**
 * Get pages from the DURP dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_durp_get_pages(DOMDocument $dom) {
  $base_url = NULL;
  $pages = array();
  $xml_pages = array();

  foreach ($dom->getElementsByTagName('Dossier') as $record) {
    // Get detailed XMLs.
    foreach ($record->getElementsByTagName('Plan') as $sub_record) {
      $xml_pages[] = $sub_record->getElementsByTagName('GeleideFormulier')->item(0)->nodeValue;
    }
  }

  // Parse detailed XMLs.
  foreach ($xml_pages as $xml_page_url) {
    $response = drupal_http_request($xml_page_url);

    if ($response->code === '200') {
      $sub_xml_dom = new DOMDocument();
      $sub_xml_dom->loadXML($response->data);

      foreach ($sub_xml_dom->getElementsByTagName('Plan') as $sub_xml_record) {
        // Get basic page URL.
        $base_url = $sub_xml_record->getElementsByTagName('Onderdelen')->item(0)->getAttribute('BasisURL');
        $sub_pages = array();
        if ($base_url) {
          // Find all subpages.
          foreach ($sub_xml_record->getElementsByTagName('Toelichting') as $sub_record) {
            if (_xml_crawler_is_page_url($sub_record->nodeValue)) {
              $sub_pages[] = $sub_record->nodeValue;
            }
          }

          // Crawle subpages.
          foreach ($sub_pages as $sub_page_url) {
            // Build url based on base url and subpage url.
            $crawle_page_url = $base_url . $sub_page_url;
            $crawle_page_url = _external_crawler_prepare_url($crawle_page_url);
            if (valid_url($crawle_page_url)) {
              $pages[] = $crawle_page_url;
            }
          }
        }
      }
    }
  }

  return $pages;
}

/**
 * Get pages from the GCOP dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_gvop_get_pages(DOMDocument $dom) {
  $xpath = new DOMXpath($dom);
  $pages = array();

  foreach ($dom->getElementsByTagName('gzd') as $record) {
    // Using xpath to find child element.
    $page_url = $xpath->query('.//dcterms:identifier', $record)->item(0)->nodeValue;
    $page_url = _external_crawler_prepare_url($page_url);
    if (valid_url($page_url)) {
      $pages[] = $page_url;
    }
  }

  return $pages;
}

/**
 * Get pages from the CVDR dom.
 *
 * @param \DOMDocument $dom
 *    CVDR DOMDocument.
 *
 * @return array $pages
 *    Pages urls.
 */
function _xml_crawler_cvdr_get_pages(DOMDocument $dom) {
  $pages = array();

  foreach ($dom->getElementsByTagName('gzd') as $record) {
    $page_url = $record->getElementsByTagName('publicatieurl_xhtml')->item(0)->nodeValue;
    $page_url = _external_crawler_prepare_url($page_url);
    if (valid_url($page_url)) {
      $pages[] = $page_url;
    }
  }

  return $pages;
}

/**
 * Check if given URL is URL to HTML page.
 */
function _xml_crawler_is_page_url($url) {
  $url = strtolower($url);
  $is_page_url = FALSE;
  if (stripos($url, '.html') !== FALSE) {
    $is_page_url = TRUE;
  }

  return $is_page_url;
}

/**
 * Return xml site type.
 */
function _xml_crawler_get_xml_type($entity_id) {
  $cid = 'xml_crawler_site_type:' . $entity_id;

  $data = &drupal_static(__FUNCTION__);
  if (!isset($data)) {
    if ($cache = cache_get($cid)) {
      $data = $cache->data;
    }
    else {
      $site = _external_crawler_fetch_sites($entity_id);
      $data = isset($site->xml_type) ? $site->xml_type : NULL;

      cache_set($cid, $data);
    }
  }
  return $data;
}
