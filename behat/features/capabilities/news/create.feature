@api @news @news-create @stability @CM @create
Feature: Create News
  Benefit: In order to add news
  Role: As a CM
  Goal/desire: I want to create News

  Scenario: Successfully create news
    Given I am logged in as a "content moderator"
    And I am on "node/add/news"
    Then I should not see "Access denied"
    And I click "Edit summary"
    When I fill in the following:
      | Title    | TEST NEWS    |
      | Date     | 06/30/2016   |
      | Time     | 02:22:00     |
      | Summary  | SUMMARY-TEXT |
      | Body     | BODY CONTENT |
      | Tags     | Tag1, Tag2   |
      | Promoted | 1            |
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I attach the file "/fixtures/files/pdf-file.pdf" to "Add a new file"
    And I press "Save"
    Then I should see the success message "News TEST NEWS has been created."
    And I should see the heading "TEST NEWS"
    And I should see "BODY CONTENT"
    And I should see "30 June 2016"
    And I should see "Tag1"
    And I should see an ".field-name-field-image img" element
    And I should see "pdf-file.pdf"

    Given I am an anonymous user
    And I visit "node/add/news"
    Then I should see the heading "Access denied"

  Scenario: Successfully set category for news
    Given I am logged in as a "content moderator"
    And news_categories terms:
      | name      |
      | CATEGORY1 |
      | CATEGORY2 |
    And I am on "node/add/news"
    Then I should not see "Access denied"
    When I fill in the following:
      | Title | TEST CATEGORY NEWS |
      | Date  | 06/30/2016         |
      | Time  | 04:00:00           |
      | Body  | BODY CONTENT       |
    And I select "CATEGORY1" from "Category"
    Then I press "Save"
    And I should see the success message "News TEST CATEGORY NEWS has been created."
    And I should see the link "Edit"
    When I click "Edit"
    And the "CATEGORY1" option from "Category" is selected
    And the "CATEGORY2" option from "Category" is not selected
