@subject-page @subject-page-create @stability @api
Feature: Create subject page
  Benefit: In order to show textual information on the site
  Role: CM
  Goal/desire: Create subject page

  Scenario: Successfully create subject page
    Given I am logged in as a "content editor"
    And I am at "node/add/subject-page"
    When I fill in the following:
      | Title | This is a test subject page |
    And I fill in wysiwyg on field Body with "Body description text"
    And I click "Publishing options"
    And I fill in the following:
      | Date | 27/06/2026 |
      | Time | 11:10:00   |
    Then I should see "Promoted"
    Then I press "Save"
    And I should see the success message "Subject page This is a test subject page has been created."
    And I should not see "27 June 2026"
    And I should see "Body description text"
    And I should not see "Share"

    Given I am an anonymous user
    And I visit "node/add/subject-page"
    Then I should see the heading "No access (403)"
