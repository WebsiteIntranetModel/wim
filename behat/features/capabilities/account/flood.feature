@flood @security @stability @api
Feature: Block flood
  Benefit: In order to block unwanted flood
  Role: USER
  Goal/desire: Prevent password brute-force

  Scenario: Check if user are locked after 5 wrong attempt to login
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should see "Sorry, unrecognized username or password."
    And I should not see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should see "Sorry, unrecognized username or password."
    And I should not see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should see "Sorry, unrecognized username or password."
    And I should not see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should see "Sorry, unrecognized username or password."
    And I should not see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should see "Sorry, unrecognized username or password."
    And I should not see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
    And I fill in the following:
      | Username | floodmaster   |
      | Password | wrongpassword |
    And I press "Log in"
    Then I should not see "Sorry, unrecognized username or password."
    And I should see "Sorry, there have been more than 5 failed login attempts for this account. It is temporarily blocked."
