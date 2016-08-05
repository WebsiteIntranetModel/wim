@subject-page @subject-page-view @stability @api
Feature: View subject page
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View subject page

  Scenario: As a AN I should be able to see page
    Given I am an anonymous user
    Given I am viewing a "Subject page":
      | title                  | TITLE-ONE           |
      | body                   | BODY-CONTENT1       |
      | field_publication_date | 2026-06-27 00:00:00 |
    Then I should not see the link "Edit" in the "Main content"
    And I should see "TITLE-ONE"
    And I should see "BODY-CONTENT1"
    And I should not see "27 June 2026"
