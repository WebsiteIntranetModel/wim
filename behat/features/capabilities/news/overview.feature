@api @news @news-overview @stability @overview
Feature: News overview
  Benefit: In order to find more information
  Role: As a User
  Goal/desire: I want to see an News overview

  Scenario: Visitor views a news overview
    Given "News" content:
      | title        | body           | status | field_publication_date |
      | TEST NEWS 1  | BODY-CONTENT1  | 1      | 2016-01-22             |
      | TEST NEWS 2  | BODY-CONTENT2  | 1      | 2016-02-21             |
      | TEST NEWS 3  | BODY-CONTENT3  | 1      | 2016-03-20             |
      | TEST NEWS 4  | BODY-CONTENT4  | 1      | 2016-04-28             |
      | TEST NEWS 5  | BODY-CONTENT5  | 1      | 2016-05-12             |
      | TEST NEWS 6  | BODY-CONTENT6  | 1      | 2016-06-01             |
      | TEST NEWS 7  | BODY-CONTENT7  | 1      | 2016-07-04             |
      | TEST NEWS 8  | BODY-CONTENT8  | 1      | 2016-08-05             |
      | TEST NEWS 9  | BODY-CONTENT9  | 1      | 2016-09-07             |
      | TEST NEWS 10 | BODY-CONTENT10 | 1      | 2016-10-03             |
      | TEST NEWS 11 | BODY-CONTENT11 | 1      | 2016-11-15             |
    And I am an anonymous user
    And I am on "news"
    Then I should see the heading "News"
    And I should not see "No results"
    And I should see an ".pagination" element

  Scenario: Visitor sets the filters on a news overview
    Given news_categories terms:
      | name      |
      | CATEGORY1 |
    And "News" content:
      | title       | body          | status | field_publication_date |
      | TEST NEWS 3 | BODY-CONTENT3 | 1      | 2016-03-20             |
      | TEST NEWS 4 | BODY-CONTENT4 | 1      | 2016-04-28             |
      | TEST NEWS 5 | BODY-CONTENT5 | 1      | 2016-05-12             |
      | TEST NEWS 6 | BODY-CONTENT6 | 1      | 2016-06-01             |
      | TEST NEWS 7 | BODY-CONTENT7 | 1      | 2016-07-04             |
    Given I am an anonymous user
    And I am on "news"
    And I should see "From"
    And I should see "To"
    And I should see "Category"

    # Test date filters
    When I fill in "edit-field-publication-date-value-value-datepicker-popup-1" with "01 June 2016"
    Then I should see "05 June 2016"
    And I should not see "12 May 2016"
    When I press the "Clear" button
    Then I should see "12 May 2016"
    When I fill in "edit-field-publication-date-value-1-value-datepicker-popup-1" with "12 May 2016"
    Then I should see "12 May 2016"
    And I should not see "01 June 2016"
    And I press the "Clear" button
    When I fill in "edit-field-publication-date-value-value-datepicker-popup-1" with "12 May 2016"
    And I fill in "edit-field-publication-date-value-1-value-datepicker-popup-1" with "04 July 2016"
    Then I should see "05 June 2016"
    And I should not see "28 April 2016"

    # Test category filter
    When I select "CATEGORY1" from "edit-field-news-category-tid"
    Then I should see "No results"
    Given I am logged in as a "content editor"
    And I am on "node/add/news"
    When I fill in the following:
      | Title | TEST CATEGORY NEWS |
    And I fill in wysiwyg on field Body with "BODY-CONTENT"
    And I click "Publishing options"
    And I fill in the following:
      | Date | 30/06/2016 |
    Then I select "CATEGORY1" from "Category"
    And I press "Save"
    And I go to "news"
    When I select "CATEGORY1" from "edit-field-news-category-tid"
    Then I should see "TEST CATEGORY NEWS"
    And I should not see "TEST NEWS 3"
