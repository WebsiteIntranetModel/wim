@api @news @news-edit @stability @CM @edit
Feature: Edit News
  Benefit: In order to edit news
  Role: As a CM
  Goal/desire: I want to edit News

  @fixtures
  Scenario: Successfully edit news
    Given "news" content:
      | title       | body          | field_publication_date | field_tags | field_promoted | status |
      | NEWS TITLE1 | BODY-CONTENT1 | 2026-06-27             | Tag1       | 1              | 1      |
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I should not see "Access denied"
    And I select "News" from "type"
    And I press "Filter"
    And I should see "NEWS TITLE1"
    And I click "edit" in the "NEWS TITLE1" row
    Then I should not see "Access denied"
    When I fill in the following:
      | Title    | NEWS TITLE2   |
      | Body     | BODY-CONTENT2 |
      | Tags     | Tag2          |
      | Date     | 06/30/2016    |
      | Promoted | 0             |
    And I press "Save"
    Then I should see the success message "News NEWS TITLE2 has been updated."
    And I click "NEWS TITLE2" in the "NEWS TITLE2" row
    And I should see "NEWS TITLE2"
    And I should see "BODY-CONTENT2"
    And I should see "Tag2"
    And I should not see "NEWS TITLE1"
    And I should not see "Tag1"
    And I should not see "BODY-CONTENT1"
    And I should not see "27 June 2026"
