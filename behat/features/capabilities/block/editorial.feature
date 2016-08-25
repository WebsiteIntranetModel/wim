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
      | URL   | <front>              |
    And I fill in wysiwyg on field Body with "TEST EDITORIAL BODY"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I select "Default" from "View Mode"
    And I press "Save"
    Then I should see the success message "Editorial TEST EDITORIAL TITLE has been created."

  Scenario: Successfully add editorial block with view mode via Felix
    Given I am logged in as a "content moderator"
    And I am on "felix-blocks/add?region=primary&path=node&destination=node"
    When I click "Editorial Test label 1"
    Then I select "Default" from "View mode"
    And I press the "Save" button
    When I mouseover the ".region-sidebar-first .block-bean h2" element
    Then I click the ".region-sidebar-first .block-bean a.contextual-links-trigger" element
    And I click the ".region-sidebar-first .block-bean .contextual-links-wrapper li.remove" element
    And I press the "Remove" button