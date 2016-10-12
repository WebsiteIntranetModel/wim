@api @faq @faq-overview @stability @overview
Feature: FAQ overview
  Benefit: In order to get answers on questions
  Role: As a User
  Goal/desire: I want to see an FAQ

  Scenario: Visitor views a FAQ
    Given I am on "faq"
    Then I should see the heading "FAQ"
    And I should see "Select a category."
    And I should see "Information"
    And I should not see "Other"
    When I click "Security"
    Then I should see "Back to categories"
    And I should see "Security"
    And I should see "Question 3"
    And I should see "Question 4"
    And I should not see "Question 2"
    When I click "Question 3"
    Then I wait for "5" seconds
    And I should see "Answer for 3 Question"
    And I should not see "Answer for 4 Question"

  Scenario: CM mark FAQ items to show them on the overview
    Given I am on "faq"
    When I click "Security"
    Then I should not see "Question 2"

    Given I am logged in as a "content manager"
    When I go to "admin/content"
    And I select "FAQ" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I should see "item(s) found"
    And I click "edit" in the "Question 2" row
    And I check the box "Show this FAQ in the FAQ overview"
    And I press "Save"
    When I go to "faq"
    Then I click "Security"
    Then I should see "Question 2"
