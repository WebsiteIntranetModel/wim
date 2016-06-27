<?php

/**
 * The primary PHP file for adding functions for Behat tests.
 *
 * PHP version 5.6
 *
 * @category FeatureContext
 * @package  Behat
 * @author   Bram ten Hove <username@example.com>
 * @author   Roman Paska <username@example.com>
 * @author   Volodymyr Kenidra <username@example.com>
 * @license  http://www.gnu.org/copyleft/gpl.html GNU General Public License
 * @link     none
 */

use Behat\Behat\Context\Context;
use Behat\Behat\Context\SnippetAcceptingContext;
use Behat\MinkExtension\Context\RawMinkContext;

/**
 * Defines application features from the specific context.
 *
 * @category FeatureContext
 * @package  Behat
 * @author   Bram ten Hove <username@example.com>
 * @author   Roman Paska <username@example.com>
 * @author   Volodymyr Kenidra <username@example.com>
 * @license  http://www.gnu.org/copyleft/gpl.html GNU General Public License
 * @link     none
 */
class FeatureContext extends RawMinkContext implements Context, SnippetAcceptingContext
{
    /**
     * Initializes context.
     *
     * Every scenario gets its own context instance.
     * You can also pass arbitrary arguments to the
     * context constructor through behat.yml.
     */
    public function __construct()
    {
    }

    /**
     * Get the wysiwyg instance variable to use in Javascript.
     *
     * @param string $instanceId The instanceId used by the WYSIWYG module
     * to identify the instance.
     *
     * @throws Exception
     *   Throws an exception if the editor does not exist.
     *
     * @return string
     *   A Javascript expression representing the WYSIWYG instance.
     */
    protected function getWysiwygInstance($instanceId)
    {
        $instance = "CKEDITOR.instances['$instanceId']";
        if (!$this->getSession()->evaluateScript("return !!$instance")) {
            throw new \Exception(
                sprintf(
                    'The editor "%s" was not found on the page %s',
                    $instanceId,
                    $this->getSession()->getCurrentUrl()
                )
            );
        }
        return $instance;
    }

    /**
     * Fills in data in the WYSIWYG editor.
     *
     * @param string $instanceId The instanceId used by the WYSIWYG
     * module to identify the instance.
     * @param string $text       Text to fill in.
     *
     * @When /^I fill in the "([^"]*)" WYSIWYG editor with "([^"]*)"$/
     *
     * @throws \Exception
     * @return void
     */
    public function iFillInTheWysiwygEditor($instanceId, $text)
    {
        $instance = $this->getWysiwygInstance($instanceId);
        $this->getSession()->executeScript("$instance.setData(\"$text\");");
    }

    /**
     * Clicks an admin link.
     *
     * @param string $text Link text
     *
     * @When I click admin link :text
     *
     * @throws \InvalidArgumentException
     * @return void
     */
    public function clickAdminLink($text)
    {
        $page = $this->getSession()->getPage();
        $adminspan = $page->find('xpath', '//a//span[text()="' . $text . '"]');

        if ($adminspan === null) {
            throw new \InvalidArgumentException(
                sprintf(
                    'Cannot find the admin link with text: "%s"',
                    $text
                )
            );
        }

        $adminlink = $adminspan->getParent();
        $adminlink->click();
    }

    /**
     * Click the link with given text.
     *
     * @param int    $position The xth position of link.
     * @param string $locator  Link text.
     *
     * @When I click the xth :position link with the text :locator
     *
     * @throws \InvalidArgumentException
     * @return void
     */
    public function iClickTheLinkWithText($position, $locator)
    {
        $session = $this->getSession();
        $links = $session->getPage()->findAll('named', array('link', $locator));
        $count = 1;
        foreach ($links as $link) {
            if ($count == $position) {
                // Now click the element.
                $link->click();
                return;
            }
            $count++;
        }
        throw new \InvalidArgumentException(
            sprintf(
                'Element not found with the locator: "%s"',
                $locator
            )
        );
    }

    /**
     * Click the CSS element at the given position.
     *
     * @param int    $position The xth element position.
     * @param string $css      Class name.
     *
     * @When I click the xth :position element with the css :css
     *
     * @throws \InvalidArgumentException
     * @return void
     */
    public function iClickTheCssElementAtPosition($position, $css)
    {
        $session = $this->getSession();
        $elements = $session->getPage()->findAll('css', $css);

        $count = 0;

        foreach ($elements as $element) {
            if ($count == $position) {
                // Now click the element.
                $element->click();
                return;
            }
            $count++;
        }
        throw new \InvalidArgumentException(
            sprintf(
                'Element not found with the css: "%s"',
                $css
            )
        );
    }

    /**
     * Click a radio button with a given label.
     *
     * @param string $label Element label
     * @param string $id    Element id
     *
     * @When I click radio button :label with the id :id
     * @When I click radio button :label
     *
     * @throws \Exception
     * @return void
     */
    public function clickRadioButton($label = '', $id = '')
    {
        $session = $this->getSession();

        $session->executeScript(
            "var inputs = document.getElementsByTagName('input');
            for(var i = 0; i < inputs.length; i++) {
            inputs[i].style.opacity = 1;
            inputs[i].style.left = 0;
            inputs[i].style.visibility = 'visible';
            inputs[i].style.position = 'relative';
            }"
        );

        $element = $session->getPage();

        $radiobutton = $id ? $element->findById($id) : $element->find(
            'named',
            array(
                'radio',
                $this->getSession()->getSelectorsHandler()->xpathLiteral($label),
            )
        );
        if ($radiobutton === null) {
            throw new \Exception(
                sprintf(
                    'The radio button with "%s" was not found on the page %s',
                    $id ? $id : $label,
                    $this->getSession()->getCurrentUrl()
                )
            );
        }

        $value = $radiobutton->getAttribute('value');
        $labelonpage = $radiobutton->getParent()->getText();

        if ($label !== '' && $label != $labelonpage) {
            throw new \Exception(
                sprintf(
                    "Button with id '%s' has label '%s' instead of '%s' on the page %s",
                    $id,
                    $labelonpage,
                    $label,
                    $this->getSession()->getCurrentUrl()
                )
            );
        }

        $radiobutton->selectOption($value, false);
    }

    /**
     * Shows hidden button.
     *
     * @When /^(?:|I )show hidden buttons$/
     *
     * @return void
     */
    public function showHiddenButton()
    {
        $session = $this->getSession();

        $session->executeScript(
            "var inputs = document.getElementsByClassName('secondary-action');
            for(var i = 0; i < inputs.length; i++) {
            inputs[i].style.opacity = 1;
            inputs[i].style.left = 0;
            inputs[i].style.position = 'relative';
            inputs[i].style.display = 'block';
            }"
        );
    }

    /**
     * Shows hidden checkboxes.
     *
     * @When /^(?:|I )show hidden checkboxes/
     *
     * @return void
     */
    public function showHiddenCheckbox()
    {
        $session = $this->getSession();

        $session->executeScript(
            "var inputs = document.getElementsByClassName('form-checkbox');
            for(var i = 0; i < inputs.length; i++) {
            inputs[i].style.opacity = 1;
            inputs[i].style.left = 0;
            inputs[i].style.position = 'relative';
            inputs[i].style.display = 'block';
          }"
        );
    }

    /**
     * Opens specified page.
     *
     * @param string $username String with the account's user name.
     *
     * @Given /^(?:|I )am on the profile of "(?P<username>[^"]+)"$/
     *
     * @When /^(?:|I )go to the profile of "(?P<username>[^"]+)"$/
     *
     * @throws \Exception
     * @return void
     */
    public function openProfileOf($username)
    {
        $account = user_load_by_name($username);
        if ($account->id() !== 0) {
            $account_uid = $account->id();
        } else {
            throw new \Exception(
                sprintf(
                    "User with username '%s' does not exist.",
                    $username
                )
            );
        }
        $page = '/user/' . $account_uid;

        $this->visitPath($page);
    }

    /**
     * Executes resize window before every scenario to prevent Selenium issues.
     *
     * @BeforeScenario
     *
     * @return void
     */
    public function resizeWindow()
    {
        $this->getSession()->resizeWindow(1280, 2024, 'current');
    }

    /**
     * Opens specified node page of type and with title.
     *
     * @param string $type  Node type
     * @param string $title Node title
     *
     * @Given /^(?:|I )open the "(?P<type>[^"]+)" node
     * with title "(?P<title>[^"]+)"$/
     *
     * @When /^(?:|I )go the  "(?P<type>[^"]+)" node
     * with title "(?P<title>[^"]+)"$/
     *
     * @throws \Exception
     * @return void
     */
    public function openNodeWithTitle($type, $title)
    {
        $query = \Drupal::entityQuery('node')
          ->condition('type', $type)
          ->condition('title', $title, '=')
          ->addTag('DANGEROUS_ACCESS_CHECK_OPT_OUT');
        $nids = $query->execute();

        if (!empty($nids) && count($nids) === 1) {
            $nid = reset($nids);
            $page = '/node/' . $nid;

            $this->visitPath($page);
        } else {
            if (count($nids) > 1) {
                throw new \Exception(
                    sprintf(
                        "Multiple nodes of type '%s' with title '%s' found.",
                        $type,
                        $title
                    )
                );
            } else {
                throw new \Exception(
                    sprintf(
                        "Node of type '%s' with title '%s' does not exist.",
                        $type,
                        $title
                    )
                );
            }
        }
    }

    /**
     * Log out.
     *
     * @Given  /^(?:|I )logout$/
     * @return void
     */
    public function iLogOut()
    {
        $page = '/user/logout';
        $this->visitPath($page);
    }

}
