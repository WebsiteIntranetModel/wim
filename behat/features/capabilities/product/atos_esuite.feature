@product @atos-esuite @stability @api
Feature: Check Atos E-Suite fields
  Benefit: All Atos E-Suite fields are in the Product
  Role: As a CM
  Goal/desire: I want to view Atos E-Suite fields

  Scenario: Checking Atos E-Suite fields if exist
    Given I am logged in as a "content moderator"
    And I am on "node/add/product"
    And I click "PCD information"
    When I fill in the following:
      | title                                           | TEST ATOS ESUITE PRODUCT |
      | edit-field-product-related-laws-und-0-title     | Related Law              |
      | edit-field-product-related-laws-und-0-url       | <front>                  |
      | edit-field-product-request-online-und-0-title   | Related Law              |
      | edit-field-product-request-online-und-0-url     | <front>                  |
      | edit-field-product-forms-und-0-title            | Form Link                |
      | edit-field-product-forms-und-0-url              | <front>                  |
      | edit-field-product-more-information-und-0-title | More info Link           |
      | edit-field-product-more-information-und-0-url   | <front>                  |
    And I click "Additional Information"
    Then I should see "ATTACHMENT"
    And I fill in wysiwyg on field Request with "Request Content"
    And I fill in wysiwyg on field Contact with "Contact Content"
    And I fill in wysiwyg on field Objection with "Objection Content"
    And I fill in wysiwyg on field Costs with "Costs Content"
    And I fill in wysiwyg on field Particulars with "Particulars Content"
    And I fill in wysiwyg on field Period with "Period Content"
    And I fill in wysiwyg on field Conditions with "Conditions Content"
    And I click "Relations"
    And I fill in the autocomplete "Related FAQ items" with "Question 2" and click "Question 2"
    And I fill in the autocomplete "Related Product items" with "Product 2" and click "Product 2"
    Then I press "Save"
    Then I should see the success message "Product TEST ATOS ESUITE PRODUCT has been created."
    And I should see the link "Related Law"
    And I should see the link "Form Link"
    And I should see the link "More info Link"
    And I should see the link "Question 2"
    And I should not see the link "Product 2"
    And I should see "Request Content"
    And I should see "Contact Content"
    And I should see "Objection Content"
    And I should see "Costs Content"
    And I should see "Particulars Content"
    And I should see "Period Content"
    And I should see "Conditions Content"
