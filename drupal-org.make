api = 2
core = 7.x

; Default configuration
defaults[projects][subdir] = contrib

; Contrib
projects[admin_menu] = 3.0-rc5
projects[ctools] = 1.9
projects[date] = 2.9
projects[entity] = 1.7
projects[features] = 2.10
projects[field_group] = 1.5
projects[entity] = 1.7
projects[entityreference] = 1.1
projects[jquery_update] = 2.7
projects[location] = 3.7
projects[magic] = 2.2
projects[migrate] = 2.8
projects[link] = 1.4
projects[strongarm] = 2.0
projects[views] = 3.14
projects[views_bootstrap] = 3.1
projects[weight] = 3.1

; Themes
projects[bootstrap] = 3.5

; Patches
; Fixing bug when Features module can't include file containing exported taxonomy vocabulary because it hasn't included file integrating Features with Taxonomy yet.
; https://www.drupal.org/node/2143765#comment-10088780
projects[features][patch][2143765_7] = https://www.drupal.org/files/issues/features-hook_modules_enabled_include_file_issue-2143765-7.patch
