@page @page-create @stability @api
Feature: Create basic page
  Benefit: In order to show textual information on the site
  Role: CM
  Goal/desire: Create basic page

  Scenario: Successfully create page
    Given I am logged in as a "content moderator"
    And I am at "node/add/page"
    Then I should see "Promoted"
    Then I should see "Image"
    When I fill in the following:
      | Title | This is a test basic page |
      | Body  | Body description text     |
      | Tags  | BSCPGTEST, BSCPGTAG       |
      | Date  | 06/27/2026                |
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I press "Save"
    And I should see the success message "Basic page This is a test basic page has been created."
    And I should see "Publication date: 27 June 2026"
    And I should see "Body description text"
    And I should not see "BSCPGTEST"
    And I am at "admin/structure/taxonomy/tags"
    Then I should see "edit" in the "BSCPGTAG" row
    Then I should see "edit" in the "BSCPGTEST" row

    Given I am an anonymous user
    And I visit "node/add/page"
    Then I should see the heading "Access denied"
