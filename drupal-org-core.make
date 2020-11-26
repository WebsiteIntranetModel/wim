api = 2
core = 7.x

projects[drupal][type] = core

projects[drupal][version] = 7.75

; Patches

; Keep a simple URL structure of file names
; https://www.drupal.org/project/drupal/issues/2954293#comment-12533368
projects[drupal][patch][2954293_6] = https://www.drupal.org/files/issues/2019-03-20/2954293-13_0.patch
