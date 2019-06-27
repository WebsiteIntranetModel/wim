<?php
/**
 * @file
 * Implementation of migrate api and WIMMigration class.
 */

/**
 * Implements hook_migrate_api().
 */
function wim_fixtures_migrate_api() {
  $data_sources = DRUPAL_ROOT . '/' . drupal_get_path('module', 'wim_fixtures') . '/data_sources/files';
  $api = [
    'api' => 2,
    'groups' => [
      'WIMMigrate' => [
        'title' => t('WIM Fixtures'),
      ],
    ],
    'migrations' => [
      'WIM_User' => [
        'class_name' => 'WIMUsers',
        'group_name' => 'WIMMigrate',
      ],
      'WIM_File' => [
        'class_name' => 'WIMFile',
        'group_name' => 'WIMMigrate',
        'default_uid' => 1,
        'source_dir' => $data_sources,
        'destination_dir' => 'public://fixtures',
      ],
      'WIM_Term_Tags' => [
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'tags',
        'file_name' => 'tag-terms.json',
      ],
      'WIM_Term_Categories' => [
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'news_categories',
        'file_name' => 'news-category-terms.json',
      ],
      'WIM_Faq_Categories' => [
        'class_name' => 'WIMTermMigration',
        'group_name' => 'WIMMigrate',
        'destination_vocabulary' => 'faq_categories',
        'file_name' => 'faq-category-terms.json',
      ],
      'WIM_Basic_Page' => [
        'class_name' => 'BasicPageMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'page',
        'file_name' => 'basic-page.json',
        'dependencies' => [
          'WIM_User',
          'WIM_File',
          'WIM_Term_Tags',
        ],
      ],
      'WIM_Person' => [
        'class_name' => 'PersonMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'person',
        'file_name' => 'person.json',
        'dependencies' => [
          'WIM_User',
          'WIM_File',
          'WIM_Term_Tags',
        ],
      ],
      'WIM_Product' => [
        'class_name' => 'ProductMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'product',
        'file_name' => 'product.json',
        'dependencies' => [
          'WIM_User',
          'WIM_File',
          'WIM_Term_Tags',
        ],
      ],
      'WIM_News' => [
        'class_name' => 'NewsMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'news',
        'file_name' => 'news.json',
        'dependencies' => [
          'WIM_Term_Categories',
          'WIM_Term_Tags',
          'WIM_User',
          'WIM_File',
        ],
      ],
      'WIM_Faq' => [
        'class_name' => 'FaqMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'faq',
        'file_name' => 'faq.json',
        'dependencies' => [
          'WIM_Faq_Categories',
          'WIM_Term_Tags',
          'WIM_User',
        ],
      ],
      'WIM_Agenda' => [
        'class_name' => 'AgendaMigration',
        'group_name' => 'WIMMigrate',
        'content_type' => 'agenda',
        'file_name' => 'agenda.json',
        'dependencies' => [
          'WIM_File',
          'WIM_Term_Tags',
          'WIM_User',
        ],
      ],
      'WIM_BlockCustom' => [
        'class_name' => 'BlockCustomMigration',
        'group_name' => 'WIMMigrate',
        'file_name' => 'block-custom.json',
      ],
      'WIM_TopTasksMenu' => [
        'class_name' => 'TopTasksMenuMigration',
        'group_name' => 'WIMMigrate',
        'file_name' => 'top-tasks.json',
        'menu_name' => 'menu-top-tasks',
        'dependencies' => [
          'WIM_File',
        ],
      ],
      'WIM_SocialMediaMenu' => [
        'class_name' => 'SocialMediaMenuMigration',
        'group_name' => 'WIMMigrate',
        'file_name' => 'social-media.json',
        'menu_name' => 'menu-social-media',
      ],
      'WIM_Editorial' => [
        'class_name' => 'EditorialMigration',
        'group_name' => 'WIMMigrate',
        'file_name' => 'editorial.json',
        'dependencies' => [
          'WIM_File',
        ],
      ],
    ],
  ];

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
    $this->dataSources = DRUPAL_ROOT . '/' . drupal_get_path('module', 'wim_fixtures') . '/data_sources/';

  }

}

/**
 * Extended class to handle list with id's.
 */
class WIMListJSON extends MigrateListJSON {

  /**
   * Getting id from json.
   *
   * The default implementation assumes the IDs are top-level array elements,
   * but the array elements are the data items - we need to look inside them
   * for the IDs.
   *
   * @param array $data
   *    Array of items.
   *
   * @return array
   *    Id's
   */
  protected function getIDsFromJSON(array $data) { // @codingStandardsIgnoreLine
    $ids = [];
    foreach ($data as $item) {
      $ids[] = $item['id'];
    }
    return $ids;
  }

}

/**
 * Extended class to handle json data.
 */
class WIMItemJSON extends MigrateItemJSON {
  protected $data = [];

  /**
   * Get item.
   *
   * Two problems with the default getItem() - it reads and parses the JSON on
   * each call, which we don't want to do for multiple items in the file; and,
   * we need to retrieve a given item from
   * the file according to its 'id' element.
   *
   * @param string $id
   *    Item id.
   *
   * @return null|object
   *    Object or null.
   */
  public function getItem($id) {
    // We cache the parsed JSON at $this->data.
    if (empty($this->data)) {
      $data = $this->loadJSONUrl($this->itemUrl);
      if ($data) {
        // Let's index the array by the ID for easy retrieval.
        foreach ($data as $item) {
          $this->data[$item->id] = $item;
        }
      }
      else {
        // Error-handling here....
      }
    }
    // Return the requested item.
    if (isset($this->data[$id])) {
      return $this->data[$id];
    }
    else {
      return NULL;
    }
  }

}
