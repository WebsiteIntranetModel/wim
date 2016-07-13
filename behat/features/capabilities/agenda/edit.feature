@api @agenda @agenda-edit @stability @CM @edit
Feature: Edit Agenda
  Benefit: In order to edit Agenda
  Role: As a CM
  Goal/desire: I want to edit Agenda

  Scenario: Successfully edit Agenda
    Given "agenda" content:
      | title         | body                 | status | Date       | Time  |
      | AGENDA TITLE1 | AGENDA-BODY-CONTENT1 | 1      | 06/27/2026 | 10:00 |
    And I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I should not see "Access denied"
    And I should see "AGENDA TITLE1"
    And I click "edit" in the "AGENDA TITLE1" row
    Then I should not see "Access denied"
    When I fill in the following:
      | Title | AGENDA TITLE2        |
      | Body  | AGENDA-BODY-CONTENT2 |
      | Date  | 06/30/2016           |
      | Time  | 10:00                |
    And I press "Save"
    Then I should see the success message "Agenda AGENDA TITLE2 has been updated."
    When I click "AGENDA TITLE2" in the "AGENDA TITLE2" row
    Then I should see the heading "AGENDA TITLE2"
    And I should see "AGENDA-BODY-CONTENT2"
    And I should not see "AGENDA TITLE1"
    And I should not see "AGENDA-BODY-CONTENT1"
    And I should not see "27 June 2026"
