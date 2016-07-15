<?php
/**
 * @file
 * wim_agenda.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function wim_agenda_taxonomy_default_vocabularies() {
  return array(
    'announcement' => array(
      'name' => 'Announcement',
      'machine_name' => 'announcement',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
