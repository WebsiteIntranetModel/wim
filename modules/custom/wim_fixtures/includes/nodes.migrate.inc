<?php
/**
 * @file
 * Nodes migration.
 */

/**
 * Class NodeMigration.
 */
class NodeMigration extends WIMMigration {

  public $fileName = '';
  public $contentType = '';

}

/**
 * Class BasicPageMigration.
 */
class BasicPageMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];

    $columns = array(
      'id' => t('Id'),
      'title' => t('Node title'),
      'body' => t('Node body'),
      'summary' => t('Node summary'),
      'field_image' => t('Node image'),
      'field_tags' => t('Node tags'),
      'field_publication_date' => t('Custom publication date'),
      'field_promoted' => t('Promoted flag'),
      'author' => t('Node creator'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'body:summary',
      'field_publication_date',
      'field_promoted',
    ));

    $this->addFieldMapping('body:format')->defaultValue('full_html');

    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(FALSE);
    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);
    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');
  }

}

/**
 * Class PersonMigration.
 */
class PersonMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];

    $columns = array(
      'id' => t('Id'),
      'title' => t('Person title'),
      'body' => t('Person body'),
      'summary' => t('Person summary'),
      'field_image' => t('Person image'),
      'field_tags' => t('Person tags'),
      'field_person_roles' => t('Person roles'),
      'field_person_phone' => t('Phone'),
      'field_email' => t('Email'),
      'field_person_address' => t('Address'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'body:summary',
      'field_person_roles',
      'field_person_phone',
      'field_email',
      'field_person_address',
    ));

    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_person_address:format')->defaultValue('full_html');

    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(FALSE);
    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);
    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');
  }

}

/**
 * Class ProductMigration.
 *
 * Now it is same as basic page, extend later.
 */
class ProductMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {
    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];
    $columns = array(
      'id' => t('Id'),
      'title' => t('Node title'),
      'body' => t('Node body'),
      'body:summary' => t('Node summary'),
      'field_image' => t('Node image'),
      'field_tags' => t('Node tags'),
      'field_publication_date' => t('Custom publication date'),
      'field_promoted' => t('Promoted flag'),
      'author' => t('Node creator'),
    );
    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());
    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'body:summary',
      'field_publication_date',
      'field_promoted',
    ));

    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');
    $this->addFieldMapping('field_image:preserve_files')
      ->defaultValue(FALSE);
    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);
    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');
  }

}

/**
 * Class NewsMigration.
 */
class NewsMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];

    $columns = array(
      'id' => t('Id'),
      'title' => t('Node title'),
      'body' => t('Node body'),
      'body:summary' => t('Node summary'),
      'field_image' => t('Node image'),
      'field_tags' => t('Node tags'),
      'field_publication_date' => t('Custom publication date'),
      'field_attachment' => t('File attachment'),
      'field_news_category' => t('News category'),
      'field_promoted' => t('Promoted flag'),
      'author' => t('Node creator'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'body:summary',
      'field_publication_date',
      'field_promoted',
    ));

    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_attachment', 'field_attachment')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_attachment:file_class')
      ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);
    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');
    $this->addFieldMapping('field_news_category', 'field_news_category')
      ->sourceMigration('WIM_Term_Categories');
    $this->addFieldMapping('field_news_category:source_type')
      ->defaultValue('tid');
  }

}

/**
 * Class FaqMigration.
 *
 * Add demo content for FAQ.
 */
class FaqMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];

    $columns = array(
      'id' => t('Id'),
      'title' => t('Question'),
      'body' => t('Answer'),
      'field_faq_additional_information' => t('Additional information'),
      'field_tags' => t('FAQ tags'),
      'field_show_on_overview' => t('Show on overview flag'),
      'field_faq_category' => t('FAQ category'),
      'author' => t('Node creator'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'field_faq_additional_information',
      'field_show_on_overview',
    ));

    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);

    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('field_faq_additional_information:format')->defaultValue('full_html');
    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');

    $this->addFieldMapping('field_faq_category', 'field_faq_category')
      ->sourceMigration('WIM_Faq_Categories');
    $this->addFieldMapping('field_faq_category:source_type')
      ->defaultValue('tid');
  }

}

/**
 * Class AgendaMigration.
 *
 * Add demo content for Agenda.
 */
class AgendaMigration extends NodeMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct(array $arguments) {

    parent::__construct($arguments);
    $this->fileName = $arguments['file_name'];
    $this->contentType = $arguments['content_type'];

    $columns = array(
      'id' => t('Id'),
      'title' => t('Title'),
      'body' => t('Body'),
      'body:summary' => t('Node summary'),
      'field_image' => t('Node Image'),
      'field_agenda_date' => t('Date'),
      'name' => t('Location name'),
      'city' => t('City'),
      'street' => t('Street'),
      'postal_code' => t('Postal Code'),
      'country' => t('County'),
      'field_tags' => t('Tags'),
      'field_promoted' => t('Promoted flag'),
      'author' => t('Node creator'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . $this->fileName),
      new WIMItemJSON($this->dataSources . $this->fileName, array()), $columns);

    $this->destination = new MigrateDestinationNode($this->contentType);
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('ID'),
      ),
    ), MigrateDestinationNode::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array(
      'title',
      'body',
      'body:summary',
      'field_agenda_date',
      'field_promoted',
    ));

    $this->addFieldMapping('body:format')->defaultValue('full_html');
    $this->addFieldMapping('uid', 'author')
      ->sourceMigration('WIM_User')->defaultValue(1);

    $this->addFieldMapping('field_image', 'field_image')
      ->sourceMigration('WIM_File');
    $this->addFieldMapping('field_image:alt')->defaultValue('');
    $this->addFieldMapping('field_image:file_class')
      ->defaultValue('MigrateFileFid');

    $this->addFieldMapping('field_location')->defaultValue('TRUE');
    $this->addFieldMapping('field_location:name', 'name');
    $this->addFieldMapping('field_location:city', 'city');
    $this->addFieldMapping('field_location:street', 'street');
    $this->addFieldMapping('field_location:postal_code', 'postal_code');
    $this->addFieldMapping('field_location:country', 'country');

    $this->addFieldMapping('field_tags', 'field_tags')->separator(',')
      ->sourceMigration('WIM_Term_Tags');
    $this->addFieldMapping('field_tags:source_type')
      ->defaultValue('tid');

  }

}
