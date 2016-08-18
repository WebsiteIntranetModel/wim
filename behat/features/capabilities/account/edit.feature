@account-edit @security @stability @api
Feature: Edit accounts
  Benefit: In order to manage users
  Role: ADMIN
  Goal/desire: Edit any user profile

  @critical
  Scenario: Successfully edit user profile
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | klark_kent |
      | Password | klark_kent |
    And I press "Log in"
    Then I should see "klark_kent"
    When I go to "/admin/people"
    Then I should see the text "edit" in the "cm" row
    And I click "edit" in the "cm" row
    Then I should not see "No access (403)"

  Scenario: Check if admin can block users
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | klark_kent |
      | Password | klark_kent |
    And I press "Log in"
    When I go to "admin/people"
    Then I should see the text "active" in the "cm" row
    And I click "edit" in the "cm" row
    When I select the radio button "Blocked" with the id "edit-status-0"
    And I press "Save"
    Then I should see the text "blocked" in the "cm" row

  Scenario: Check if CM can edit users
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | cm |
      | Password | cm |
    And I press "Log in"
    When I go to "admin/people"
    Then I should see "No access (403)"
