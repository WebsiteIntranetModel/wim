@news @news-view @stability @api
Feature: View News
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View News

  Scenario: As a AN I should be able to see News
    Given I am an anonymous user
    And tags terms:
      | name |
      | TAG1 |
      | TAG2 |
    And I am viewing a "news":
      | title                  | NEWS-TEST-TITLE |
      | body                   | BODY-CONTENT1   |
      | field_publication_date | 2026-06-27      |
      | field_tags             | TAG1, TAG2      |
    Then I should not see the link "Edit"
    And I should not see "BSCPGTEST"
    And I should see "NEWS-TEST-TITLE"
    And I should see "BODY-CONTENT1"
    And I should see "27 June 2026"
    And I should see "TAG1"
    And I should see "TAG2"
