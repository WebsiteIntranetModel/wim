@api @block @felix @stability @CM
Feature: Add blocks via Felix
  Benefit: In order to add blocks to regions
  Role: As a CM
  Goal/desire: I want to add block on the site

  Scenario: Successfully add block
    Given I am logged in as a "content moderator"
    When I am on the homepage

    #Sidebar first
    And I should see "Sidebar First" in the "Sidebar first"
    When I mouseover the ".region-sidebar-first .block-felix" element
    Then I should see an ".region-sidebar-first .block-felix .contextual-links-trigger-active" element

    #Content Top
    And I should see "Content Top" in the "Content Top"
    When I mouseover the ".region-content-top .block-felix" element
    Then I should see an ".region-content-top .block-felix .contextual-links-trigger-active" element

    #Content
    And I should see "Content" in the "Content"
    When I mouseover the ".region-content .block-felix" element
    Then I should see an ".region-content .block-felix .contextual-links-trigger-active" element

    #Content Bottom
    And I should see "Content Bottom" in the "Content Bottom"
    When I mouseover the ".region-content-bottom .block-felix" element
    Then I should see an ".region-content-bottom .block-felix .contextual-links-trigger-active" element

    #Highlighted
    And I should see "Highlighted" in the "Highlighted"
    When I mouseover the ".region-highlighted .block-felix" element
    Then I should see an ".region-highlighted .block-felix .contextual-links-trigger-active" element

    #Sidebar Second
    And I should see "Sidebar Second" in the "Sidebar second"
    When I mouseover the ".region-sidebar-second .block-felix" element
    Then I should see an ".region-sidebar-second .block-felix .contextual-links-trigger-active" element

    #Footer First
    And I should see "Footer First" in the "Footer First"
    When I mouseover the ".region-footer-first .block-felix" element
    Then I should see an ".region-footer-first .block-felix .contextual-links-trigger-active" element

    #Footer Second
    And I should see "Footer Second" in the "Footer Second"
    When I mouseover the ".region-footer-second .block-felix" element
    Then I should see an ".region-footer-second .block-felix .contextual-links-trigger-active" element

    #Footer Third
    And I should see "Footer Third" in the "Footer Third"
    When I mouseover the ".region-footer-third .block-felix" element
    Then I should see an ".region-footer-third .block-felix .contextual-links-trigger-active" element

    When I go to "felix-blocks/add?region=primary&path=node&destination=node"
    Then I click "Test block 1"
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
