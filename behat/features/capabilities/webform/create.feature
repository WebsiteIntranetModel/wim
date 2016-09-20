@webform @stability @api
Feature: Create form on site
  Benefit: In order to create forms on site
  Role: CM
  Goal/desire: Create forms

  Scenario: Successfully create webforms
    Given I am logged in as a "content manager"
    And I am at "node/add/webform"
    When I fill in the following:
      | Title | Test Webform |
      | Tags  | Tag1         |
    And I fill in wysiwyg on field Body with "Body description text"
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    Then I press "Save"
    And I should see "Webform Test Webform has been created."
    Then I click "Conditionals"
    And I click "E-mails"
    And I click "Form settings"
