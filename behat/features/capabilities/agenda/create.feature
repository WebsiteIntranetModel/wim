@api @agenda @agenda-create @stability @CM @create
Feature: Create Agenda
  Benefit: In order to add Agenda
  Role: As a CM
  Goal/desire: I want to create Agenda

  Scenario: Successfully create Agenda
    Given I am logged in as a "content editor"
    And I am on "node/add/agenda"
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title         | TEST AGENDA            |
      | Date          | 30/06/2016             |
      | Time          | 10:00:00               |
      | Location name | Rembrandt House Museum |
      | Street        | Jodenbreestraat 4      |
      | City          | Amsterdam              |
      | Postal code   | 1011                   |
      | Tags          | Tag1, Tag2             |
    And I fill in wysiwyg on field Body with "TEST AGENDA BODY"
    And I click "Introduction"
    And I fill in wysiwyg on field "Lead paragraph" with "Lead paragraph demo content"
    And I click "Publishing options"
    And I fill in the following:
      | Promoted | 0 |
    And I click "Browse"
    Then I wait for AJAX to finish
    And I wait for 5 seconds
    And I switch to the iframe "mediaBrowser"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Upload a new file"
    And I press "Next"
    Then I press "Save"
    When I switch back from an iframe
    And I select "Netherlands" from "Country"
    And I wait for AJAX to finish
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    Then I should see the success message "Agenda TEST AGENDA has been created."
    And I should see the heading "TEST AGENDA"
    And I should see "TEST AGENDA BODY"
    And I should see "Share"
    Then the url should match "/agenda/test-agenda"

    Given I am an anonymous user
    And I visit "node/add/agenda"
    Then I should see "No access (403)"
