@api @block @product @stability @CM
Feature: Add Product as blocks
  Benefit: In order to add block with Product info
  Role: As a CM
  Goal/desire: I want to add block with Product

  Scenario: CM Successfully add block with Product
    Given I am logged in as a "content manager"
    And I am on "felix-blocks/add?region=secondary&path=agenda&destination=agenda"
    When I click "Nodetype"
    And I click "Product"
    And I click "Introduction"
    And I click "Product 3 with Lead Paragraph"
    Then I should be on "agenda"
    And I should see the link "Product 3 with Lead Paragraph"
    And I should see "Lead paragraph demo content"
