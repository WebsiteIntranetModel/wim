<?php
/**
 * @file
 * Custom selection handler for Atos E-suite.
 */

/**
 * A generic Entity handler.
 *
 * The generic base implementation has a variety of overrides to workaround
 * core's largely deficient entity handling.
 */
class EntityReferenceSelectionHandlerAtos extends EntityReference_SelectionHandler_Generic {

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new EntityReferenceSelectionHandlerAtos($field, $instance, $entity_type, $entity);
  }

  /**
   * Implements EntityReferenceHandler::settingsForm().
   */
  public static function settingsForm($field, $instance) {
    $entity_info = entity_get_info($field['settings']['target_type']);
    // Merge-in default values.
    $field['settings']['handler_settings'] += array(
      'target_bundles' => array(),
      'sort' => array(
        'type' => 'none',
      ),
    );

    if (!empty($entity_info['entity keys']['bundle'])) {
      $bundles = array();
      foreach ($entity_info['bundles'] as $bundle_name => $bundle_info) {
        $bundles[$bundle_name] = $bundle_info['label'];
      }

      $form['target_bundles'] = array(
        '#type' => 'checkboxes',
        '#title' => t('Target bundles'),
        '#options' => $bundles,
        '#default_value' => $field['settings']['handler_settings']['target_bundles'],
        '#size' => 6,
        '#multiple' => TRUE,
        '#description' => t('The bundles of the entity type that can be referenced. Optional, leave empty for all bundles.'),
        '#element_validate' => array('_entityreference_element_validate_filter'),
      );
    }
    else {
      $form['target_bundles'] = array(
        '#type' => 'value',
        '#value' => array(),
      );
    }

    return $form;
  }

  /**
   * Implements EntityReferenceHandler::getReferencableEntities().
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    $options = array();
    $bundles = $this->field['settings']['handler_settings']['target_bundles'];

    $q = db_select('atos_esuite', 'a')->fields('a', array('identifier', 'nid'));
    $q->join('node', 'n', 'n.nid = a.nid');
    $q->fields('n', array('title', 'type'))
      ->condition('n.type', $bundles, 'IN');
    $results = $q->execute()->fetchAllAssoc('nid');

    if (!empty($results)) {
      foreach ($results as $result) {
        $options[$result->type][$result->nid] = check_plain($result->title);
      }
    }

    return $options;
  }

  /**
   * Implements EntityReferenceHandler::countReferencableEntities().
   */
  public function countReferencableEntities($match = NULL, $match_operator = 'CONTAINS') {
    $query = $this->buildEntityFieldQuery($match, $match_operator);
    return $query->count()->execute();
  }

  /**
   * Implements EntityReferenceHandler::validateReferencableEntities().
   */
  public function validateReferencableEntities(array $ids) {
    if ($ids) {
      $bundles = $this->field['settings']['handler_settings']['target_bundles'];

      $q = db_select('atos_esuite', 'a')->fields('a', array(
        'identifier',
        'nid',
      ));
      $q->join('node', 'n', 'n.nid = a.nid');
      $q->condition('n.type', $bundles, 'IN')->condition('a.nid', $ids, 'IN');
      $result = $q->execute()->fetchAllAssoc('nid');

      if (!empty($result)) {
        return array_keys($result);
      }
    }

    return array();
  }

  /**
   * Build an EntityFieldQuery to get referencable entities.
   */
  protected function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', $this->field['settings']['target_type']);
    if (!empty($this->field['settings']['handler_settings']['target_bundles'])) {
      $query->entityCondition('bundle', $this->field['settings']['handler_settings']['target_bundles'], 'IN');
    }
    if (isset($match)) {
      $entity_info = entity_get_info($this->field['settings']['target_type']);
      if (isset($entity_info['entity keys']['label'])) {
        $query->propertyCondition($entity_info['entity keys']['label'], $match, $match_operator);
      }
    }

    // Add a generic entity access tag to the query.
    $query->addTag($this->field['settings']['target_type'] . '_access');
    $query->addTag('entityreference');
    $query->addMetaData('field', $this->field);
    $query->addMetaData('entityreference_selection_handler', $this);

    // Add the sort option.
    if (!empty($this->field['settings']['handler_settings']['sort'])) {
      $sort_settings = $this->field['settings']['handler_settings']['sort'];
      if ($sort_settings['type'] === 'property') {
        $query->propertyOrderBy($sort_settings['property'], $sort_settings['direction']);
      }
      elseif ($sort_settings['type'] === 'field') {
        list($field, $column) = explode(':', $sort_settings['field'], 2);
        $query->fieldOrderBy($field, $column, $sort_settings['direction']);
      }
    }

    return $query;
  }

  /**
   * Implements EntityReferenceHandler::getLabel().
   */
  public function getLabel($entity) {
    $target_type = $this->field['settings']['target_type'];
    return entity_access('view', $target_type, $entity) ? entity_label($target_type, $entity) : t('- Restricted access -');
  }

}
