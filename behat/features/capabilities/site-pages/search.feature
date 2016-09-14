@site-pages @search @stability @api
Feature: View search page
  Benefit: In order to view search page
  Role: AN
  Goal/desire: View search page

  Scenario: As a AN I should be able to see search page and search site
    Given I am an anonymous user
    And I am on the homepage
    When I fill in 'lorem' for 'search_block_form' in the "Header"
    And I press "Search"
    Then I should be on "search/site/lorem"
    And I should see ""
    And I should see an "form#search-form" element
    And I should see "Filter by type"
    And I should see "Filter by date"
