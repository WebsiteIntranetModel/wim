@api @faq @faq-overview @stability @overview
Feature: FAQ overview
  Benefit: In order to get answers on questions
  Role: As a User
  Goal/desire: I want to see an FAQ

  Scenario: Visitor views a FAQ
    Given faq_categories terms:
      | name          |
      | FAQ-CATEGORY1 |
      | FAQ-CATEGORY2 |
    And "faq" content:
      | title      | body     | status | field_show_on_overview | field_faq_category |
      | QUESTION 1 | ANSWER 1 | 1      | 1                      | FAQ-CATEGORY1      |
      | QUESTION 2 | ANSWER 2 | 1      | 1                      | FAQ-CATEGORY1      |
      | QUESTION 3 | ANSWER 3 | 1      | 1                      | FAQ-CATEGORY2      |
      | QUESTION 4 | ANSWER 4 | 1      | 1                      | FAQ-CATEGORY2      |
    When I am on "faq"
    Then I should see the heading "FAQ"
    And I should see "Select a category."
    When I click "FAQ-CATEGORY1"
    Then I should see "Back to categories"
    And I should see "FAQ-CATEGORY1"
    And I should see "QUESTION 1"
    And I should not see "QUESTION 3"
    When I click "QUESTION 1"
    Then I wait for "5" seconds
    And I should see "ANSWER 1"
    And I should not see "ANSWER 2"

  Scenario: CM mark FAQ items to show them on the overview
    Given faq_categories terms:
      | name          |
      | FAQ-CATEGORY1 |
      | FAQ-CATEGORY2 |
    And "faq" content:
      | title      | body     | status | field_show_on_overview | field_faq_category |
      | QUESTION 1 | ANSWER 1 | 1      | 1                      | FAQ-CATEGORY1      |
      | QUESTION 2 | ANSWER 2 | 1      | 1                      | FAQ-CATEGORY2      |
    And I am on "faq"
    When I click "FAQ-CATEGORY1"
    Then I should see "QUESTION 1"
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I click "edit" in the "QUESTION 1" row
    And I uncheck the box "Show this FAQ in the FAQ overview"
    And I press "Save"
    When I go to "faq"
    Then I click "FAQ-CATEGORY1"
    Then I should not see "QUESTION 1"
