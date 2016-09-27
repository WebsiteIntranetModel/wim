@api @menu @top-tasks-menu @stability
Feature: View Top Tasks menu
  Benefit: In order to navigate top tasks
  Role: As a AN
  Goal/desire: I want to view Top Tasks menu links

  Scenario: As a AN I should be able to see Top Tasks links
    Given I am an anonymous user
    And I am on the homepage
    Then I should see "Arrange immediately" in the "Highlighted"
    And I should see "Leisure" in the "Highlighted"
    And I should see "Waste" in the "Highlighted"
    When I click "#block-menu-menu-top-tasks li.first" element
    Then I should see the link "Make an appointment" in the "Highlighted"
    When I click "Make an appointment" in the "Highlighted"
    Then I should be on the homepage
