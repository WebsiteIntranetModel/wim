@api @block @editorial @stability @CM
Feature: Add Editorial blocks
  Benefit: In order to create Editorial blocks
  Role: As a CM
  Goal/desire: I want to create Editorial blocks on the site

  Scenario: Successfully create Editorial block
    Given I am logged in as a "content moderator"
    And I am on "block/add/editorial"
    When I fill in the following:
      | Label | TEST EDITORIAL       |
      | Title | TEST EDITORIAL TITLE |
      | Body  | TEST EDITORIAL BODY  |
      | URL   | <front>              |
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I select "Default" from "View Mode"
    And I press "Save"
    Then I should see the success message "Editorial TEST EDITORIAL TITLE has been created."
