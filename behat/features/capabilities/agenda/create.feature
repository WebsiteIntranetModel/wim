@api @agenda @agenda-create @stability @CM @create
Feature: Create Agenda
  Benefit: In order to add Agenda
  Role: As a CM
  Goal/desire: I want to create Agenda

  Scenario: Successfully create Agenda
    Given I am logged in as a "content moderator"
    And I am on "node/add/agenda"
    Then I should not see "Access denied"
    When I fill in the following:
      | Title         | TEST AGENDA            |
      | Body          | TEST AGENDA BODY       |
      | Date          | 06/30/2016             |
      | Time          | 10:00:00               |
      | Location name | Rembrandt House Museum |
      | Street        | Jodenbreestraat 4      |
      | City          | Amsterdam              |
      | Postal code   | 1011                   |
      | Tags          | Tag1, Tag2             |
      | Promoted      | 0                      |
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I select "Netherlands" from "Country"
    And I wait for AJAX to finish
    And I press "Save"
    Then I should see the success message "Agenda TEST AGENDA has been created."
    And I should see the heading "TEST AGENDA"
    And I should see "TEST AGENDA BODY"

    Given I am an anonymous user
    And I visit "node/add/agenda"
    Then I should see "Access denied"
