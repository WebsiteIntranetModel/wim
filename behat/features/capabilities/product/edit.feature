@product @product-edit @stability @api
Feature: Edit Product
  Benefit: In order to edit product
  Role: As a CM
  Goal/desire: I want to edit Products

  Scenario: Successfully edit product
    Given "product" content:
      | title          | body          | Date       | field_tags | field_promoted | status |
      | PRODUCT TITLE1 | BODY-CONTENT1 | 06/27/2026 | Tag1       | 1              | 1      |
    Given I am logged in as a "content editor"
    When I go to "admin/content"
    And I select "Product" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I click "edit" in the "PRODUCT TITLE1" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | title | PRODUCT TITLE2 |
      | Tags  | Tag2           |
    And I fill in wysiwyg on field Body with "BODY CONTENT2"
    And I click "Publishing options"
    And I fill in the following:
      | Date     | 30/06/2016 |
      | Time     | 05:25:11   |
      | Promoted | 0          |
    And I press "Save"
    And I should see "Product PRODUCT TITLE2 has been updated."
    And I click "PRODUCT TITLE2" in the "PRODUCT TITLE2" row
    And I should see "PRODUCT TITLE2"
    And I should see "BODY CONTENT2"
    And I should not see "PRODUCT TITLE1"
    And I should not see "BODY-CONTENT1"
