@product @product-edit @stability @api
Feature: Edit Product
  Benefit: In order to edit product
  Role: As a CM
  Goal/desire: I want to edit Products

  Scenario: Successfully edit product
    Given "product" content:
      | title          | body          | Date       | field_tags | field_promoted | status |
      | PRODUCT TITLE1 | BODY-CONTENT1 | 06/27/2026 | Tag1       | 1              | 1      |
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    And I select "Product" from "type"
    And I press "Filter"
    And I click "edit" in the "PRODUCT TITLE1" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | title    | PRODUCT TITLE2 |
      | Body     | BODY-CONTENT2  |
      | Tags     | Tag2           |
      | Date     | 06/30/2016     |
      | Time     | 05:25:11       |
      | Promoted | 0              |
    And I press "Save"
    And I should see the success message "Product PRODUCT TITLE2 has been updated."
    And I click "PRODUCT TITLE2" in the "PRODUCT TITLE2" row
    And I should see "30 June 2016"
    And I should see "PRODUCT TITLE2"
    And I should see "BODY-CONTENT2"
    And I should not see "PRODUCT TITLE1"
    And I should not see "BODY-CONTENT1"
    And I should not see "27 June 2026"
