@product @product-create @stability @api
Feature: Create Product
  Benefit: In order to add products
  Role: As a CM
  Goal/desire: I want to create Products

  Scenario: Successfully create product
    Given I am logged in as a "content editor"
    And I am on "node/add/product"
    Then I should not see "No access (403)"
    And I should see "Image"
    When I fill in the following:
      | title | TEST PRODUCT |
      | Tags  | Tag1, Tag2   |
    And I fill in wysiwyg on field Body with "BODY CONTENT"
    And I click "Publishing options"
    And I should see "Promoted"
    And I fill in the following:
      | Date | 27/06/2026 |
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    Then I should see the success message "Product TEST PRODUCT has been created."
    And I should see the heading "TEST PRODUCT"
    And I should see "BODY CONTENT"
    And I should see "Share"
    Then the url should match "/product/test-product"

    Given I am an anonymous user
    And I visit "node/add/product"
    Then I should see the heading "No access (403)"
