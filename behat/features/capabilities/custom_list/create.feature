@api @custom_list @CM @create
Feature: Create Custom List
  Benefit: In order to create a Custom List
  Role: As a CM
  Goal/desire: I want to create a Custom List

  Scenario: Successfully create a Custom List block
    Given I am logged in as a "content manager"
    And I am on "admin/structure/lists/add"
    Then I should not see "No access (403)"
    When I fill in the following:
      | Administration title | TEST CUSTOM LIST BLOCK |
      | Title                | TEST CUSTOM LIST BLOCK |
    And I check the box "Provide block"
    And I uncheck the box "Provide page"
    And I press "Save"
    Then I should see the success message "The list has been added."
    And I should see "TEST CUSTOM LIST BLOCK"
