<?php
/**
 * @file
 * Implementation of Dom Crawler.
 */

use Symfony\Component\DomCrawler\Crawler;
use Symfony\Component\DomCrawler\Link;
use Symfony\Component\CssSelector\CssSelectorConverter;

/**
 * Build Solr document.
 */
function external_crawler_build_document($pagekey, $url, $title, $body, $site_id) {
  module_load_include('inc', 'apachesolr', 'apachesolr.index');

  $document = new ApacheSolrDocument();
  $document->id = apachesolr_document_id($pagekey, 'external_crawler');
  $document->site = url(NULL, ['absolute' => TRUE]);
  $document->hash = apachesolr_site_hash();
  $document->entity_id = $site_id;
  $document->entity_type = EXTERNAL_CRAWLER_ENTITY_TYPE;
  $document->language = LANGUAGE_NONE;
  $document->url = $url;

  $document->addField('label', $title);
  $document->addField('content', _external_crawler_clear_body($body));

  $document->addField('domain_id', 1);
  $document->addField('domain_site', 1);

  // Allow other modules to alter the document.
  $context = ['pagekey' => $pagekey, 'site_id' => $site_id];
  drupal_alter('external_crawler_document', $document, $context);

  return $document;
}

/**
 * DOMCrawler doesn't have a exclude function yet.
 *
 * Find more information here https://github.com/symfony/symfony/pull/9157.
 */
function _external_crawler_domcrawler_exclude(Crawler $crawler, $excludeSelectors) {
  $document = new \DOMDocument('1.0', 'UTF-8');
  $root = $document->appendChild($document->createElement('_root'));
  $crawler->rewind();
  $root->appendChild($document->importNode($crawler->current(), TRUE));
  $domxpath = new \DOMXPath($document);
  $cssSelectorConverter = new CssSelectorConverter();

  foreach ($excludeSelectors as $selector) {
    $crawlerInverse = $domxpath->query($cssSelectorConverter->toXPath($selector));
    foreach ($crawlerInverse as $elementToRemove) {
      $parent = $elementToRemove->parentNode;
      $parent->removeChild($elementToRemove);
    }
  }
  $crawler->clear();
  $crawler->add($document);
}

/**
 * Find links in the crawler and add them to the external_crawler_page table.
 */
function _external_crawler_index_page_crawl($site, $pagedata, Crawler $nodeCrawler, $from_url) {
  // Retrieve links for indexing and adding to page table.
  $new_depth = $pagedata['depth'] + 1;
  if ($new_depth <= $site->max_depth) {
    $linkNodes = $nodeCrawler->filter('a');
    foreach ($linkNodes as $linkNode) {
      // Link already creates absolute links for us.
      $link = new Link($linkNode, $from_url);

      // Only start crawling the page if it's from current domain.
      $link_data = parse_url($link->getUri());
      $url_data = parse_url($from_url);

      $is_excluded = drupal_match_path($link->getUri(), $site->url_exclude);

      if ((isset($link_data['host']) && $link_data['host'] == $url_data['host'] && !$is_excluded) || (isset($site->is_xml) && $site->is_xml)) {
        $new_pagedata = _external_crawler_get_pagedata(
          _external_crawler_generate_pagekey($site, $link->getUri()),
          [
            'site_id' => $site->site_id,
            'url' => $link->getUri(),
            'title' => trim(strip_tags($linkNode->nodeValue)),
            'depth' => $new_depth,
          ]
        );

        db_merge('external_crawler_page')
          ->key(['pagekey' => $new_pagedata['pagekey']])
          ->fields($new_pagedata)
          ->execute();
      }
    };
  }
}

/**
 * Fetch page and update Solr index.
 */
function _external_crawler_index_page($url, stdClass $site) {
  if (module_exists('apachesolr_attachments')) {
    module_load_include('inc', 'apachesolr_attachments', 'apachesolr_attachments.index');
  }

  // Load required libaries.
  external_crawler_load_vendor();

  // Prepare URL.
  $url = _external_crawler_prepare_url($url);
  // Define a pagekey for use in the db.
  $pagekey = _external_crawler_generate_pagekey($site, $url);
  $pagedata = _external_crawler_get_pagedata($pagekey, [
    'url' => $url,
    'site_id' => $site->site_id,
  ]);

  // Retrieve the page.
  $result = drupal_http_request($url, ['max_redirects' => 2]);

  if ($result->code == 200 && $result->data) {
    // Setup basic document.
    $document = [];
    $document['url'] = $url;
    $document['title'] = $pagedata['title'];
    $document['body'] = '';

    // Get mime type from the returned Content-Type header.
    $content_type_parts = explode('; ', $result->headers['content-type']);
    $content_type_mime = $content_type_parts[0];

    // Get mime type from the extension in the url.
    $ext_parts = explode('.', $url);
    $ext = $ext_parts[count($ext_parts) - 1];
    include_once DRUPAL_ROOT . '/includes/file.mimetypes.inc';
    $ext_mapping = file_mimetype_mapping();
    $ext_mime = isset($ext_mapping['extensions'][$ext]) ? $ext_mapping['mimetypes'][$ext_mapping['extensions'][$ext]] : '';

    if (strlen($result->data) > 26214400) {
      // Skip this URL. Content is > 25MB.
      // Indexation can lead to memory exhaustion.
      return;
    }

    if ($content_type_mime == 'text/html') {
      _external_crawler_index_page_html($site, $result, $document, $pagedata, $url);
    }
    else if (module_exists('apachesolr_attachments') && (apachesolr_attachments_allowed_mime($content_type_mime) || apachesolr_attachments_allowed_mime($ext_mime)) && variable_get('apachesolr_attachments_entity_bundle_indexing_document', 'none') !== 'none') {
      _external_crawler_index_page_document($site, $result, $document, $pagedata, $url);
    }

    if (empty($document['title'])) {
      // No title was provided. Generate a title from the URL.
      $string = explode('/', $url);
      $string_array = array_reverse($string);
      $document['title'] = urldecode(reset($string_array));
    }

    // Set latest crawl data.
    $pagedata['date'] = time();

    // Allow other modules to interact.
    module_invoke_all('external_crawler_index', $site, $result, $pagedata, $document);

    // Add to solr.
    external_crawler_save_page($pagedata, $document);
  }
  else {
    if ($result->code == 404) {
      // Page not found. Delete from solr index and page table.
      external_crawler_delete_page($pagekey);
    }
    else {
      watchdog('external_crawler', 'There was an error crawling !pagekey.<pre>@data</pre>', [
        '!pagekey' => $pagekey,
        '@data' => print_r($result, TRUE),
      ], WATCHDOG_ERROR);
    }
  }
}

/**
 * Index page HTML.
 */
function _external_crawler_index_page_html($site, $result, &$document, &$pagedata, $url) {
  $crawler = new Crawler($result->data);

  $base_url = $url;
  foreach ($crawler->filter('base') as $element) {
    if ($href = $element->getAttribute('href')) {
      $base_url = $href;
    }
  }

  if ($site->content_include) {
    $included = $crawler->filter($site->content_include)
      ->each(function (Crawler $nodeCrawler, $i) {
        return $nodeCrawler;
      });
  }
  else {
    $included = [$crawler];
  }

  // Set the page title.
  if ($crawler->filterXpath('//title')->count()) {
    $document['title'] = $crawler->filterXpath('//title')->text();
  }
  else {
    $document['title'] = NULL;
  }

  foreach ($included as $nodeCrawler) {
    if ($site->content_exclude) {
      // Remove from excluded.
      _external_crawler_domcrawler_exclude($nodeCrawler, explode(',', $site->content_exclude));
    }

    // Add HTML for the index.
    $document['body'] .= $nodeCrawler->html();

    // Crawl for new pages.
    _external_crawler_index_page_crawl($site, $pagedata, $nodeCrawler, $base_url);
  }

}

/**
 * Index page document.
 */
function _external_crawler_index_page_document($site, $result, &$document, &$pagedata, $url) {
  $filepath = file_unmanaged_save_data($result->data);

  if (variable_get('apachesolr_attachments_extract_using', 'tika') == 'tika') {
    $text = apachesolr_attachments_extract_using_tika($filepath);
  }
  else {
    // Extract using Solr.
    try {
      list($text, $metadata) = apachesolr_attachments_extract_using_solr($filepath);
    }
    catch (Exception $e) {
      // Exceptions from Solr may be transient,
      // or indicate a problem with a specific file.
      watchdog('Apache Solr Attachments', "Exception occurred sending %filepath to Solr\n!message", [
        '%filepath' => $filepath,
        '!message' => nl2br(check_plain($e->getMessage())),
      ], WATCHDOG_ERROR);
      return FALSE;
    }
  }

  if (isset($text)) {
    $document['body'] .= $text;
  }
}

/**
 * Prepare URL for request.
 */
function _external_crawler_prepare_url($url) {
  $url = trim($url);
  $url = str_replace(' ', '%20', $url);

  return $url;
}
