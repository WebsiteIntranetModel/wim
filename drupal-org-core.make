api = 2
core = 7.x

projects[drupal][type] = core
projects[drupal][version] = 7.65

; Patches
;
; Ignore front end vendor folders to improve directory search performance
; https://www.drupal.org/node/2329453#comment-10637754
projects[drupal][patch][2329453_111] = https://www.drupal.org/files/issues/ignore_front_end_vendor-2329453-111.patch

; Keep a simple URL structure of file names
; https://www.drupal.org/project/drupal/issues/2954293#comment-12533368
projects[drupal][patch][2954293_6] = https://www.drupal.org/files/issues/2018-03-19/2954293-6.patch
