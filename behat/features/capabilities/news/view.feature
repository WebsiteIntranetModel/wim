@news @news-view @stability @api
Feature: View News
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View News

  Scenario: As a AN I should be able to see News
    Given I am an anonymous user
    And tags terms:
      | name |
      | Tag1 |
      | Tag2 |
    And I am viewing a "news":
      | title                  | NEWS-TEST-TITLE |
      | body                   | BODY-CONTENT1   |
      | field_publication_date | 2026-06-27      |
      | field_tags             | Tag1, Tag2      |
    Then I should not see the link "Edit" in the "Main content"
    And I should not see "BSCPGTEST"
    And I should see "NEWS-TEST-TITLE"
    And I should see "BODY-CONTENT1"
    And I should see "27 June 2026"

  Scenario: As a AN I should see metatags
    Given I am an anonymous user
    When I go to "actual/news/news-metatag-test"
    And I see the metatag "description" with "This is a small description."
    And I see the metatag "keywords" with "keyword1, keyword2"
    And I see the title meta with "Metatag title"
