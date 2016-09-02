@content-manager @security @roles @stability @api
Feature: Content manager role
  Benefit: In order to have permissions manage website
  Role: CONTENT MANAGER
  Goal/desire: Get permissions

  Scenario: Check if content manager has permissions
    Given I am logged in as a "content manager"
    And I am on "admin/people"
    Then I should not see "No access (403)"
    When I am on "admin/content/blocks"
    Then I should not see "No access (403)"
    When I am on "admin/structure/features"
    Then I should see "No access (403)"
    When I am on "admin/people/permissions"
    Then I should see "No access (403)"
    When I am on "admin/modules"
    Then I should see "No access (403)"
    When I am on "admin/config"
    Then I should see "Translate the built in interface and optionally other text."
    Then I should see "Redirect users from one URL to another."
    Then I should see "Configure default behavior of users"
