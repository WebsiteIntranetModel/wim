@breadcrumbs @stability @api
Feature: View site breadcrumbs
  Benefit: In order to view site breadcrumbs and see pages links
  Role: AN
  Goal/desire: View breadcrumbs

  Scenario: As a AN I should be able to see breadcrumbs on pages
    Given I am an anonymous user
    When I am on the homepage
    Then I should not see an ".breadcrumb" element
    When I click "Actual"
    Then I should see "Home / Actual / News"
    And I click "Lorem ipsum dolor sit 5"
    Then I should see "Home / Actual / News / Lorem ipsum dolor sit 5"
    When I click "FAQ"
    Then I should see "Home / FAQ"
    And I click "Security"
    And I should see "Home / FAQ / Security"
