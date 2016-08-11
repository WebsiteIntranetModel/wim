@api @faq @faq-edit @stability @CM @edit
Feature: Edit FAQ
  Benefit: In order to edit FAQ
  Role: As a CM
  Goal/desire: I want to edit FAQ

  Scenario: Successfully edit FAQ
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    And I select "FAQ" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I should see "Question 1"
    And I click "edit" in the "Question 1" row
    Then I should not see "No access (403)"
    And I enter "Question 1 Edited" for Question
    And I fill in wysiwyg on field "Answer" with "ANSWER 1 Edited"
    And I fill in wysiwyg on field "Additional information" with "ADDITIONAL INFO 1 Edited"
    And I enter "Tag3" for Tags
    And I press "Save"
    Then I should see the success message "FAQ Question 1 Edited has been updated."
    Then I click "Question 1 Edited" in the "Question 1 Edited" row
    And I should see the heading "Question 1 Edited"
    And I should see "ANSWER 1 Edited"
    And I should see "ADDITIONAL INFO 1 Edited"
    And I should not see the heading "Question 1"
    And I should not see "Answer for 1 Question"
    And I should not see "Some addition information for Question 1"
