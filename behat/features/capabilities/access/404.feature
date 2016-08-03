@access @404 @security @stability @api
Feature: Site 403
  Benefit: In order to view 404 page
  Role: AN
  Goal/desire: View 404 page

  Scenario: Successfully see 404 page
    Given I am an anonymous user
    When I go to "no-such-page"
    Then I should see the heading "Not Found (404)"
