@media @media-manage @stability @api
Feature: Manage media elements
  Benefit: In order to manage information on the site
  Role: CM
  Goal/desire: Manage files.

  Scenario: Successfully manage media
    Given I am logged in as a "content manager"
    When I am at "admin/content/file"
    And I fill in "edit-filename" with "gorilla"
    And I break
    And I press "Apply"
    And I wait for 3 seconds
    Then I should see the text "gorilla.jpg"
    Then I click "Edit" in the "gorilla.jpg" row
    And I should not see "No access (403)"
