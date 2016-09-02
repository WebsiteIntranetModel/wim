@api @block @felix @stability @CM
Feature: Add blocks via Felix
  Benefit: In order to add blocks to regions
  Role: As a CM
  Goal/desire: I want to add block on the site

  Scenario: Successfully add block
    Given I am logged in as a "content manager"
    When I am on the homepage

    #Sidebar first
    And I should see "Sidebar First" in the "Sidebar first"

    #Content
    And I should see "Content" in the "Content"

    #Content Bottom
    And I should see "Content Bottom" in the "Content Bottom"

    #Highlighted
    And I should see "Highlighted" in the "Highlighted"

    #Sidebar Second
    And I should see "Sidebar Second" in the "Sidebar second"

    #Footer
    And I should see "Footer" in the "Footer"

    When I go to "felix-blocks/add?region=primary&path=node&destination=node"
    Then I click "Block"
    And I click "Test block 1"
    And I fill in "Subject" with "Felix test block"
    And I select "1/2 of page" from "Bootstrap layout"
    And I check the box "New row"
    When I press the "Save" button
    Then I should see the success message "Succesfully added a new block to the region Sidebar First."
    And I should see "Felix test block" in the "Sidebar first"
    When I mouseover the ".region-sidebar-first .block-block h2" element
    Then I click the ".region-sidebar-first .block-block a.contextual-links-trigger" element
    And I click the ".region-sidebar-first .block-block .contextual-links-wrapper li.remove" element
    And I press the "Remove" button
    And I should not see "Felix test block" in the "Sidebar first"
