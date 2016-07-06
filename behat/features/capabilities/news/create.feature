@api @news @news-create @stability @CM @create
Feature: Create News
  Benefit: In order to add news
  Role: As a CM
  Goal/desire: I want to create News

  Scenario: Successfully create news
    Given I am logged in as a "content moderator"
    And I am on "node/add/news"
    Then I should not see "Access denied"
    And I should see "Category"
    And I should see "Promoted"
    And I should see "Add a new file"
    And I should see "Image"
    When I fill in the following:
      | Title | TEST NEWS    |
      | Date  | 06/30/2016   |
      | Body  | BODY CONTENT |
      | Tags  | tag1, tag2   |
    And I attach the file "/fixtures/images/drupal-icon.png" to "Image"
    And I attach the file "/fixtures/files/pdf-file.pdf" to "Add a new file"
    And I press "Save"
    Then I should see the success message "News TEST NEWS has been created."
    And I should see the heading "TEST NEWS"
    And I should see "BODY CONTENT"
    And I should see "30 June 2016"
    And I should see "tag1"
    And I should see an ".field-name-field-image img" element
    And I should see "pdf-file.pdf"

    Given I am an anonymous user
    And I visit "node/add/news"
    Then I should see the heading "Access denied"

  Scenario: Successfully set category for news
    Given I am logged in as a "content moderator"
    Given news_categories terms:
      | name      |
      | CATEGORY1 |
      | CATEGORY2 |
    And I am on "node/add/news"
    Then I should not see "Access denied"
    When I fill in the following:
      | Title | TEST CATEGORY NEWS |
      | Date  | 06/30/2016         |
      | Body  | BODY CONTENT       |
    Then I select "CATEGORY1" from "Category"
    Then I press "Save"
    Then I should see the success message "News TEST CATEGORY NEWS has been created."
    Then I should see the link "Edit"
    When I click "Edit"
    Then I should see "CATEGORY1"
    Then the "select[name='field_news_category[und]'] option[selected='selected']" element should contain "CATEGORY1"
    Then the "select[name='field_news_category[und]'] option[selected='selected']" element should not contain "CATEGORY2"
