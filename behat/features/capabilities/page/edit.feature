@page @page-edit @stability @api
Feature: Edit basic page
  Benefit: In order to change textual information on the site
  Role: CM
  Goal/desire: Edit basic page

  Scenario: As a CM I should be able to successfully edit page
    Given "page" content:
      | title     | body          | Date       | author         |
      | TITLE-ONE | BODY-CONTENT1 | 06/27/2026 | jack_nicholson |
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | jack_nicholson |
      | Password | jack_nicholson |
    And I press "Log in"
    Then I should see "jack_nicholson"
    When I go to "admin/content"
    And I select "Basic page" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I click "edit" in the "TITLE-ONE" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | TITLE-TWO     |
      | Tags  | BSCPGTEST     |
    And I fill in wysiwyg on field Body with "BODY-CONTENT2"
    And I click "Publishing options"
    And I fill in the following:
      | Date | 30/06/2016 |
      | Time | 10:00:00   |
    And I press "Save"
    And I should see "Basic page TITLE-TWO has been updated."
    And I click "TITLE-TWO" in the "TITLE-TWO" row
    And I should see "BODY-CONTENT2"
    And I should not see "TITLE-ONE"
    And I should not see "BODY-CONTENT1"
