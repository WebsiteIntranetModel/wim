<?php

/**
 * Plugin that adds an additional facet item to active items.
 */

class ExternalCrawlerInternalFilter extends FacetapiFilter {

  /**
   * {@inheritdoc}
   */
  public function execute(array $build) {
    $types = $this->adapter->getTypes();
    if (in_array('external_crawler', $types)) {
      unset($types['external_crawler']);
      unset($build['external_crawler']);
    }
    if (!empty($types)) {
      $active = reset($build)['#active'];
      $path = reset($build)['#path'];
      $query = reset($build)['#query'];
      $internal = [
        '#markup' => t('Internal'),
        '#path' => $path,
        '#html' => FALSE,
        '#indexed_value' => reset($types),
        '#count' => 0,
        '#active' => $active,
        '#item_parents' => [],
        '#item_children' => [],
        '#query' => $query,
      ];
      foreach ($types as $type) {
        if (isset($build[$type])) {
          $internal['#count'] += $build[$type]['#count'];
          $internal['#item_children'] = array_merge($internal['#item_children'], $build[$type]['#item_children']);
          if (!$active) {
            if (!empty($internal['#query']['f'])) {
              if (!in_array('entity_type:' . $type, $internal['#query']['f'])) {
                $internal['#query']['f'][] = 'entity_type:' . $type;
              }
            }
            else {
              $internal['#query']['f'][] = 'entity_type:' . $type;
            }
          }
          else {
            if (isset($internal['#query']['f'])) {
              $key = array_search('entity_type:' . $type, $internal['#query']['f']);
              unset($internal['#query']['f'][$key]);
            }
          }
          unset($build[$type]);
        }
      }
    }

    if (empty($internal['#query']['f'])) {
      unset($internal['#query']['f']);
    }

    if (!empty($internal)) {
      $build[] = $internal;
      return $build;
    }
    else {
      return array_filter($build, 'facetapi_filter_active');
    }
  }

}
