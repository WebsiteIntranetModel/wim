@api @block @page @stability @CM
Feature: Add Basic page as blocks
  Benefit: In order to add block with Basic page info
  Role: As a CM
  Goal/desire: I want to add block with Basic page

  Scenario: CM Successfully add block with Basic page
    Given I am logged in as a "content manager"
    And I am on "felix-blocks/add?region=primary&path=agenda&destination=agenda"
    When I click "Nodetype"
    And I click "Basic page"
    And I click "Introduction"
    And I click "Test page with Lead Paragraph"
    Then I should be on "agenda"
    And I should see the link "Test page with Lead Paragraph"
    And I should see "Lead paragraph demo content"
