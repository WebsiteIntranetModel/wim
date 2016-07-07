@api @faq @faq-edit @stability @CM @edit
Feature: Edit FAQ
  Benefit: In order to edit FAQ
  Role: As a CM
  Goal/desire: I want to edit FAQ

  Scenario: Successfully edit FAQ
    Given "faq" content:
      | title     | body    | field_faq_additional_information | field_tags | status | uid |
      | QUESTION1 | ANSWER1 | ADDITIONAL INFO1                 | TAG1       | 1      | 1   |
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I should not see "Access denied"
    And I should see "QUESTION1"
    And I click "edit" in the "QUESTION1" row
    Then I should not see "Access denied"
    When I fill in the following:
      | Question               | QUESTION2        |
      | Answer                 | ANSWER2          |
      | Additional information | ADDITIONAL INFO2 |
      | Tags                   | TAG2             |
    And I press "Save"
    Then I should see the success message "FAQ QUESTION2 has been updated."
    And I click "QUESTION2" in the "QUESTION2" row
    And I should see "QUESTION2"
    And I should see "ANSWER2"
    And I should see "ADDITIONAL INFO2"
    And I should see "TAG2"
    And I should not see "QUESTION1"
    And I should not see "TAG1"
    And I should not see "ANSWER1"
    And I should not see "ADDITIONAL INFO1"
