@api @faq @faq-create @stability @CM @create
Feature: Create FAQ
  Benefit: In order to add FAQ item
  Role: As a CM
  Goal/desire: I want to create FAQ

  Scenario: Successfully create FAQ
    Given I am logged in as a "content editor"
    And I am on "node/add/faq"
    Then I should not see "No access (403)"
    When I fill in the following:
      | Question | TEST FAQ QUESTION |
      | Tags     | Tag1, Tag2        |
    And I fill in wysiwyg on field Answer with "ANSWER"
    And I fill in wysiwyg on field "Additional information" with "ADDITIONAL INFORMATION"
    And I wait for AJAX to finish
    And I select "Other" from "Category"
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    Then I should see the success message "FAQ TEST FAQ QUESTION has been created."
    And I should see the heading "TEST FAQ QUESTION"
    And I should see "ANSWER"
    And I should see "Share"
    Then the url should match "/faq/test-faq-question"

    Given I am an anonymous user
    And I visit "node/add/faq"
    Then I should see "No access (403)"

  Scenario: Successfully set category for FAQ
    Given I am logged in as a "content editor"
    And faq_categories terms:
      | name          |
      | FAQ-CATEGORY1 |
      | FAQ-CATEGORY2 |
    And I am on "node/add/faq"
    Then I should not see "No access (403)"
    When I fill in the following:
      | Question | TEST FAQ QUESTION |
    And I select "FAQ-CATEGORY1" from "Category"
    Then I press "Save"
    And I should see the success message "FAQ TEST FAQ QUESTION has been created."
    When I click "Edit" in the "Main content"
    And the "FAQ-CATEGORY1" option from "Category" is selected
    And the "FAQ-CATEGORY2" option from "Category" is not selected