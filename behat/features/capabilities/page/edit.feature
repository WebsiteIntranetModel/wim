@page @page-edit @stability @api
Feature: Edit basic page
  Benefit: In order to change textual information on the site
  Role: CM
  Goal/desire: Edit basic page

  Scenario: As a CM I should be able to successfully edit page
    Given "page" content:
          | title      | body          | Date        |
          | TITLE-ONE  | BODY-CONTENT1 | 06/27/2026  |
    Given I am logged in as a "content moderator"
    When I go to "admin/content"
    Then I should not see "Access denied"
    And I click "edit" in the "TITLE-ONE" row
    Then I should not see "Access denied"
    When I fill in the following:
          | Title | TITLE-TWO     |
          | Body  | BODY-CONTENT2 |
          | Tags  | BSCPGTEST     |
          | Date  | 06/30/2016    |
    And I press "Save"
    And I should see the success message "Basic page TITLE-TWO has been updated."
    And I click "TITLE-TWO" in the "TITLE-TWO" row
    And I should see "Publication date: 30 June 2016"
    And I should see "BODY-CONTENT2"
    And I should not see "BSCPGTEST"
    And I should not see "TITLE-ONE"
    And I should not see "BODY-CONTENT1"
    And I should not see "Publication date: 27 June 2026"
