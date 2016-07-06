<?php
/**
 * @file
 * Nodes migration.
 */

/**
 * Class NodeMigration.
 */
class FileMigration extends WIMMigration {

}

/**
 * Class WIMFile.
 */
class WIMFile extends FileMigration {

  protected $sourceDir;
  protected $destinationDir;

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);

    $this->description = t('Import files.');
    $this->sourceDir = $arguments['source_dir'];
    $this->destinationDir = $arguments['destination_dir'];

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'sourceid' => array(
          'type' => 'varchar',
          'length' => 255,
          'not null' => TRUE,
        ),
      ),
      MigrateDestinationFile::getKeySchema()
    );

    $directories = array(
      $this->sourceDir,
    );

    // Edit to include the desired extensions.
    $allowed = 'jpg jpeg gif png pdf docx txt';
    if (module_exists('file_entity')) {
      $allowed = variable_get('file_entity_default_allowed_extensions', $allowed);
    }
    $file_mask = '/^.*\.(' . str_replace(array(',', ' '), '|', $allowed) . ')$/i';
    $list = new MigrateListFiles($directories, $this->sourceDir, $file_mask);
    // Send FALSE as second argument to prevent loading of file data, which we
    // don't need.
    $item = new MigrateItemFile($this->sourceDir, FALSE);
    $fields = array('sourceid' => t('File name with path'));
    $this->source = new MigrateSourceList($list, $item, $fields);
    $this->destination = new MigrateDestinationFile('file', 'MigrateFileUri');

    // Save to the default file scheme.
    $this->addFieldMapping('destination_dir')
      ->defaultValue($this->destinationDir);
    // Use the full file path in the file name so that we retain the directory
    // structure.
    $this->addFieldMapping('destination_file', 'destination_file');
    // Set the value to the file name, including path.
    $this->addFieldMapping('value', 'file_uri');
  }

  /**
   * Implementation of prepareRow().
   *
   * This method is called from the source
   * plugin upon first pulling the raw data from the source.
   *
   * @param object $row
   *   Object containing raw source data.
   *
   * @return bool
   *   TRUE to process this row, FALSE to have the source skip it.
   */
  public function prepareRow($row) {
    if (parent::prepareRow($row) === FALSE) {
      return FALSE;
    }

    $row->file_uri = $this->sourceDir . $row->sourceid;

    // Remove the leading forward slash.
    $row->destination_file = substr($row->sourceid, 1);
  }

}
