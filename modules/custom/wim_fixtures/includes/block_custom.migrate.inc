<?php

/**
 * @file
 * Block Custom migration.
 */

/**
 * Class BlockCustomMigration.
 */
class BlockCustomMigration extends WIMMigration {
  public $fileName = '';

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];

    $columns = [
      'id' => t('Id'),
      'info' => t('Block description'),
      'body' => t('Body'),
    ];

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, []), $columns);

    $this->destination = new MigrateDestinationCustomBlock();
    $this->map = new MigrateSQLMap($this->machineName, [
      'id' => [
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ],
    ], MigrateDestinationCustomBlock::getKeySchema());

    $this->addSimpleMappings([
      'info',
      'body',
    ]);
  }

}
