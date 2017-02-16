<?php

/**
 * @file
 * Mapping of XML to node content.
 */

/**
 * Populate node object with PDC content.
 *
 * @param DOMXPath $xpath
 *   Xpath object.
 * @param object $node
 *   Node object.
 * @param bool $private
 *   Private flag.
 *
 * @throws \Exception
 */
function sduconnect_set_pdc_content(DOMXPath $xpath, &$node, $private = FALSE) {
  $formats = filter_formats();
  $default_format = reset($formats);

  $xpath->registerNameSpace('m', 'http://www.sduconnect.nl/Productoverzicht');
  $xpath->registerNameSpace('dcterms', 'http://purl.org/dc/terms/');
  $xpath->registerNameSpace('overheid', 'http://standaarden.overheid.nl/owms/terms/');
  $xpath->registerNameSpace('overheidproduct', 'http://standaarden.overheid.nl/product/terms/');
  $xpath->registerNameSpace('overheidsc', 'http://standaarden.overheid.nl/sc/terms/');

  $node->type = 'product';
  // Title.
  $node->title = (string) $xpath->query('//m:page/m:product/m:name')
    ->item(0)->nodeValue;

  // Created.
  $created = strtotime(sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/m:created')));
  if ($created > 0) {
    $node->created = $created;
  }

  // Changed.
  $changed = strtotime(sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/m:updated')));
  if ($changed > 0) {
    $node->changed = $changed;
  }

  // Language.
  $language = (string) $xpath->query('//m:page/m:product/m:language')
    ->item(0)->nodeValue;
  if ($language) {
    $node->language = strtolower(trim($language));
  }

  // Body.
  $body = sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/m:description'));

  $node->body = array(
    LANGUAGE_NONE => array(
      array(
        'value' => $body,
        'format' => $default_format->format,
      ),
    ),
  );

  // Related Product items.
  $items = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:product_relaties/m:product_relatie/@base_id'));
  if ($items) {
    $node->field_related_product = array(LANGUAGE_NONE => array());
    foreach ($items as $item) {
      $node->field_related_product[LANGUAGE_NONE][] = array('target_id' => SDUCONNECT_PRODUCT . '-' . trim($item));
    }
  }
  elseif (empty($items) && !empty($node->field_related_product)) {
    unset($node->field_related_product);
    $node->field_related_product = array();
  }

  // Related FAQ items.
  $items = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:vac_relaties/m:vac_relatie/@base_id'));
  if ($items) {
    $node->field_related_faq = array(LANGUAGE_NONE => array());
    foreach ($items as $item) {
      $node->field_related_faq[LANGUAGE_NONE][] = array('target_id' => SDUCONNECT_FAQ . '-' . trim($item));
    }
  }
  elseif (empty($items) && !empty($node->field_related_faq)) {
    unset($node->field_related_faq);
    $node->field_related_faq = array();
  }

  // More info.
  $names = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:product_links/m:product_link/m:product_link_name'));
  $urls = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:product_links/m:product_link/m:product_link_url'));
  $items = array();
  foreach ($names as $i => $name) {
    $items[] = array(
      'url' => $urls[$i],
      'title' => $name,
    );
  }
  if ($items) {
    $node->field_product_more_information = array(LANGUAGE_NONE => $items);
  }
  elseif (empty($items) && !empty($node->field_product_more_information)) {
    unset($node->field_product_more_information);
    $node->field_product_more_information = array();
  }

  // Related laws.
  $names = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:law_rules/m:law_rule/m:law_rule_name'));
  $urls = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:law_rules/m:law_rule/m:url'));
  $items = array();
  foreach ($names as $i => $name) {
    $items[] = array(
      'url' => $urls[$i],
      'title' => $name,
    );
  }
  if ($items) {
    $node->field_product_related_laws = array(LANGUAGE_NONE => $items);
  }
  elseif (empty($items) && !empty($node->field_product_related_laws)) {
    unset($node->field_product_related_laws);
    $node->field_product_related_laws = array();
  }

  // Forms.
  $names = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:formulieren_extern/m:formulier/m:label'));
  $urls = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:formulieren_extern/m:formulier/m:href'));
  $items = array();
  foreach ($names as $i => $name) {
    $items[] = array(
      'url' => $urls[$i],
      'title' => $name,
    );
  }
  if ($items) {
    $node->field_product_forms = array(LANGUAGE_NONE => $items);
  }
  elseif (empty($items) && !empty($node->field_product_forms)) {
    unset($node->field_product_forms);
    $node->field_product_forms = array();
  }

  // Helper array to map xml tags to fields in node.
  $mapping = array(
    '//m:page/m:product/m:uitvoerende_instanties/m:instantie/m:opmerkingen' => 'field_product_locations',
    '//m:page/m:product/m:contact' => 'field_product_contact',
    '//m:page/m:product/m:appeal' => 'field_product_objection',
    '//m:page/m:product/m:costs' => 'field_product_costs',
    '//m:page/m:product/m:procedure' => 'field_product_procedure',
    '//m:page/m:product/m:period' => 'field_product_period',
    '//m:page/m:product/m:conditions' => 'field_product_conditions',
    '//m:page/m:product/m:notice' => 'field_product_attention',
    // @codingStandardsIgnoreStart
    // '//m:page/m:product/m:subsidies' => 'field_product_subsidies',
    // '//m:page/m:product/m:subsidies_budget' => 'field_product_subsidies_budget',
    // '//m:page/m:product/m:subsidies_maximale_bijdrage' => 'field_product_subsidies_maximale_bijdrage',
    // @codingStandardsIgnoreEnd
  );

  // Here we set mapped fields.
  foreach ($mapping as $query => $field_name) {
    $field = sduconnect_nodelist_to_string($xpath->query($query));
    if (!empty($field)) {
      // Gives opportunity alter content before save.
      drupal_alter('sduconnect_prepare_content', $field, $field_name);
      $node->$field_name = array(
        LANGUAGE_NONE => array(
          array(
            'value' => $field,
            'format' => $default_format->format,
          ),
        ),
      );
    }
    elseif (strlen($field) == 0 && !empty($node->$field_name)) {
      unset($node->$field_name);
      $node->$field_name = array();
    }
  }

  // Request online.
  $url = sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/overheidproduct:scproduct/overheidproduct:meta/overheidproduct:scmeta/overheidproduct:aanvraagURL/@resourceIdentifier'));
  $items = array();
  if ($url) {
    $items[] = array(
      'href' => $url,
      'title' => 'Online aanvragen',
    );
  }
  if ($items) {
    $node->field_product_request = array(
      LANGUAGE_NONE => array(
        array(
          'value' => theme('links', array('links' => $items)),
          'format' => $default_format->format,
        ),
      ),
    );
  }
  elseif (empty($items) && !empty($node->field_product_request)) {
    unset($node->field_product_request);
    $node->field_product_request = array();
  }

  // Tags.
  $a = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:doelgroepen/m:doelgroep'));
  $b = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:themes/m:theme/m:main/m:name'));
  $c = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:themes/m:theme/m:subthemes/m:subtheme/m:name'));
  $d = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:vind_themes/m:vind_theme/m:name'));
  $e = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/overheidproduct:scproduct/overheidproduct:meta/overheidproduct:owmsmantel/dcterms:subject'));
  $tags = array_unique(array_merge($a, $b, $c, $d, $e));
  $items = sduconnect_tags($tags);
  $node->field_tags = array(LANGUAGE_NONE => $items);

  // Samenwerkende Catalogi.
  $categories = sduconnect_nodelist_to_array($xpath->query('//m:page/m:product/m:doelgroepen/m:doelgroep'));
  $items = array();
  foreach ($categories as $category) {
    if ($category === 'organisatie/ondernemer') {
      $category = 'ondernemer';
    }
    $items[] = array(
      'value' => $category,
    );
  }
  $node->field_sc_audience = array(LANGUAGE_NONE => $items); // @codingStandardsIgnoreLine

  // Start- and end date.
  $start = sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/m:subsidies_startdate'));
  if ($start) {
    $start = implode('-', array_reverse(explode('-', $start))) . ' 00:00:00';
  }
  $end = sduconnect_nodelist_to_string($xpath->query('//m:page/m:product/m:subsidies_enddate'));
  if ($end) {
    $end = implode('-', array_reverse(explode('-', $end))) . ' 00:00:00';
  }
  $items = array();
  if ($start) {
    $items[] = array(
      'value' => $start,
      'value2' => $end,
      'timezone' => variable_get('date_default_timezone', 'Europe/Amsterdam'),
      'timezone_db' => 'UTC',
      'date_type' => 'datetime',
    );
  }
  // $node->field_date = array(LANGUAGE_NONE => $items); // @codingStandardsIgnoreLine

  // Publication date.
  $date[] = array(
    'value' => date('Y-m-d H:i:s', $created),
    'value2' => '',
    'timezone' => variable_get('date_default_timezone'),
    'timezone_db' => 'UTC',
    'date_type' => 'datetime',
  );

  $node->field_publication_date = array(LANGUAGE_NONE => $date);
}

/**
 * Populate node object with VAC content.
 *
 * @param object $xpath
 *   Xpath object.
 * @param object $node
 *   Node.
 * @param bool $private
 *   Import private fields.
 */
function sduconnect_set_vac_content($xpath, &$node, $private = FALSE) {
  $formats = filter_formats();
  $default_format = reset($formats);

  $xpath->registerNameSpace('vac', 'http://standaarden.overheid.nl/vac/');
  $xpath->registerNameSpace('dcterms', 'http://purl.org/dc/terms/');
  $xpath->registerNameSpace('overheid', 'http://standaarden.overheid.nl/owms/terms/');
  $xpath->registerNameSpace('overheidvac', 'http://standaarden.overheid.nl/vac/terms/');

  $node->type = 'faq';
  // Title.
  $node->title = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:vraag'));

  // Body.
  $body = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:antwoord/vac:antwoordTekst'));
  $body .= sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:antwoord/vac:antwoordProductVeld'));
  if ($private) {
    $body .= sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:onderwaterantwoord/vac:onderwaterantwoordTekst'));
    $body .= sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:onderwaterantwoord/vac:onderwaterantwoordProductVeld'));
  }

  $node->body = array(
    LANGUAGE_NONE => array(
      array(
        'value' => $body,
        'format' => $default_format->format,
      ),
    ),
  );

  // Created.
  $created = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:meta/vac:owmsmantel/dcterms:available/start'));
  $node->created = strtotime($created);

  // Changed.
  $changed = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:meta/vac:owmskern/dcterms:modified'));
  $node->changed = strtotime($changed);

  // Language.
  $language = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:meta/vac:owmskern/dcterms:language'));
  if ($language) {
    $parts = explode('-', $language);
    $node->language = trim($parts[0]);
  }

  // Explanation.
  $value = sduconnect_nodelist_to_string($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:toelichting'));
  $items = array();
  if (preg_match('/[a-z0-9]/si', strip_tags($value))) {
    $items[] = array(
      'value' => $value,
      'format' => $default_format->format,
    );
    $node->field_faq_additional_information = array(LANGUAGE_NONE => $items);
  }

  // Tags.
  $a = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:meta/vac:owmsmantel/dcterms:audience'));
  $b = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:meta/vac:vacmeta/vac:trefwoord'));
  $tags = array_unique(array_merge($a, $b));
  $items = sduconnect_tags($tags);
  $node->field_tags = array(LANGUAGE_NONE => $items);

  // More information.
  $names = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:verwijzingOverigeInfo'));
  $urls = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:body/vac:kanaal/vac:verwijzingOverigeInfo/@resourceIdentifier'));
  $items = array();
  foreach ($names as $i => $name) {
    $items[] = array(
      'url' => $urls[$i],
      'title' => $name,
    );
  }

  if ($items) {
    $node->field_faq_more_information = array(LANGUAGE_NONE => $items);
  }

  // Related Product items.
  $items = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:body/vac:verwijzingProduct/@resourceIdentifier'));
  if ($items) {
    $node->field_related_product = array(LANGUAGE_NONE => array());
    foreach ($items as $item) {
      $node->field_related_product[LANGUAGE_NONE][] = array('target_id' => SDUCONNECT_PRODUCT . '-' . trim($item));
    }
  }

  // Related FAQ items.
  $items = sduconnect_nodelist_to_array($xpath->query('//vac:vacs/vac:vac/vac:body/vac:verwijzingVac/@resourceIdentifier'));
  if ($items) {
    $node->field_related_faq = array(LANGUAGE_NONE => array());
    foreach ($items as $item) {
      $node->field_related_faq[LANGUAGE_NONE][] = array('target_id' => SDUCONNECT_FAQ . '-' . trim($item));
    }
  }

  // This should be disabled for new items.
  if (!isset($node->nid)) {
    $node->field_show_on_overview[LANGUAGE_NONE][] = array('value' => 0);
  }
}

/**
 * Convert DOMXML node list to string.
 *
 * @param object $node_list
 *   List of nodes.
 *
 * @return string
 *   Trimmed string value.
 */
function sduconnect_nodelist_to_string($node_list) {
  if ($node_list->length) {
    return trim($node_list->item(0)->nodeValue);
  }
  return '';
}

/**
 * Convert DOMXML node list to array.
 *
 * @param object $node_list
 *   List of nodes.
 *
 * @return array
 *   Array of values.
 */
function sduconnect_nodelist_to_array($node_list) {
  $output = array();
  foreach ($node_list as $node) {
    $output[] = $node->nodeValue;
  }
  return $output;
}

/**
 * Get term id's for tags.
 *
 * @param string $names
 *   Term name.
 *
 * @return array
 *   Array of tid's.
 */
function sduconnect_tags($names) {
  $output = array();
  $vocab = 'tags';
  $names = array_filter(array_unique(array_map('trim', $names)));
  foreach ($names as $name) {
    $query = db_select('taxonomy_term_data', 'td')
      ->fields('td', array('tid'))
      ->condition('td.name', $name)
      ->range(0, 1);
    $v = $query->join('taxonomy_vocabulary', 'v', 'td.vid = v.vid');
    $query->condition("$v.machine_name", $vocab);
    $tid = $query->execute()->fetchField();
    if (!$tid) {
      $vid = db_select('taxonomy_vocabulary', 'v')
        ->fields('v', array('vid'))
        ->condition('v.machine_name', $vocab)
        ->execute()
        ->fetchField();
      $term = (object) array(
        'name' => $name,
        'vid' => $vid,
        'vocabulary_machine_name' => $vocab,
      );
      taxonomy_term_save($term);
      $tid = $term->tid;
    }
    $output[] = array(
      'tid' => $tid,
    );
  }
  return $output;
}
