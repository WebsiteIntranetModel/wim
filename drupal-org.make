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
projects[apachesolr_attachments] = 1.4
projects[autologout] = 4.4
projects[bean] = 1.11
projects[breakpoints] = 1.4
projects[bootstrap_fieldgroup] = 1.2
projects[context] = 3.7
projects[context_condition_theme] = 1.0
projects[colectomy] = 1.0-beta2
projects[chosen] = 2.0
projects[ctools] = 1.11
projects[date] = 2.9
projects[date_facets] = 1.0
projects[diff] = 3.3
projects[elysia_cron] = 2.4
projects[email] = 1.3
projects[encrypt] = 2.3
projects[entity] = 1.8
projects[entityreference] = 1.5
projects[facetapi] = 1.5
projects[features] = 2.10
projects[felix] = 1.0-beta9
projects[field_group] = 1.5
projects[file_entity] = 2.0-beta3
projects[flood_control] = 1.0
projects[hansel] = 1.6
projects[honeypot] = 1.22
projects[i18n] = 1.15
projects[jquery_update] = 2.7
projects[location] = 3.7
projects[logging_alerts] = 2.2
projects[magic] = 2.3
projects[mailsystem] = 2.34
projects[media] = 2.1
projects[menu_block] = 2.7
projects[menu_icons] = 3.0-beta4
projects[metatag] = 1.21
projects[migrate] = 2.8
projects[mimemail] = 1.0-beta4
projects[module_filter] = 2.0
projects[nodequeue] = 2.1
projects[l10n_update] = 2.1
projects[link] = 1.4
projects[libraries] = 2.3
projects[linkit] = 3.5
projects[paragraphs] = 1.0-rc5
projects[password_policy] = 1.12
projects[pathauto] = 1.3
projects[picture] = 2.13
projects[redirect] = 1.0-rc3
projects[revisioning] = 1.9
projects[roleassign] = 1.1
projects[scheduler] = 1.5
projects[strongarm] = 2.0
projects[special_menu_items] = 2.0
projects[token] = 1.7
projects[userprotect] = 1.2
projects[variable] = 2.5
projects[views] = 3.17
projects[views_bootstrap] = 3.1
projects[views_bulk_operations] = 3.4
projects[webform] = 4.14
projects[webform_clear] = 2.0
projects[webform_encrypt] = 1.2
projects[weight] = 3.1
projects[wysiwyg] = 2.x-dev
projects[xmlsitemap] = 2.3

; Themes
projects[adminimal_theme] = 1.24
projects[bootstrap] = 3.12

; Patches
; Features
; Fixing bug when Features module can't include file containing exported taxonomy vocabulary because it hasn't included file integrating Features with Taxonomy yet.
; https://www.drupal.org/node/2143765#comment-10088780
projects[features][patch][2143765_7] = https://www.drupal.org/files/issues/features-hook_modules_enabled_include_file_issue-2143765-7.patch

; Fixing Notice: Undefined property: stdClass::$status in features_export_form
; https://www.drupal.org/node/2324973
projects[features][patch][2324973_19] = https://www.drupal.org/files/issues/undefined-property-status-2324973-19.patch

; Apachesolr exclude node
; Fix for undefined property when publishing a revision.
projects[apachesolr_exclude_node][patch][2862892] = https://www.drupal.org/files/issues/apachesolr_exclude_node_d7-2862892.patch

; Ctools
; Fixing css for dropdown buttons
projects[ctools][patch][1966072_4] = https://www.drupal.org/files/ctools-ops-dropbutton-css-1966072-4.patch

; Location
; Fixing bug with the location field ajax callback
; https://www.drupal.org/node/1997658#comment-10532078
projects[location][patch][1997658_6] = https://www.drupal.org/files/issues/location-1997658-46.patch

; Fixing bug with the location Google maps link
; https://www.drupal.org/node/2781227
projects[location][patch][2781227_1] = https://www.drupal.org/files/issues/location-google-maps-link-2781227-1.patch

; Bean
; Add migration support for Bean
; https://www.drupal.org/node/2295973#comment-11536795
projects[bean][patch][2295973_11] = https://www.drupal.org/files/issues/bean-migrate-support-2295973-11.patch

; Fix view modes for Bean blocks
; https://www.drupal.org/node/1911234
projects[bean][patch][1911234_6] = https://www.drupal.org/files/issues/select-from-enabled-view-modes-1911234-6.patch

; Views
; Add plural format to views_handler_area_result
; https://www.drupal.org/node/1793500#comment-10875360
projects[views][patch][1793500_13] = https://www.drupal.org/files/issues/views-area-results-plural-1793500-13.patch

; Facet API
; Fix "Show fewer" link for Facet API filters
; https://www.drupal.org/node/2327997
projects[facetapi][patch][2327997_3] = https://www.drupal.org/files/issues/facetapi-2327997-3-show-fewer-links.patch

; Felix
; Fix notice from Felix module
; https://www.drupal.org/node/2811151
projects[felix][patch][2811151] = https://www.drupal.org/files/issues/felix-invalid-foreach-2811151-1.patch
; Fix Felix views configs
; https://www.drupal.org/node/2861052
projects[felix][patch][2861052] = https://www.drupal.org/files/issues/felix-views-configs-2861052-1.patch

; Webform Clear
; Fix Undefined index is_new for Webform Clear
; https://www.drupal.org/node/2471671
projects[webform_clear][patch][2471671] = https://www.drupal.org/files/issues/2471671-test-withpatch.patch

; Hansel breadcrumbs
; Token replacement (pathauto patterns) completely broken
; https://www.drupal.org/node/2399645
projects[hansel][patch][2399645] = https://www.drupal.org/files/issues/hansel-broken-token-generation-2399645-1.patch

; Linkit
; Allow Linkit support for any eligible element type
; https://www.drupal.org/node/2651404
projects[linkit][patch][2651404] = https://www.drupal.org/files/issues/linkit-add-to-any-element-2651404-3.patch
; Support for default drupal menu system
; https://www.drupal.org/node/2514928
projects[linkit][patch][2514928] = https://www.drupal.org/files/issues/linkit-menu-links-2514928-9.patch

; CKEditor 4.5.11
;libraries[ckeditor][download][type] = get
;libraries[ckeditor][download][url] = http://ckeditor.com/builder/download/4aa56d967057f1cfe925bceb9b98049d

; Slick
libraries[slick][download][type] = get
libraries[slick][download][url] = https://github.com/kenwheeler/slick/archive/master.zip

; Chosen
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.6.2/chosen_v1.6.2.zip

; Apachesolr attachments
projects[apachesolr_attachments][patch][2677866] = https://www.drupal.org/files/issues/mysql-56-compatibility-2677866-12.patch
