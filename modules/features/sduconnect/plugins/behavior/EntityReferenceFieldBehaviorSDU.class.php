<?php
/**
 * @file
 * Custom behaviour handler for SDU Connect.
 */

/**
 * Custom behaviors for a Entity Reference field with SDU id.
 *
 * Implementations that wish to provide an implementation of this should
 * register it using CTools' plugin system.
 */
class EntityReferenceFieldBehaviorSDU extends EntityReference_BehaviorHandler_Abstract {

  /**
   * Implements EntityReference_BehaviorHandler_Abstract::schema_alter().
   *
   * This method gets called from entityreference_field_schema() which
   * is a hook_field_schema() implementation.
   *
   * First of all we need to modify the default entityreference field schema
   * that accepts only integer values to prepare it for our varchar ids.
   */
  public function schema_alter(&$schema, $field) { // @codingStandardsIgnoreLine
    $schema['columns']['target_id']['type'] = 'varchar';
    $schema['columns']['target_id']['length'] = 255;
    $schema['columns']['target_id']['default'] = '';
    // Varchar cannot be unsigned so we unset this.
    unset($schema['columns']['target_id']['unsigned']);
  }

  /**
   * Act on loading entity reference fields of entities.
   *
   * @see hook_field_load()
   */
  public function load($entity_type, $entities, $field, $instances, $langcode, &$items) {
    foreach ($entities as $entity) {
      foreach ($items[$entity->nid] as $key => $item) {
        // Skip db call if item is not from sduconnect.
        if (strpos($item['target_id'], SDUCONNECT_FAQ) !== FALSE || strpos($item['target_id'], SDUCONNECT_PRODUCT) !== FALSE) {
          $items[$entity->nid][$key]['target_id'] = sduconnect_get_nid_by_id($item['target_id']);
        }
        else {
          $items[$entity->nid][$key]['target_id'] = $item['target_id'];
        }
      }
    }
  }

  /**
   * Implements EntityReference_BehaviorHandler_Abstract::insert().
   *
   * This method gets called from entityreference_field_insert() which
   * is a hook_field_insert() implementation.
   */
  public function insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
    $this->transformItems($items);
  }

  /**
   * Implements EntityReference_BehaviorHandler_Abstract::update().
   *
   * This is the same as the previous method only that this gets called on
   * field update.
   */
  public function update($entity_type, $entity, $field, $instance, $langcode, &$items) {
    $this->transformItems($items);
  }

  /**
   * Generate a settings form for this handler.
   */
  public function settingsForm($field, $instance) {

    return [];
  }

  /**
   * Helper function: Transform field items from nid to field_id values.
   */
  protected function transformItems(&$items) {
    foreach ($items as $key => &$item) {
      $item['target_id'] = sduconnect_get_id_by_nid($item['target_id']);
    }
  }

}
