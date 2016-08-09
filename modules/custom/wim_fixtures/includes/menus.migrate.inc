<?php
/**
 * @file
 * Menus-only migration.
 */

/**
 * Class TopTasksMenuMigration.
 */
class TopTasksMenuMigration extends WIMMigration {
  public $fileName = '';
  public $menuName = '';

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->menuName = $arguments['menu_name'];

    $columns = array(
      array('mlid', t('Link id')),
      array('link_title', t('Link title')),
      array('link_path', t('Link path')),
      array('expanded', t('Link expanded')),
      array('has_children', t('Link has children')),
      array('plid', t('Parent id')),
      array('depth', t('Depth')),
      array('icon', t('Icon')),
    );

    $this->source = new MigrateSourceCSV($this->dataSources . $this->fileName, $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationMenuLinks();
    $this->map = new MigrateSQLMap($this->machineName, array(
      'mlid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'ID of destination link',
      ),
    ), MigrateDestinationMenuLinks::getKeySchema());

    $this->addSimpleMappings(array(
      'link_title',
      'link_path',
      'expanded',
      'has_children',
      'depth',
    ));

    $this->addFieldMapping('menu_name')
      ->defaultValue($this->menuName);

    $this->addFieldMapping('plid', 'plid')
      ->sourceMigration($this->getMachineName());
    $this->addFieldMapping('options', 'icon')->sourceMigration('WIM_File');

  }

  /**
   * Prepare entity.
   *
   * Set options for menu items.
   */
  public function prepare($entity, stdClass $row) {
    if (isset($entity->options) && !empty($entity->options)) {
      $icon = file_load($entity->options);
      $entity->options = array(
        'menu_icon' => array(
          'enable' => 1,
          'image_style' => 'icon',
          'path' => $icon->uri,
        ),
      );
    }
    else {
      $entity->options = array();
    }
  }

}
