@api @news @stability @overview
Feature: News overview
  Benefit: In order to find more information
  Role: As a User
  Goal/desire: I want to see an News overview

  Scenario: Visitor views a news overview
    Given "News" content:
      | Title        | Body           | status |
      | TEST NEWS 1  | BODY-CONTENT1  | 1      |
      | TEST NEWS 2  | BODY-CONTENT2  | 1      |
      | TEST NEWS 3  | BODY-CONTENT3  | 1      |
      | TEST NEWS 4  | BODY-CONTENT4  | 1      |
      | TEST NEWS 5  | BODY-CONTENT5  | 1      |
      | TEST NEWS 6  | BODY-CONTENT6  | 1      |
      | TEST NEWS 7  | BODY-CONTENT7  | 1      |
      | TEST NEWS 8  | BODY-CONTENT8  | 1      |
      | TEST NEWS 9  | BODY-CONTENT9  | 1      |
      | TEST NEWS 10 | BODY-CONTENT10 | 1      |
      | TEST NEWS 11 | BODY-CONTENT11 | 1      |
    Given I am an anonymous user
    And I am on "news"
    Then I should see the heading "News"
    Then I should see 10 "article.node-teaser" elements
    Then the "article.node-teaser" element should contain "Read more"
    Then I should see an ".pagination" element
