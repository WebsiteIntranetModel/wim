@api @agenda @agenda-edit @stability @CM @edit
Feature: Edit Agenda
  Benefit: In order to edit Agenda
  Role: As a CM
  Goal/desire: I want to edit Agenda

  Scenario: Successfully edit Agenda
    Given I am logged in as a "content editor"
    When I go to "admin/content"
    And I select "Agenda" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I should see "Test Agenda 2"
    And I click "edit" in the "Test Agenda 2" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | Test Agenda Edited 2 |
      | Date  | 30/06/2016           |
      | Time  | 10:00:00             |
      | Tags  | Tag3                 |
    And I fill in wysiwyg on field "Body" with "AGENDA-BODY-CONTENT2"
    And I press "Save"
    Then I should see "Agenda Test Agenda Edited 2 has been updated."
    When I click "Test Agenda Edited 2" in the "Test Agenda Edited 2" row
    Then I should see the heading "Test Agenda Edited 2"
    And I should see "AGENDA-BODY-CONTENT2"
    And I should see "30 June 2016 - 10:00"
    And I should not see "Test Agenda 2"
    And I should not see "Agenda 2 body content."
    And I should not see "06 July 2026 - 08:00"
