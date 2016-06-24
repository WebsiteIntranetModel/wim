api = 2
core = 7.x

projects[drupal][type] = core
projects[drupal][version] = 7.44

; Patches
;
; run-tests.sh should exit with a failure code if any tests failed
; https://www.drupal.org/node/2189345#comment-10622516
projects[drupal][patch][2189345_167] = https://www.drupal.org/files/issues/2189345-39_0.patch
; Ignore front end vendor folders to improve directory search performance
; https://www.drupal.org/node/2329453#comment-10637754
projects[drupal][patch][2329453_111] = https://www.drupal.org/files/issues/ignore_front_end_vendor-2329453-111.patch
