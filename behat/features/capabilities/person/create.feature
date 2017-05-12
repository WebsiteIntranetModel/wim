@person @person-create @stability @api
Feature: Create person
  Benefit: In order to show textual information on the site
  Role: CM
  Goal/desire: Create person

  Scenario: Successfully create person
    Given I am logged in as a "content editor"
    And I am at "node/add/person"
    When I fill in the following:
      | Title | Bruce Wayne         |
      | Tags  | BSCPGTEST, BSCPGTAG |
      | Role | Batman              |
      | Phone | 03023 302302 3      |
      | Email | batman@test.com     |
    And I fill in wysiwyg on field Body with "Body description text"
    And I fill in wysiwyg on field Address with "Secret place"
    And I click "Browse"
    Then I wait for AJAX to finish
    And I wait for 5 seconds
    And I switch to the iframe "mediaBrowser"
    And I attach the file "/fixtures/images/drupal-icon.png" to "Upload a new file"
    And I press "Next"
    Then I press "Save"
    When I switch back from an iframe
    And I click "Reminder"
    And I should see "Reminder email"
    And I click "Scheduling options"
    And I should see "Publish on"
    And I should see "Unpublish on"
    And I press "Save"
    And I should see the success message "Person Bruce Wayne has been created."
    And I should see "Body description text"
    And I should see "Batman"
    And I should see "Email"
    And I should see "Phone"
    And I should see "Secret place"
    And I should see "Share"
    Then the url should match "/bruce-wayne"

    Given I am an anonymous user
    And I visit "node/add/person"
    Then I should see the heading "No access (403)"
