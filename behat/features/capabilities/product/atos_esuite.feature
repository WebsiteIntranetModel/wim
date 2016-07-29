@product @atos-esuite @stability @api
Feature: Check Atos E-Suite fields
  Benefit: All Atos E-Suite fields are in the Product
  Role: As a CM
  Goal/desire: I want to view Atos E-Suite fields

  Scenario: Checking Atos E-Suite fields if exist
    Given I am logged in as a "content moderator"
    And I am on "node/add/product"
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
    And I fill in the autocomplete "Related FAQ items" with "Question 1" and click "Question 1"
    And I fill in the autocomplete "Related Product items" with "Product 1" and click "Product 1"
    When I fill in the following:
      | Request     | Request Content     |
      | Contact     | Contact Content     |
      | Objection   | Objection Content   |
      | Costs       | Costs Content       |
      | Particulars | Particulars Content |
      | Period      | Period Content      |
      | Conditions  | Conditions Content  |
    Then I press "Save"
    Then I should see the success message "Product TEST ATOS ESUITE PRODUCT has been created."
    And I should see the link "Related Law"
    And I should see the link "Form Link"
    And I should see the link "More info Link"
    And I should see the link "Question 1"
    And I should not see the link "Product 1"
    And I should see "Request Content"
    And I should see "Contact Content"
    And I should see "Objection Content"
    And I should see "Costs Content"
    And I should see "Particulars Content"
    And I should see "Period Content"
    And I should see "Conditions Content"
