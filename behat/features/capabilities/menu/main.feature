@api @menu @main-menu @stability
Feature: View Main menu
  Benefit: In order to navigate site pages
  Role: As a AN
  Goal/desire: I want to view Main menu links

  Scenario: As a AN I should be able to see Main menu links
    Given I am an anonymous user
    And I am on the homepage
    Then I should see the link "Home" in the "Header"
    When I click "Home" in the "Header"
    Then I should be on the homepage
    When I click "Actual" in the "Header"
    Then I should be on "news"
    When I mouseover the link "Actual" in the "Header"
    And I should see the link "News"
    And I should see the link "Agenda"
