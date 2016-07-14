<?php
/**
 * @file
 * Implementation of migrate api and WIMMigration class.
 */

/**
 * Implements hook_migrate_api().
 */
function wim_fixtures_migrate_api() {
  $data_sources = DRUPAL_ROOT . '/' .
    drupal_get_path('module', 'wim_fixtures') . '/data_sources/files';
  $api = array(
    'api' => 2,
    'groups' => array(
      'WIMMigrate' => array(
        'title' => t('WIM Fixtures'),
      ),
    ),
    'migrations' => array(
      'WIM_User' => array(
        'class_name' => 'WIMUsers',
        'group_name' => 'WIMMigrate',
      ),
      'WIM_File' => array(
        'class_name' => 'WIMFile',
        'group_name' => 'WIMMigrate',
        'default_uid' => 1,
        'source_dir' => $data_sources,
        'destination_dir' => 'public://fixtures',
      ),
      'WIM_Term_Tags' => array(
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'tags',
        'file_name' => 'tag-terms.csv',
      ),
      'WIM_Term_Categories' => array(
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'news_categories',
        'file_name' => 'news-category-terms.csv',
      ),
      'WIM_Faq_Categories' => array(
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'faq_categories',
        'file_name' => 'faq-category-terms.csv',
      ),
      'WIM_Basic_Page' => array(
        'class_name' => 'BasicPageMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'page',
        'file_name' => 'basic-page.csv',
        'dependencies' => array(
          'WIM_User',
        ),
      ),
      'WIM_Product' => array(
        'class_name' => 'BasicPageMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'product',
        'file_name' => 'product.csv',
        'dependencies' => array(
          'WIM_User',
        ),
      ),
      'WIM_News' => array(
        'class_name' => 'NewsMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'news',
        'file_name' => 'news.csv',
        'dependencies' => array(
          'WIM_Term_Categories',
          'WIM_Term_Tags',
          'WIM_User',
        ),
      ),
      'WIM_Faq' => array(
        'class_name' => 'FaqMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'faq',
        'file_name' => 'faq.csv',
        'dependencies' => array(
          'WIM_Faq_Categories',
          'WIM_Term_Tags',
          'WIM_User',
        ),
      ),
      'WIM_Agenda' => array(
        'class_name' => 'AgendaMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'agenda',
        'file_name' => 'agenda.csv',
        'dependencies' => array(
          'WIM_File',
          'WIM_User',
        ),
      ),
    ),
  );

  return $api;
}

/**
 * Migration classes for migrating users and profiles.
 */

/**
 * Abstract class as a base for all our migration classes.
 */
abstract class WIMMigration extends Migration {

  public $dataSources = '';

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);
    // Avoid known line ending issue: "Invalid data value".
    // drupal.org/node/1152158#InvalidDataValue.
    ini_set('auto_detect_line_endings', TRUE);
    $this->dataSources = DRUPAL_ROOT . '/' .
      drupal_get_path('module', 'wim_fixtures') . '/data_sources/';

  }

}
