@media @media-manage @stability @api
Feature: Manage media elements
  Benefit: In order to manage information on the site
  Role: CM
  Goal/desire: Manage files.

  Scenario: Successfully manage media
    Given I am logged in as a "content manager"
    And I am at "admin/content/file"
    And I should not see "No access (403)"
    And I should see the text "gorilla-3.jpg" in the "Testing media 2" row
    And I should see the text "gorilla-3.jpg" in the "Testing media 3" row
    Then I click "Edit" in the "gorilla-3.jpg" row
    And I should not see "No access (403)"
