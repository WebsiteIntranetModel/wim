@person @person-edit @stability @api
Feature: Edit person
  Benefit: In order to change textual information on the site
  Role: CM
  Goal/desire: Edit person

  Scenario: As a CM I should be able to successfully edit person
    Given "person" content:
      | title       | body          | Role    | Phone   | Email       | author         |
      | TEST-PERSON | BODY-CONTENT1 | testrole | 777-777 | jn@test.com | jack_nicholson |
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | jack_nicholson |
      | Password | jack_nicholson |
    And I press "Log in"
    Then I should see "jack_nicholson"
    When I go to "admin/content"
    And I select "Person" from "Type"
    And I press "Apply"
    And I wait for AJAX to finish
    And I click "edit" in the "TEST-PERSON" row
    Then I should not see "No access (403)"
    When I fill in the following:
      | Title | EDITED-PERSON |
      | Role | kamikadze     |
      | Email | jn+1@test.com |
      | Phone | 222-333       |
    And I fill in wysiwyg on field Body with "BODY-CONTENT2"
    And I press "Save"
    And I should see "Person EDITED-PERSON has been updated."
    And I click "EDITED-PERSON" in the "EDITED-PERSON" row
    And I should see "BODY-CONTENT2"
    And I should see "kamikadze"
    And I should see "jn+1@test.com"
    And I should see "222-333"
    And I should not see "TEST-PERSON"
    And I should not see "BODY-CONTENT1"
    And I should not see "testrole"
    And I should not see "777-777"
    And I should not see "jn@test.com"
