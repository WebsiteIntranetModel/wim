@api @news @news-create @stability @CM @create
Feature: Create News
  Benefit: In order to add news
  Role: As a CM
  Goal/desire: I want to create News

  Scenario: Successfully create news
    Given I am logged in as a "content editor"
    And I am on "node/add/news"
    Then I should not see "No access (403)"
    And I click "Edit summary"
    When I fill in the following:
      | Title   | TEST NEWS    |
      | Tags    | Tag1, Tag2   |
    And I fill in wysiwyg on field Summary with "SUMMARY-TEXT"
    And I fill in wysiwyg on field Body with "BODY CONTENT"
    And I click "Introduction"
    And I fill in wysiwyg on field "Lead paragraph" with "Lead paragraph demo content"
    And I click "Publishing options"
    And I check the box "Promoted"
    And I fill in the following:
      | Date | 30/06/2016 |
      | Time | 02:22:00   |
    And I click "Browse"
    Then I wait for AJAX to finish
    And I wait for 5 seconds
    And I switch to the iframe "mediaBrowser"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Upload a new file"
    And I press "Next"
    Then I press "Save"
    When I switch back from an iframe
    And I attach the file "/fixtures/files/pdf-file.pdf" to "Add a new file"
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    Then I should see the success message "News TEST NEWS has been created."
    And I should see the heading "TEST NEWS"
    And I should see "BODY CONTENT"
    And I should see "30 June 2016"
    And I should see an ".field-name-field-image img" element
    And I should see "pdf-file.pdf"
    And I should see "Share"
    Then the url should match "/news/test-news"

    Given I am an anonymous user
    And I visit "node/add/news"
    Then I should see the heading "No access (403)"

  Scenario: Successfully set category for news
    Given I am logged in as a "content editor"
    And news_categories terms:
      | name      |
      | CATEGORY1 |
      | CATEGORY2 |
    And I am on "node/add/news"
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | TEST CATEGORY NEWS |
    And I fill in wysiwyg on field Body with "BODY CONTENT"
    And I select "CATEGORY1" from "Category"
    Then I press "Save"
    And I should see the success message "News TEST CATEGORY NEWS has been created."
    When I click "Edit" in the "Main content"
    And the "CATEGORY1" option from "Category" is selected
    And the "CATEGORY2" option from "Category" is not selected
