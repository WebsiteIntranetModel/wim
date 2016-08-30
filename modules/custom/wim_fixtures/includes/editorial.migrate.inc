<?php
/**
 * @file
 * Editorial migration.
 */

/**
 * Class EditorialMigration.
 */
class EditorialMigration extends WIMMigration {
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
      array('label', t('Label')),
      array('title', t('Title')),
      array('field_body', t('Body')),
      array('field_link', t('Link')),
      array('field_image', t('Image')),
    );

    $this->source = new MigrateSourceCSV($this->dataSources . $this->fileName, $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationBean('editorial');
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'description' => 'ID of destination node',
      ),
    ), MigrateDestinationBean::getKeySchema());

    $this->addSimpleMappings(array(
      'label',
      'title',
      'field_body',
      'field_link',
    ));

    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(FALSE);
  }

}
