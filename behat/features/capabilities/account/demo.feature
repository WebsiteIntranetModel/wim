@account-demo @security @stability @api
Feature: Demo accounts
  Benefit: In order to perform other tests
  Role: ADMIN
  Goal/desire: See demo users

  Scenario: Check if demo users are there
    Given I am logged in as a "administrator"
    And I am on "admin/people"
    Then I should see the text "active" in the "webmaster" row
    And I should see the text "webmaster" in the "webmaster" row
    And I should see the text "active" in the "cm" row
    And I should see the text "content manager" in the "cm" row
    And I should see the text "active" in the "ce" row
    And I should see the text "content editor" in the "ce" row
    And I should see the text "active" in the "test" row
    And I should see the text "active" in the "klark_kent" row
    And I should see the text "administrator" in the "klark_kent" row
