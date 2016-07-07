@api @faq @faq-overview @stability @overview
Feature: FAQ overview
  Benefit: In order to get answers on questions
  Role: As a User
  Goal/desire: I want to see an FAQ

  Scenario: Visitor views a FAQ
    Given "faq" content:
      | title      | body     | status |
      | QUESTION 1 | ANSWER 1 | 1      |
      | QUESTION 2 | ANSWER 2 | 1      |
      | QUESTION 3 | ANSWER 3 | 1      |
      | QUESTION 4 | ANSWER 4 | 1      |
    When I am on "faq"
    Then I should see the heading "FAQ"
    And I should see 4 ".view-display-id-faq_overview .views-row" elements
    When I click "QUESTION 1"
    Then I should see "ANSWER 1"
    And I should not see "ANSWER 2"
    When I click "QUESTION 2"
    And I wait for "5" seconds
    Then I should see "ANSWER 2"
    And I should not see "ANSWER 1"
