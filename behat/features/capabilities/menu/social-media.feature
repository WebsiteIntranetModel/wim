@api @menu @social-media-menu @stability
Feature: View Social Media menu
  Benefit: In order to navigate to social pages
  Role: As a AN
  Goal/desire: I want to view Social Media menu links

  Scenario: As a AN I should be able to see Social Media links
    Given I am an anonymous user
    And I am on the homepage
    Then I should see "Follow us"
