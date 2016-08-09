api = 2
core = 7.x

; Default configuration
defaults[projects][subdir] = contrib

; Contrib
projects[admin_menu] = 3.0-rc5
projects[breakpoints] = 1.4
projects[context] = 3.7
projects[colectomy] = 1.0-beta2
projects[ctools] = 1.9
projects[date] = 2.9
projects[entity] = 1.7
projects[features] = 2.10
projects[felix] = 1.0-beta8
projects[field_group] = 1.5
projects[entity] = 1.7
projects[entityreference] = 1.1
projects[jquery_update] = 2.7
projects[location] = 3.7
projects[magic] = 2.2
projects[menu_block] = 2.7
projects[migrate] = 2.8
projects[nodequeue] = 2.1
projects[link] = 1.4
projects[linkit] = 3.5
projects[picture] = 2.13
projects[strongarm] = 2.0
projects[views] = 3.14
projects[views_bootstrap] = 3.1
projects[weight] = 3.1
projects[wysiwyg] = 2.x-dev

; Themes
projects[bootstrap] = 3.5

; Patches
; Fixing bug when Features module can't include file containing exported taxonomy vocabulary because it hasn't included file integrating Features with Taxonomy yet.
; https://www.drupal.org/node/2143765#comment-10088780
projects[features][patch][2143765_7] = https://www.drupal.org/files/issues/features-hook_modules_enabled_include_file_issue-2143765-7.patch
; Fixing bug with the location field ajax callback
; https://www.drupal.org/node/1997658#comment-10532078
projects[location][patch][1997658_6] = https://www.drupal.org/files/issues/location-1997658-46.patch

; Custom
; a11ychecker_custom
;libraries[a11ychecker][download][type] = "get"
;libraries[a11ychecker][download][url] = "http://a11ychecker.download.cksource.com/custom/a11ychecker_custom.zip"
;libraries[a11ychecker][destination] = "custom"
;libraries[a11ychecker][subdir] = "ckeditor_customtags"
;libraries[a11ychecker][directory_name] = "a11ychecker_custom"
