@api @news @news-edit @stability @CM @edit
Feature: Edit News
  Benefit: In order to edit news
  Role: As a CM
  Goal/desire: I want to edit News

  Scenario: Successfully edit news
    Given "news" content:
      | title       | body          | field_publication_date | field_tags | field_promoted | status |
      | NEWS TITLE1 | BODY-CONTENT1 | 2026-06-27             | Tag1       | 1              | 1      |
    Given I am logged in as a "content editor"
    When I go to "admin/content"
    And I select "News" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I should see "NEWS TITLE1"
    And I click "edit" in the "NEWS TITLE1" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | NEWS TITLE2   |
      | Tags  | Tag2          |
    And I fill in wysiwyg on field Body with "BODY-CONTENT2"
    And I click "Publishing options"
    And I uncheck the box "Promoted"
    And I fill in the following:
      | Date     | 30/06/2016 |
      | Time     | 11:23:00   |
      | Promoted | 0          |
    And I press "Save"
    Then I should see "News NEWS TITLE2 has been updated."
    And I click "NEWS TITLE2" in the "NEWS TITLE2" row
    And I should see "NEWS TITLE2"
    And I should see "BODY-CONTENT2"
    And I should not see "NEWS TITLE1"
    And I should not see "BODY-CONTENT1"
    And I should not see "27 June 2026"
