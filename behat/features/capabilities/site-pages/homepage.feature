@site-pages @homepage @stability @api
Feature: View homepage
  Benefit: In order to view site homepage
  Role: AN
  Goal/desire: View homepage

  Scenario: As a AN I should be able to see homepage and all blocks
    Given I am an anonymous user
    When I am on the homepage
    Then I should see "Arrange immediately" in the ".region-highlighted" element
    And I should see "News"
    And I should see "Search"
    And I should see an "a.logo" element
