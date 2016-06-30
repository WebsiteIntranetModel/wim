@api @news @stability
Feature: Create News
  Benefit: In order to add news
  Role: As a CM
  Goal/desire: I want to create News

  @CM @perfect @critical
  Scenario: Successfully create news
    Given I am logged in as a "Content Moderator"
    And I am on "node/add/news"
    When I fill in the following:
      | Title | Test news        |
      | Date  | 06/30/2016       |
      | Body  | Body description |
      | Tags  | tag1, tag2       |
    And I press "Save"
    Then I should see the success message "News Test news has been created."
    And I should see the heading "Test news"
    And I should see "Body description"
    And I should see "Thursday, June 30, 2016"
    And I should see "tag1"

    Given I am an anonymous user
    And I visit "node/add/news"
    Then I should see the heading "Access denied"

  Scenario: Node edit access by Content Moderator
    Given I am logged in as a "Content Moderator"
    And I am viewing a "News" with the title "Test news"
    Then I should see the link "Edit"
    When I click "Edit"
    Then I should see "Edit News Test news"

  Scenario: Node edit access by anonymous
    Given I am an anonymous user
    And I am viewing a "News" with the title "Test news"
    Then I should not see the link "Edit"
