@person @person-view @stability @api
Feature: View person
  Benefit: In order to view textual information on the site
  Role: AN
  Goal/desire: View person

  Scenario: As a AN I should be able to see person
    Given I am an anonymous user
    Given I am viewing a "person":
      | title                | PERSON-ONE       |
      | body                 | PERSON-CONTENT1  |
      | field_person_roles   | test_role        |
      | field_person_phone   | 2026062700       |
      | field_email:email    | person@test.com  |
      | field_person_address | bungalo          |
      | field_tags           | Tag1             |
    Then I should not see the link "Edit" in the "Main content"
    And I should not see "Tag1"
    And I should see "PERSON-ONE"
    And I should see "PERSON-CONTENT1"
    And I should see "test_role"
    And I should see "person@test.com"
    And I should see "2026062700"
    And I should see "bungalo"

  Scenario: As a AN I should see metatags
    Given I am an anonymous user
    When I go to "person-metatag-test"
    And I see the metatag "description" with "This is a small description."
    And I see the metatag "keywords" with "keyword1, keyword2"
    And I see the title meta with "Metatag title"
