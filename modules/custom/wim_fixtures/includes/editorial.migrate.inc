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

    $columns = [
      'id' => t('Id'),
      'label' => t('Label'),
      'title' => t('Title'),
      'field_body' => t('Body'),
      'field_link' => t('Link'),
      'field_image' => t('Image'),
      'meta_title' => t('Metatag title'),
      'meta_keywords' => t('Metatag keywords'),
      'meta_description' => t('Metatag description'),
    ];

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, []), $columns);

    $this->destination = new MigrateDestinationBean('editorial');
    $this->map = new MigrateSQLMap($this->machineName, [
      'id' => [
        'type' => 'int',
        'unsigned' => TRUE,
        'description' => 'ID of destination node',
      ],
    ], MigrateDestinationBean::getKeySchema());

    $this->addSimpleMappings([
      'label',
      'title',
      'field_body',
      'field_link',
    ]);

    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('Alt text');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(FALSE);
  }

}
