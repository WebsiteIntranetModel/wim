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

    $columns = [
      'id' => t('Link id'),
      'link_title' => t('Link title'),
      'link_path' => t('Link path'),
      'expanded' => t('Link expanded'),
      'has_children' => t('Link has children'),
      'plid' => t('Parent id'),
      'depth' => t('Depth'),
      'icon' => t('Icon'),
    ];

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, []), $columns);

    $this->destination = new MigrateDestinationMenuLinks();
    $this->map = new MigrateSQLMap($this->machineName, [
      'id' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'ID of destination link',
      ],
    ], MigrateDestinationMenuLinks::getKeySchema());

    $this->addSimpleMappings([
      'link_title',
      'link_path',
      'expanded',
      'has_children',
      'depth',
    ]);

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
      $entity->options = [
        'menu_icon' => [
          'enable' => 1,
          'image_style' => 'icon',
          'path' => $icon->uri,
        ],
      ];
    }
    else {
      $entity->options = [];
    }
  }

}

/**
 * Class SocialMediaMenuMigration.
 */
class SocialMediaMenuMigration extends WIMMigration {
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

    $columns = [
      'id' => t('Link id'),
      'link_title' => t('Link title'),
      'link_path' => t('Link path'),
    ];

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, []), $columns);

    $this->destination = new MigrateDestinationMenuLinks();
    $this->map = new MigrateSQLMap($this->machineName, [
      'id' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'ID of destination link',
      ],
    ], MigrateDestinationMenuLinks::getKeySchema());

    $this->addSimpleMappings([
      'link_title',
      'link_path',
    ]);

    $this->addFieldMapping('menu_name')
      ->defaultValue($this->menuName);

  }

}
