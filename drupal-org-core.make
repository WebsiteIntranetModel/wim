api = 2
core = 7.x

projects[drupal][type] = core
projects[drupal][version] = 7.57

; Patches
;
; Ignore front end vendor folders to improve directory search performance
; https://www.drupal.org/node/2329453#comment-10637754
projects[drupal][patch][2329453_111] = https://www.drupal.org/files/issues/ignore_front_end_vendor-2329453-111.patch

; Newer Chrome versions and IE11/Edge cannot drag and drop anymore on desktop after 7.51 update when jQuery is updated to 1.7-1.11.0
; https://www.drupal.org/node/2821441#comment-11787576
projects[drupal][patch][2821441_30] = https://www.drupal.org/files/issues/pointereventfix-2821441-30.patch
