@api @faq @faq-create @stability @CM @create
Feature: Create FAQ
  Benefit: In order to add FAQ item
  Role: As a CM
  Goal/desire: I want to create FAQ

  Scenario: Successfully create FAQ
    Given I am logged in as a "content moderator"
    And I am on "node/add/faq"
    Then I should not see "Access denied"
    When I fill in the following:
      | Question               | TEST FAQ QUESTION      |
      | Answer                 | ANSWER                 |
      | Additional information | ADDITIONAL INFORMATION |
      | Tags                   | Tag1, Tag2             |
    And I wait for AJAX to finish
    And I press "Save"
    Then I should see the success message "FAQ TEST FAQ QUESTION has been created."
    And I should see the heading "TEST FAQ QUESTION"
    And I should see "ANSWER"

    Given I am an anonymous user
    And I visit "node/add/faq"
    Then I should see "Access denied"
