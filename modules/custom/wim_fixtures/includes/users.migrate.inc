<?php
/**
 * @file
 * User-only migration.
 */

/**
 * Class WIMUsers.
 */
class WIMUsers extends WIMMigration {

  /**
   * Constructor.
   *
   * @param array $arguments
   *   Arguments.
   */
  public function __construct($arguments) {
    parent::__construct($arguments);

    $this->description = t('Import an JSON-file (only "Account"-fields)');

    $columns = array(
      'id' => t('User-ID'),
      'mail' => t('Email'),
      'name' => t('Name'),
      'password' => t('Password'),
      'roles' => t('Roles'),
    );

    $this->source = new MigrateSourceList(new WIMListJSON($this->dataSources . 'users.json'),
      new WIMItemJSON($this->dataSources . 'users.json', array()), $columns);

    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName, array(
      'id' => array(
        'type' => 'varchar',
        'length' => 6,
        'not null' => TRUE,
        'description' => t('UserID'),
      ),
    ), MigrateDestinationUser::getKeySchema());

    // Mapped fields.
    $this->addSimpleMappings(array('name'));
    $this->addFieldMapping('mail', 'mail')
      ->defaultValue('')
      ->description(t('Email address'));
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));

    $this->addFieldMapping('pass', 'password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));

    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));

    $this->addFieldMapping('role_names', 'roles')
      ->description('Role')->separator(',');

    $this->addFieldMapping('status')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));

    // Other handlers.
    if (module_exists('path')) {
      $this->addFieldMapping('path')
        ->defaultValue(NULL)
        ->description(t('Path alias'));
    }
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
  }

}
