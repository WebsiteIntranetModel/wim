@api @news @stability @overview
Feature: News overview
  Benefit: In order to find more information
  Role: As a User
  Goal/desire: I want to see an News overview

  @AN @perfect
  Scenario: Visitor views a news overview
    Given "News" content:
      | Title        | Body             | status |
      | Test news 1  | PLACEHOLDER BODY | 1      |
      | Test news 2  | PLACEHOLDER BODY | 1      |
      | Test news 3  | PLACEHOLDER BODY | 1      |
      | Test news 4  | PLACEHOLDER BODY | 1      |
      | Test news 5  | PLACEHOLDER BODY | 1      |
      | Test news 6  | PLACEHOLDER BODY | 1      |
      | Test news 7  | PLACEHOLDER BODY | 1      |
      | Test news 8  | PLACEHOLDER BODY | 1      |
      | Test news 9  | PLACEHOLDER BODY | 1      |
      | Test news 10 | PLACEHOLDER BODY | 1      |
      | Test news 11 | PLACEHOLDER BODY | 1      |
      | Test news 12 | PLACEHOLDER BODY | 1      |
    Given I am an anonymous user
    And I am on "news"
    Then I should see the heading "News"
    Then I should see 10 "article.node-teaser" elements
    Then the "article.node-teaser" element should contain "Read more"
    Then I should see an ".pagination" element
