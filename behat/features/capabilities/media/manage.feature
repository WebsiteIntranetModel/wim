@media @media-manage @stability @api
Feature: Manage media elements
  Benefit: In order to manage information on the site
  Role: CM
  Goal/desire: Manage files.

  Scenario: Successfully manage media
    Given I am logged in as a "content manager"
    And I am at "admin/content/file"
    And I should not see "No access (403)"
    And I should see the text "2 places" in the "gorilla.jpg" row
    Then I click "Edit" in the "gorilla.jpg" row
    And I should not see "No access (403)"
