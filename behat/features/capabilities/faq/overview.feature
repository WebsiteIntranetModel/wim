@api @faq @faq-overview @stability @overview
Feature: FAQ overview
  Benefit: In order to get answers on questions
  Role: As a User
  Goal/desire: I want to see an FAQ

  Scenario: Visitor views a FAQ
    Given "faq" content:
      | title      | body     | status | field_show_on_overview |
      | QUESTION 1 | ANSWER 1 | 1      | 1                      |
      | QUESTION 2 | ANSWER 2 | 1      | 1                      |
      | QUESTION 3 | ANSWER 3 | 1      | 1                      |
      | QUESTION 4 | ANSWER 4 | 1      | 1                      |
    When I am on "faq"
    Then I should see the heading "FAQ"
    When I click "QUESTION 1"
    And I wait for "5" seconds
    Then I should see "ANSWER 1"
    And I should not see "ANSWER 2"
    When I click "QUESTION 2"
    And I wait for "5" seconds
    Then I should see "ANSWER 2"
    And I should not see "ANSWER 1"

  Scenario: CM mark FAQ items to show them on the overview
    Given "faq" content:
      | title      | body     | status | field_show_on_overview |
      | QUESTION 1 | ANSWER 1 | 1      | 1                      |
    When I am on "faq"
    Then I should see "QUESTION 1"
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I click "edit" in the "QUESTION 1" row
    And I uncheck the box "Show this FAQ in the FAQ overview"
    And I press "Save"
    When I go to "faq"
    Then I should not see "QUESTION 1"
