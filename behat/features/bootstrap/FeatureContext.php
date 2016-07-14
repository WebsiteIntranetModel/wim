<?php

/**
 * @file
 * The primary PHP file for adding functions for Behat tests.
 */

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Testwork\Hook\Scope\BeforeSuiteScope;
use Behat\Testwork\Hook\Scope\AfterSuiteScope;
use Behat\Mink\Exception\ElementNotFoundException;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  /**
   * I wait for (seconds) seconds.
   *
   * @When I wait for :arg1 seconds
   */
  public function iWaitForSeconds($seconds, $condition = '') {
    $milliseconds = (int) ($seconds * 1000);
    $this->getSession()->wait($milliseconds, $condition);
  }

  /**
   * This will be run when Behat testing suite is started.
   *
   * @BeforeSuite
   */
  public static function enableFixtureModules(BeforeSuiteScope $scope) {
    module_enable(array('migrate', 'wim_fixtures'));
    variable_set('admin_menu_position_fixed', 0);

    $machine_names = self::getAllFixtureMigrations(TRUE);
    foreach ($machine_names as $machine_name) {
      self::runMigration($machine_name);
    }
  }

  /**
   * This will be run when Behat testing suite is ended.
   *
   * @AfterSuite
   */
  public static function disableFixtureModules(AfterSuiteScope $scope) {
    $machine_names = self::getAllFixtureMigrations();
    self::revertMigrations($machine_names);
    module_disable(array('migrate', 'wim_fixtures'));
    variable_del('admin_menu_position_fixed');
  }

  /**
   * Get all migrations from api.
   *
   * @param bool|FALSE $register
   *   If we should register migration.
   *
   * @return array
   *   Machine names array.
   */
  protected static function getAllFixtureMigrations($register = FALSE) {
    if (!module_exists('wim_fixtures')) {
      return array();
    }

    module_load_include('inc', 'wim_fixtures', 'wim_fixtures.migrate');
    $migrations = wim_fixtures_migrate_api();
    $machine_names = array();
    foreach ($migrations['migrations'] as $name => $migration) {
      $machine_names[] = $name;
    }

    if ($register) {
      migrate_static_registration($machine_names);
    }

    return $machine_names;
  }

  /**
   * Just run the migrations.
   *
   * @param string $machine_name
   *   Machine name.
   *
   * @throws \Exception
   */
  protected static function runMigration($machine_name) {
    $migration = Migration::getInstance($machine_name);
    $dependencies = $migration->getHardDependencies();
    if ($dependencies) {
      foreach ($dependencies as $name) {
        self::runMigration($name);
      }
    }
    $migration->processImport();
  }

  /**
   * Just revert all migrations.
   *
   * @param array $machine_names
   *   Machine names.
   *
   * @throws \Exception
   */
  protected static function revertMigrations($machine_names) {
    $dependencies = array();
    foreach ($machine_names as $machine_name) {
      $migration = Migration::getInstance($machine_name);
      $dependencies += $migration->getDependencies();
    }

    foreach ($dependencies as $dependency) {
      $dependencies[$dependency] = $dependency;
    }

    // First revert top level migrations (no dependencies)
    foreach ($machine_names as $machine_name) {
      if (in_array($machine_name, $dependencies)) {
        continue;
      }
      self::revertMigration($machine_name);
    }

    if ($dependencies) {
      self::revertMigrations($dependencies);
    }
  }

  /**
   * Revert single migration.
   *
   * @param string $machine_name
   *   Migration name.
   *
   * @throws \Exception
   */
  protected static function revertMigration($machine_name) {
    $migration = Migration::getInstance($machine_name);
    $migration->processRollback(array('force' => TRUE));
  }

  /**
   * Checks if an option is selected in the dropdown.
   *
   * @param string $option
   *   The option string to be searched for.
   * @param string $select
   *   The dropdown field selector.
   *
   * @throws \Exception
   *
   * @Then /^the "(?P<option>(?:[^"]|\\")*)" option from "(?P<select>(?:[^"]|\\")*)" (?:is|should be) selected$/
   */
  public function theOptionFromShouldBeSelected($option, $select) {
    // Get the object of the dropdown field.
    $dropDown = $this->getSession()->getPage()->findField($select);
    if (empty($dropDown)) {
      throw new \Exception('The page does not have the dropdown with label "' . $select . '"');
    }
    $optionField = $dropDown->find('named', array(
      'option',
      $option,
    ));

    if (NULL === $optionField) {
      throw new ElementNotFoundException($this->getSession(), 'select option field', 'id|name|label|value', $option);
    }

    if (!$optionField->isSelected()) {
      throw new \Exception('Select option field with value|text "' . $option . '" is not selected in the select "' . $select . '"');
    }
  }

  /**
   * Checks if an option is not selected in the dropdown.
   *
   * @param string $option
   *   The option string to be searched for.
   * @param string $select
   *   The dropdown field selector.
   *
   * @throws \Exception
   *
   * @Then /^the "(?P<option>(?:[^"]|\\")*)" option from "(?P<select>(?:[^"]|\\")*)" (?:is not|should not be) selected$/
   */
  public function theOptionFromShouldNotBeSelected($option, $select) {
    // Get the object of the dropdown field.
    $dropDown = $this->getSession()->getPage()->findField($select);
    if (empty($dropDown)) {
      throw new \Exception('The page does not have the dropdown with label "' . $select . '"');
    }
    $optionField = $dropDown->find('named', array(
      'option',
      $option,
    ));

    if (NULL === $optionField) {
      throw new ElementNotFoundException($this->getSession(), 'select option field', 'id|name|label|value', $option);
    }

    if ($optionField->isSelected()) {
      throw new \Exception('Select option field with value|text "' . $option . '" is selected in the select "' . $select . '"');
    }
  }

  /**
   * Viewing node type with given title.
   *
   * @param string $type
   *   The node type.
   * @param string $title
   *   The node title.
   *
   * @throws \Exception
   *
   * @Given I am viewing :type (content ) node with the title :title
   */
  public function viewingNodeWithTheTitle($type, $title) {
    // Fetch node with given title.
    $result = db_query("SELECT n.nid FROM {node} n WHERE n.title = :title AND n.type = :type", array(
      ":title" => $title,
      ":type" => $type,
    ));
    $nid = $result->fetchField();

    if (!$nid) {
      throw new \Exception('The node "' . $type . '" with the title "' . $title . '" was not found.');
    }

    $this->getSession()->visit($this->locatePath('/node/' . $nid));
  }

}
