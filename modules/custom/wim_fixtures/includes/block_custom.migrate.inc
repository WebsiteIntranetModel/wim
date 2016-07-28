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

    $columns = array(
      array('id', t('Id')),
      array('info', t('Block description')),
      array('body', t('Body')),
    );

    $this->source = new MigrateSourceCSV($this->dataSources . $this->fileName, $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationCustomBlock();
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationCustomBlock::getKeySchema());

    $this->addSimpleMappings(array(
      'info',
      'body',
    ));
  }

}
