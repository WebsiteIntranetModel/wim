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
    And I should see "12 July 2016 - 10:00"
    And I should see "Jodenbreestraat 4"
    And I should see "1011 Amsterdam"
    And I should see "Netherlands"
    And I should see the link "Google Maps"
