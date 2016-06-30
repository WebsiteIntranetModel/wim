@api @news @stability @CM @create
Feature: Create News
  Benefit: In order to add news
  Role: As a CM
  Goal/desire: I want to create News

  Scenario: Successfully create news
    Given I am logged in as a "content moderator"
    And I am on "node/add/news"
    Then I should see "Category"
    Then I should see "Promoted"
    Then I should see "Add a new file"
    Then I should see "Image"
    When I fill in the following:
      | Title | TEST NEWS    |
      | Date  | 06/30/2016   |
      | Body  | BODY CONTENT |
      | Tags  | tag1, tag2   |
    And I press "Save"
    Then I should see the success message "News TEST NEWS has been created."
    And I should see the heading "TEST NEWS"
    And I should see "BODY CONTENT"
    And I should see "Thursday, June 30, 2016"
    And I should see "tag1"

    Given I am an anonymous user
    And I visit "node/add/news"
    Then I should see the heading "Access denied"
