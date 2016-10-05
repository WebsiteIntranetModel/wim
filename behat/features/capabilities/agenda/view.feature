@agenda @agenda-view @stability @api
Feature: View Agenda
  Benefit: In order to view Agenda on the site
  Role: AN
  Goal/desire: View Agenda

  Scenario: As a AN I should be able to see Agenda
    Given I am an anonymous user
    And I am viewing "agenda" node with the title "Test Agenda 1"
    Then I should see the heading "Test Agenda 1"
    And I should see "Rembrandt House Museum"
    And I should see "12 July 2017 - 10:00"
    And I should see "Jodenbreestraat 4"
    And I should see "1011 Amsterdam"
    And I should see "Netherlands"
    And I should see the link "Google Maps"

  Scenario: As a AN I should see metatags
    Given I am an anonymous user
    When I go to "agenda/agenda-metatag-test"
    And I see the metatag "description" with "This is a small description."
    And I see the metatag "keywords" with "keyword1, keyword2"
    And I see the title meta with "Metatag title"
