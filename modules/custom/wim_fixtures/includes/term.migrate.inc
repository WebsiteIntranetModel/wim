<?php
/**
 * @file
 * Term migration.
 */

/**
 * Class TermMigration.
 */
class TermMigration extends WIMMigration {

  public $destinationVocabulary = '';
  public $fileName = '';

}

/**
 * Class WIMTermMigration.
 */
class WIMTermMigration extends TermMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->destinationVocabulary = $arguments['destination_vocabulary'];
    $this->fileName = $arguments['file_name'];

    $columns = array(
      array('id', t('Id')),
      array('name', t('Name')),
    );

    $this->source = new MigrateSourceCSV($this->dataSources . $this->fileName, $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationTerm($this->destinationVocabulary);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationTerm::getKeySchema());

    $this->addFieldMapping('name', 'name');
  }

}
