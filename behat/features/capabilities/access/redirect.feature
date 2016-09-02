@redirect @security @stability @api
Feature: Redirect pages
  Benefit: In order to add redirects for not existing pages
  Role: CM
  Goal/desire: View redirected page

  Scenario: Add redirect
    Given I am logged in as a "content manager"
    When I go to "node/444"
    Then I should see "Not Found (404)"
    And I should see the link "Add URL redirect from this page to another location"
    Then I click "Add URL redirect from this page to another location"
    And I fill in "To" with "news"
    Then I press "Save"

  Scenario: Successfully see redirected page
    Given I am an anonymous user
    When I go to "node/444"
    Then I should see "News"
    Given I am logged in as a "administrator"
    When I go to "admin/config/search/redirect"
    And I click "Delete" in the "node/444" row
    Then I press "Confirm"