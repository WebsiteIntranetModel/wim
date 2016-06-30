@page @stability @api
Feature: Create basic page
  Benefit: In order to show textual information on the site
  Role: CM
  Goal/desire: Create basic page

  Scenario: Successfully create page
    Given I am logged in as a "Content Moderator"
    And I am at "node/add/page"
    When I fill in the following:
      | Title | This is a test basic page |
      | Body  | Body description text     |
      | Tags  | BSCPGTEST                 |
      | Date  | 06/27/2026                |
    And I press "Save"
    And I should see the success message "Basic page This is a test basic page has been created."
    And I should see "Publication date: Saturday, June 27, 2026"
    And I should see "Body description text"
    And I should not see "BSCPGTEST"
