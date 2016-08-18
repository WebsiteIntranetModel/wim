@account @login @security @stability @api
Feature: Login
  Benefit: In order to participate
  Role: AN
  Goal/desire: Log in with my username

  @critical
  Scenario: Successfully login with username
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
        | Username | admin |
        | Password | admin |
    And I press "Log in"
    Then I should see "admin"
