@cookie @homepage @stability @api
Feature: View cookie message
  Benefit: In order to view cookie message
  Role: AN
  Goal/desire: View and accept cookie message

  Scenario: As a AN I should be able to see cookie message and able to accept this message
    Given I am an anonymous user
    When I am on the homepage
    Then I should see "Your experience on this site will be improved by allowing cookies"
    And I should see "Allow cookies"
    And I click "Allow cookies"
    Then I should not see "Your experience on this site will be improved by allowing cookies"
    When I reload the page
    Then I should not see "Your experience on this site will be improved by allowing cookies"
