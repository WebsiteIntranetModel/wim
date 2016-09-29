@page @page-create @stability @api
Feature: Create basic page
  Benefit: In order to show textual information on the site
  Role: CM
  Goal/desire: Create basic page

  Scenario: Successfully create page
    Given I am logged in as a "content editor"
    And I am at "node/add/page"
    When I fill in the following:
      | Title | This is a test basic page |
      | Tags  | BSCPGTEST, BSCPGTAG       |
    And I fill in wysiwyg on field Body with "Body description text"
    And I click "Publishing options"
    And I fill in the following:
      | Date | 27/06/2026 |
      | Time | 11:10:00   |
    Then I should see "Promoted"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    And I should see the success message "Basic page This is a test basic page has been created."
    And I should see "Body description text"
    And I should see "Share"
    Then the url should match "/this-is-a-test-basic-page"

    Given I am logged in as a "content manager"
    And I am at "admin/structure/taxonomy/tags"
    Then I should see "edit" in the "BSCPGTAG" row
    Then I should see "edit" in the "BSCPGTEST" row

    Given I am an anonymous user
    And I visit "node/add/page"
    Then I should see the heading "No access (403)"
