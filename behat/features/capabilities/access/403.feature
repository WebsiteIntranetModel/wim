@access @403 @security @stability @api
Feature: Site 403
  Benefit: In order to view 403 page
  Role: AN
  Goal/desire: View 403 page

  Scenario: Successfully see 403 page
    Given I am an anonymous user
    When I go to "admin"
    Then I should see the heading "No access (403)"
