api = 2
core = 7.x

; Default configuration
defaults[projects][subdir] = contrib

; Contrib
projects[admin_menu] = 3.0-rc5
projects[admin_views] = 1.6
projects[adminimal_admin_menu] = 1.7
projects[apachesolr] = 1.8
projects[apachesolr_exclude_node] = 1.4
projects[autologout] = 4.4
projects[bean] = 1.11
projects[breakpoints] = 1.4
projects[context] = 3.7
projects[context_condition_theme] = 1.0
projects[colectomy] = 1.0-beta2
projects[ctools] = 1.10
projects[date] = 2.9
projects[date_facets] = 1.0
projects[elysia_cron] = 2.2
projects[email] = 1.3
projects[encrypt] = 2.3
projects[entity] = 1.8
projects[entityreference] = 1.2
projects[facetapi] = 1.5
projects[features] = 2.10
projects[feeds] = 2.0-beta2
projects[felix] = 1.0-beta9
projects[field_group] = 1.5
projects[file_entity] = 2.0-beta3
projects[flood_control] = 1.0
projects[hansel] = 1.6
projects[honeypot] = 1.22
projects[job_scheduler] = 2.0-alpha3
projects[jquery_update] = 2.7
projects[location] = 3.7
projects[magic] = 2.2
projects[media] = 2.0-beta2
projects[menu_block] = 2.7
projects[menu_icons] = 3.0-beta4
projects[metatag] = 1.17
projects[migrate] = 2.8
projects[module_filter] = 2.0
projects[nodequeue] = 2.1
projects[l10n_update] = 2.0
projects[link] = 1.4
projects[libraries] = 2.3
projects[linkit] = 3.5
projects[paragraphs] = 1.0-rc4
projects[password_policy] = 1.12
projects[pathauto] = 1.3
projects[picture] = 2.13
projects[redirect] = 1.0-rc3
projects[scheduler] = 1.5
projects[strongarm] = 2.0
projects[special_menu_items] = 2.0
projects[token] = 1.6
projects[userprotect] = 1.2
projects[views] = 3.14
projects[views_bootstrap] = 3.1
projects[views_bulk_operations] = 3.3
projects[webform] = 4.14
projects[webform_clear] = 2.0
projects[webform_encrypt] = 1.1
projects[weight] = 3.1
projects[wysiwyg] = 2.x-dev

; Themes
projects[adminimal_theme] = 1.24
projects[bootstrap] = 3.5

; Patches
; Fixing bug when Features module can't include file containing exported taxonomy vocabulary because it hasn't included file integrating Features with Taxonomy yet.
; https://www.drupal.org/node/2143765#comment-10088780
projects[features][patch][2143765_7] = https://www.drupal.org/files/issues/features-hook_modules_enabled_include_file_issue-2143765-7.patch
; Fixing Notice: Undefined property: stdClass::$status in features_export_form
; https://www.drupal.org/node/2324973
projects[features][patch][2324973_19] = https://www.drupal.org/files/issues/undefined-property-status-2324973-19.patch
; Fixing bug with the location field ajax callback
; https://www.drupal.org/node/1997658#comment-10532078
projects[location][patch][1997658_6] = https://www.drupal.org/files/issues/location-1997658-46.patch
; Fixing bug with the location Google maps link
; https://www.drupal.org/node/2781227
projects[location][patch][2781227_1] = https://www.drupal.org/files/issues/location-google-maps-link-2781227-1.patch
; Add migration support for Bean
; https://www.drupal.org/node/2295973#comment-11536795
projects[bean][patch][2295973_11] = https://www.drupal.org/files/issues/bean-migrate-support-2295973-11.patch
; Fix "Select all" checkbox works only once
; https://www.drupal.org/node/2608360#comment-11620927
projects[views_bulk_operations][patch][2608360_14] = https://www.drupal.org/files/issues/2608360-14.patch
; Fix "Show fewer" link for Facet API filters
; https://www.drupal.org/node/2327997
projects[facetapi][patch][2327997_3] = https://www.drupal.org/files/issues/facetapi-2327997-3-show-fewer-links.patch

; Custom
; a11ychecker_custom
libraries[a11ychecker][download][type] = "get"
libraries[a11ychecker][download][url] = "http://a11ychecker.download.cksource.com/custom/a11ychecker_custom.zip"
libraries[a11ychecker][destination] = "libraries"
libraries[a11ychecker][subdir] = "ckeditor_plugins"

; CKEditor 4.4.6
libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = http://ckeditor.com/builder/download/4aa56d967057f1cfe925bceb9b98049d

; Slick
libraries[slick][download][type] = get
libraries[slick][download][url] = https://github.com/kenwheeler/slick/archive/master.zip
