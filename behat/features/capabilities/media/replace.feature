@media @media-replace @stability @api
Feature: Replace media elements
  Benefit: In order to replace media elements on the site
  Role: CM
  Goal/desire: When replacing the file, the file will be replaced for all the nodes where this images is used.

  Scenario: Successfully replace media
    Given I am logged in as a "content manager"
    And I am at "admin/content/file"
    And I should not see "No access (403)"
    And I should see the text "2 places" in the "gorilla.jpg" row
    Then I click "Edit" in the "gorilla.jpg" row
    And I should not see "No access (403)"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Replace file"
    Then I press "Save"
    And I should see "Image gorilla.jpg has been updated."
    And I should see "The replaced Image fixtures/gorilla.jpg has been deleted."
    Then I go to "admin/content"
    And I select "Basic page" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I click "edit" in the "Testing media 2" row
    And I should not see "No access (403)"
    And I should not see "(127.75 KB)"
    And I should see "(54.6 KB)"
    Then I go to "admin/content"
    And I click "edit" in the "Testing media 3" row
    And I should not see "No access (403)"
    And I should not see "(127.75 KB)"
    And I should see "(54.6 KB)"
