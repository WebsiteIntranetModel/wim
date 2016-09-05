@force-password-change @security @stability @api
Feature: Force password change
  Benefit: In order to force users change password
  Role: ADMIN
  Goal/desire: Force user to change his password

  Scenario: Check if CM can force users to change password
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | tony_stark |
      | Password | tony_stark |
    And I press "Log in"
    When I go to "admin/config/people/password_policy/password_change"
    Then I should see "No access (403)"

  @critical
  Scenario: Successfully force CM roles to change passwords
    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | klark_kent |
      | Password | klark_kent |
    And I press "Log in"
    Then I should see "klark_kent"
    When I go to "admin/config/people/password_policy/password_change"
    Then I should see "Force users in the following roles to change their password"
    And I check the box "content manager"
    Then I press "Save changes"
    Then I should see "Users in the following roles will be required to immediately change their password: content manager"

    Given I am an anonymous user
    And I am on the homepage
    When I go to "/user/login"
    And I fill in the following:
      | Username | tony_stark |
      | Password | tony_stark |
    And I press "Log in"
    Then I should see "Your password has expired. You must change your password to proceed on the site."
