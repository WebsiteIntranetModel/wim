@webform @stability @api
Feature: Create form on site
  Benefit: In order to create forms on site
  Role: CM
  Goal/desire: Create forms

  Scenario: Successfully create webforms
    Given I am logged in as a "content editor"
    And I am at "node/add/webform"
    When I fill in the following:
      | Title | Test Webform |
      | Tags  | Tag1         |
    And I fill in wysiwyg on field Body with "Body description text"
    Then I press "Save"
    And I should see "Webform Test Webform has been created."
    Then I click "Conditionals"
    And I click "E-mails"
    And I click "Form settings"
