@taxonomy @security @stability @api
Feature: Taxonomy pages
  Benefit: In order restrict access for some pages on the site
  Role: CM
  Goal/desire: View taxonomy page

  Scenario: Successfully see access denied page for taxonomy
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | content_manager |
      | Password | content_manager |
    And I press "Log in"
    Then I should see "content_manager"
    Given I am viewing a "Tags" term with the name "SUPERTAG"
    Then I should see "No access (403)"

