@tabs @inline-tabs @stability @api
Feature: View tabs
  Benefit: In order to view tabs created in CKEditor
  Role: AN
  Goal/desire: View tabs

  Scenario: As a AN I should be able to see tabs in content
    Given I am an anonymous user
    And I am at "testing-ckeditor-tabs"
    And I click "Tab1"
    Then I should see "Content for tab1"
    And I click "Tab2"
    Then I should see "Content for tab2"
    And I click "Tab3"
    Then I should see "Content for tab3"
    And I click "Tab4"
    Then I should see "Content for tab4"
    And I click "Tab5"
    Then I should see "Content for tab5"
