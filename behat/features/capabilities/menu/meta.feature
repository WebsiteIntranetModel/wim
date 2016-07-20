@api @menu @meta-menu @stability
Feature: View Meta menu
  Benefit: In order to navigate site pages
  Role: As a AN
  Goal/desire: I want to view Meta menu links

  Scenario: As a AN I should be able to see Meta menu links
    Given I am an anonymous user
    And I am on the homepage
    Then I should see the link "Home" in the "Meta left"
    When I click "Home" in the "Meta left"
    Then I should be on the homepage
    