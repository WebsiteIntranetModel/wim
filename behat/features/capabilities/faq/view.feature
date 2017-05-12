@faq @faq-view @stability @api
Feature: View FAQ
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View FAQ

  Scenario: As a AN I should be able to see FAQ
    Given I am an anonymous user
    And tags terms:
      | name |
      | TAG1 |
      | TAG2 |
    And I am viewing a "faq":
      | title                            | FAQ-QUESTION    |
      | body                             | ANSWER-CONTENT  |
      | field_faq_additional_information | ADDITIONAL-INFO |
      | field_tags                       | Tag1, Tag2      |
    Then I should not see the link "Edit" in the "Main content"
    And I should not see "BSCPGTEST"
    And I should see "FAQ-QUESTION"
    And I should see "ANSWER-CONTENT"
    And I should see "ADDITIONAL-INFO"

  Scenario: As a AN I should see metatags
    Given I am an anonymous user
    When I go to "faq/faq-metatag-test"
    And I see the metatag "description" with "This is a small description."
    And I see the metatag "keywords" with "keyword1, keyword2"
    And I see the title meta with "Metatag title"
