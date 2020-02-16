@webmaster @security @roles @stability @api
Feature: Webmaster role
  Benefit: In order to have permissions manage website
  Role: WEBMASTER
  Goal/desire: Get permissions

  Scenario: Check if webmaster has permissions
    Given I am logged in as a "webmaster"
    And the cache has been cleared
    And I am on "admin/people"
    Then I should not see "No access (403)"
    When I am on "admin/content/blocks"
    Then I should not see "No access (403)"
    When I am on "admin/structure/features"
    Then I should see "No access (403)"
    And I should not see "Create feature"
    When I am on "admin/people/permissions"
    Then I should see "No access (403)"
    When I am on "admin/structure/views"
    Then I should see "No access (403)"
    When I am on "admin/modules"
    Then I should see "No access (403)"
    When I am on "admin/config"
    Then I should see "Atos import settings."
    Then I should see "Administer Auto Logout settings."
    Then I should see "Configure default behavior of users"
    Then I should see "Redirect users from one URL to another."
