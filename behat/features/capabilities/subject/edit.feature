@subject-page @subject-page-edit @stability @api
Feature: Edit subject page
  Benefit: In order to change textual information on the site
  Role: CM
  Goal/desire: Edit subject page

  Scenario: As a CM I should be able to successfully edit subject page
    Given "Subject page" content:
      | title       | body          | Date       | author          |
      | SUBJECT-ONE | BODY-CONTENT1 | 06/27/2026 | content_manager |
    Given I am logged in as a "content manager"
    When I go to "admin/content"
    And I select "Subject page" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I click "edit" in the "SUBJECT-ONE" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | SUBJECT-TWO   |
    And I fill in wysiwyg on field Body with "BODY-CONTENT2"
    And I click "Publishing options"
    And I fill in the following:
      | Date | 30/06/2016 |
      | Time | 10:00:00   |
    Then I press "Save"
    And I should see "Subject page SUBJECT-TWO has been updated."
    And I click "SUBJECT-TWO" in the "SUBJECT-TWO" row
    And I should not see "30 June 2016"
    And I should see "BODY-CONTENT2"
    And I should not see "SUBJECT-ONE"
    And I should not see "BODY-CONTENT1"
