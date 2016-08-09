@api @agenda @agenda-overview @stability @overview
Feature: Agenda overview
  Benefit: In order to find more information
  Role: As a User
  Goal/desire: I want to see an Agenda overview

  Scenario: Visitor views a agenda overview
    Given I am an anonymous user
    When I am on "agenda"
    Then I should see the heading "Agenda"
    And I should not see "No results"
    And the ".region-content article.node-teaser" element should contain "Read more"
    And the ".region-content .views-row-1 article.node-teaser" element should contain "Test Agenda 4"
    And I should see "Test Agenda 1"
    And I should not see "Test Agenda 3"
