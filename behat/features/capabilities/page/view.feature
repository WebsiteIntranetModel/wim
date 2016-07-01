@page @page-view @stability @api
Feature: View basic page
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View basic page

  Scenario: As a AN I should be able to see page
    Given I am an anonymous user
    Given I am viewing a "page":
      | title                   | TITLE-ONE           |
      | body                    | BODY-CONTENT1       |
      | field_publication_date  | 2026-06-27 00:00:00 |
    Then I should not see the link "Edit"
    And I should not see "BSCPGTEST"
    And I should see "TITLE-ONE"
    And I should see "BODY-CONTENT1"
    And I should see "27 June 2026"
