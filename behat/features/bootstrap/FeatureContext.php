<?php

/**
 * @file
 * The primary PHP file for adding functions for Behat tests.
 */

use Drupal\DrupalExtension\Context\RawDrupalContext;
use Behat\Mink\Driver\Selenium2Driver;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\Testwork\Hook\Scope\BeforeSuiteScope;
use Behat\Testwork\Hook\Scope\AfterSuiteScope;
use Behat\Mink\Exception\ElementNotFoundException;
use Behat\Behat\Hook\Scope\BeforeScenarioScope;
use Behat\Behat\Hook\Scope\AfterStepScope;
use Behat\Mink\WebAssert;

/**
 * Defines application features from the specific context.
 */
class FeatureContext extends RawDrupalContext implements SnippetAcceptingContext {

  // @var Drupal\DrupalExtension\Context\MinkContext
  private $minkContext;

  /**
   * This will be run when Behat testing suite is started.
   *
   * Add logout link to the main menu.
   *
   * @BeforeSuite
   */
  public static function addLogoutItem(BeforeSuiteScope $scope) {
    $item = array(
      'link_path' => 'user/logout',
      'link_title' => 'Log out',
      'menu_name' => 'main-menu',
      'weight' => 0,
      'language' => LANGUAGE_NONE,
      'plid' => 0,
      'module' => 'menu',
    );

    menu_link_save($item);
  }

  /**
   * This will be run when Behat testing suite is ended.
   *
   * Remove logout link.
   *
   * @AfterSuite
   */
  public static function removeLogoutItem(AfterSuiteScope $scope) {
    menu_link_delete(NULL, 'user/logout');
  }

  /**
   * This will be run when Behat testing suite is started.
   *
   * Enable all necessary features and modules which are disabled by default.
   *
   * @BeforeSuite
   */
  public static function enableFeaturesModules(BeforeSuiteScope $scope) {
    module_enable(array('atos_esuite'));
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
   * This will add mink context before scenario.
   *
   * @BeforeScenario
   */
  public function gatherContexts(BeforeScenarioScope $scope) {
    $environment = $scope->getEnvironment();

    $this->minkContext = $environment->getContext('Drupal\DrupalExtension\Context\MinkContext');
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
    if ($migration) {
      $dependencies = $migration->getHardDependencies();
      if ($dependencies) {
        foreach ($dependencies as $name) {
          self::runMigration($name);
        }
      }
      $migration->processImport();
    }
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
      if ($migration) {
        $dependencies += $migration->getDependencies();
      }
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
   * Before run cookie message test enable it.
   *
   * @BeforeScenario @cookie
   */
  public function enableCookieModule() {
    module_enable(array('cookie_consent'));
    variable_set('cookie_consent_style', 'custom');
    variable_set('cookie_consent_roles', drupal_map_assoc(array(DRUPAL_ANONYMOUS_RID)));
  }

  /**
   * After run cookie message test disable it.
   *
   * @AfterScenario @cookie
   */
  public function disableCookieModule($event) {
    variable_del('cookie_consent_style');
    variable_del('cookie_consent_roles');
    module_disable(array('cookie_consent'));
  }

  /**
   * Checks if an option is selected in the dropdown.
   *
   * @param string $option
   *   The option string to be searched for.
   * @param string $select
   *   The dropdown field selector.
   *
   * @throws \Behat\Mink\Exception\ElementNotFoundException
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
   * @throws \Behat\Mink\Exception\ElementNotFoundException
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
   * @throws \Behat\Mink\Exception\ElementNotFoundException
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
      throw new ElementNotFoundException('The node "' . $type . '" with the title "' . $title . '" was not found.');
    }

    $this->getSession()->visit($this->locatePath('/node/' . $nid));
  }

  /**
   * I mouseover the link (link) in the (menu title) region.
   *
   * @param string $link
   *   The menu link.
   * @param string $region
   *   The region.
   *
   * @throws \Exception
   *
   * @When /^I mouseover the link "(?P<text>[^"]*)" in the "(?P<region>[^"]*)"(?:| region)$/
   */
  public function iMouseOverTheLinkInTheRegion($link, $region) {
    $session = $this->getSession();
    $regionObj = $session->getPage()->find('region', $region);
    $link_element = $regionObj->findLink($link);
    if (NULL === $link_element) {
      throw new \Exception(sprintf('Link "%s" is not found in the "%s" region on the page %s.', $link, $region, $session->getCurrentUrl()));
    }
    $link_element->mouseOver();
  }

  /**
   * I fill in autocomplete "field" with "text" and click "text".
   *
   * @param string $autocomplete
   *    Title for field.
   * @param string $text
   *    Entered text.
   * @param string $popup
   *    Text in popup list.
   *
   * @throws \Exception
   *
   * @When I fill in the autocomplete :autocomplete with :text and click :popup
   */
  public function fillInDrupalAutocomplete($autocomplete, $text, $popup) {
    $el = $this->getSession()->getPage()->findField($autocomplete);
    $el->focus();

    // Set the autocomplete text then put a space at the end which triggers
    // the JS to go do the autocomplete stuff.
    $el->setValue($text);
    $el->keyUp(' ');

    // Sadly this grace of 1 second is needed here.
    sleep(1);
    $this->minkContext->iWaitForAjaxToFinish();

    // We need the id for filed where to search for dropdown list.
    $parent = $el->getParent()->getParent();

    $parent_id = $parent->getAttribute('id');
    if (NULL === $parent_id) {
      throw new \Exception(t('Could not find the parent id where to find the popup box'));
    }

    $element_selector = '#autocomplete';
    $autocomplete = $parent->find('css', $element_selector);
    if (NULL === $autocomplete) {
      throw new \Exception(t('Could not find the autocomplete popup box'));
    }

    $popup_element = $autocomplete->find('xpath', "//div[text() = '{$popup}']");

    if (empty($popup_element)) {
      throw new \Exception(t('Could not find autocomplete popup text @popup', array(
        '@popup' => $popup,
      )));
    }

    $popup_element->click();
    // We need to click outside to hide list.
    $parent->click();
  }

  /**
   * I mouseover the (element) element.
   *
   * @param string $element_selector
   *   The element selector.
   *
   * @throws \Exception
   *
   * @Given /^I mouseover the "(?P<element>[^"]*)" element$/
   */
  public function iMouseOverTheElement($element_selector) {
    $web = new WebAssert($this->getSession());
    $element = $web->elementExists('css', $element_selector);
    $session = $this->getSession();

    if (NULL === $element) {
      throw new \Exception(sprintf('Element "%s" is not found on the page %s', $element_selector, $session->getCurrentUrl()));
    }

    $element->mouseOver();
  }

  /**
   * I click the (element) element.
   *
   * @param string $element_selector
   *   The element selector.
   *
   * @throws \Exception
   *
   * @Given /^I click the "(?P<element>[^"]*)" element$/
   */
  public function iClickTheElement($element_selector) {
    $web = new WebAssert($this->getSession());
    $element = $web->elementExists('css', $element_selector);
    $session = $this->getSession();

    if (NULL === $element) {
      throw new \Exception(sprintf('Element "%s" is not found on the page %s', $element_selector, $session->getCurrentUrl()));
    }

    $element->click();
  }

  /**
   * Helper step to take screenshot if there is an error.
   *
   * @AfterStep
   */
  public function takeScreenShotAfterFailedStep(afterStepScope $scope) {
    if (99 === $scope->getTestResult()->getResultCode()) {
      $driver = $this->getSession()->getDriver();
      if (!($driver instanceof Selenium2Driver)) {
        return;
      }
      file_put_contents('/var/www/html/sites/default/files/test.png', $this->getSession()
        ->getDriver()
        ->getScreenshot());
    }
  }

  /**
   * CKEditor.
   *
   * @Then I fill in wysiwyg on field :locator with :value
   */
  public function iFillInWysiwygOnFieldWith($locator, $value) {
    $el = $this->getSession()->getPage()->findField($locator);

    if (empty($el)) {
      throw new ExpectationException('Could not find WYSIWYG with locator: ' . $locator, $this->getSession());
    }

    $fieldId = $el->getAttribute('id');

    if (empty($fieldId)) {
      throw new Exception('Could not find an id for field with locator: ' . $locator);
    }

    $this->getSession()
      ->executeScript("CKEDITOR.instances[\"$fieldId\"].setData(\"$value\");");
  }

  /**
   * Checks that field with specified in|name|label|value is disabled.
   *
   * Example: Then the field "Email" should be disabled.
   * Example: Then the "Email" field should be disabled.
   *
   * @Then /^the "(?P<name>(?:[^"]|\\")*)" (?P<type>(?:(field|button))) should (?P<negate>(?:(not |)))be disabled/
   * @Then /^the (?P<type>(?:(field|button))) "(?P<name>(?:[^"]|\\")*)" should (?P<negate>(?:(not |)))be disabled/
   */
  public function stepFieldShouldBeDisabled($name, $type, $negate) {
    $page = $this->getSession()->getPage();
    if ($type === 'field') {
      $element = $page->findField($name);
    }
    else {
      $element = $page->find('named', array(
        'button',
        $this->getSession()->getSelectorsHandler()->xpathLiteral($name),
      ));
    }

    if (empty($element)) {
      throw new Exception(sprintf("Element '%s' not found", $name));
    }

    $disabledAttribute = $element->getAttribute('disabled');
    if (trim($negate)) {
      if (!empty($disabledAttribute)) {
        throw new Exception(sprintf("Failed asserting element '%s' is not disabled", $name));
      }
    }
    else {
      if (empty($disabledAttribute)) {
        throw new Exception(sprintf("Failed asserting element '%s' is disabled", $name));
      }
    }
  }

  /**
   * I see the metatag.
   *
   * @param string $metaname
   *    Title for field.
   * @param string $text
   *    Entered text.
   *
   * @throws \Exception
   *
   * @When I see the metatag :metaname with :text
   */
  public function seeTheMeta($metaname, $text) {
    $page = $this->getSession()->getPage();

    $contents = $page->find('xpath', '//meta[@name="' . $metaname . '"]');

    if (is_null($contents) || trim($contents->getAttribute('content')) !== trim($text)) {
      throw new Exception(sprintf("Content '%s' not found", $text));
    }
  }

  /**
   * I see the title metatag.
   *
   * @param string $text
   *    Entered text.
   *
   * @throws \Exception
   *
   * @When I see the title meta with :text
   */
  public function seeTheTitleMeta($text) {
    $page = $this->getSession()->getPage();

    $content = $page->find('xpath', '//title[text()="' . $text . '"]');

    if (is_null($content)) {
      throw new Exception(sprintf("Title content '%s' not found", $text));
    }
  }

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
   * I switch to the iframe "name".
   *
   * @Given /^I switch to the iframe "([^"]*)"$/
   */
  public function iSwitchToIframe($arg1 = NULL) {
    $this->getSession()->switchToIFrame($arg1);
  }

  /**
   * I switch back from an iframe.
   *
   * @When I switch back from an iframe
   */
  public function iSwitchBackFromAnIframe() {
    $this->getSession()->switchToIFrame();
  }

  /**
   * Click nth link element with given name.
   *
   * @When I click :num nth :link
   *
   * @throws \Exception
   *   If nth link or link cannot be found.
   */
  public function iClickNthElement($num, $link) {
    $page = $this->getSession()->getPage();
    $links = $page->findAll('named', array('link', $link));
    if ((int) $num > count($links)) {
      throw new \Exception(sprintf('The "%s" nth link was not found on the page %s', $num, $this->getSession()->getCurrentUrl()));
    }
    // Find the link within the region.
    $linkObj = $links[$num - 1];
    if (empty($linkObj)) {
      throw new \Exception(sprintf('The link "%s" was not found with number "%s" on the page %s', $link, $num, $this->getSession()->getCurrentUrl()));
    }

    $linkObj->click();
  }

}
