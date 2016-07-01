 @product @product-create @stability @api
Feature: Create Product
  Benefit: In order to add products
  Role: As a CM
  Goal/desire: I want to create Products

  Scenario: Successfully create product
    Given I am logged in as a "content moderator"
    And I am on "node/add/product"
    Then I should not see "Access denied"
    And I should see "Promoted"
    And I should see "Image"
    When I fill in the following:
      | Title | TEST PRODUCT |
      | Date  | 06/27/2026   |
      | Body  | BODY CONTENT |
      | Tags  | TAG1, TAG2   |
    And I press "Save"
    Then I should see the success message "Product TEST PRODUCT has been created."
    And I should see the heading "TEST PRODUCT"
    And I should see "BODY CONTENT"
    And I should see "Saturday, June 27, 2026"
    And I should see "TAG1"
    And I should see "TAG2"

    Given I am an anonymous user
    And I visit "node/add/product"
    Then I should see the heading "Access denied"
