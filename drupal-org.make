api = 2
core = 7.x

; Default configuration
defaults[projects][subdir] = contrib

; Contrib
projects[admin_menu][version] = 3.0-rc6
projects[admin_views][version] = 1.7
projects[adminimal_admin_menu][version] = 1.9
projects[antibot][version] = 1.2
projects[apachesolr][version] = 1.8
projects[apachesolr_attachments][version] = 1.x-dev
projects[apachesolr_autocomplete][version] = 1.6
projects[apachesolr_exclude_node][version] = 1.4
projects[autologout][version] = 4.5
projects[bean][version] = 1.11
projects[breakpoints][version] = 1.4
projects[bootstrap_fieldgroup][version] = 1.2
projects[captcha][version] = 1.5
projects[context][version] = 3.10
projects[context_condition_theme][version] = 1.0
projects[colectomy][version] = 1.0-beta2
projects[chosen][version] = 2.0
projects[ctools][version] = 1.11
projects[date][version] = 2.9
projects[date_facets][version] = 1.0
projects[diff][version] = 3.3
projects[elysia_cron][version] = 2.4
projects[email][version] = 1.3
projects[encrypt][version] = 2.3
projects[entity][version] = 1.9
projects[entityreference][version] = 1.5
projects[facetapi][version] = 1.6
projects[features][version] = 2.11
projects[felix][version] = 1.0-beta9
projects[field_group][version] = 1.5
projects[file_entity][version] = 2.4
projects[flood_control][version] = 1.0
projects[hansel][version] = 1.6
projects[i18n][version] = 1.15
projects[jquery_update][version] = 3.0-alpha5
projects[location][version] = 3.7
projects[logging_alerts][version] = 2.2
projects[login_destination][version] = 1.4
projects[magic][version] = 2.3
projects[mailsystem][version] = 2.34
projects[mass_contact][version] = 1.x-dev
projects[media][version] = 2.19
projects[menu_block][version] = 2.7
projects[menu_icons][version] = 3.0-beta4
projects[metatag][version] = 1.21
projects[migrate][version] = 2.11
projects[mimemail][version] = 1.1
projects[module_filter][version] = 2.2
projects[multiform][version] = 1.4
projects[nodequeue][version] = 2.2
projects[node_clone][version] = 1.0
projects[l10n_update][version] = 2.3
projects[link][version] = 1.6
projects[libraries][version] = 2.3
projects[linkit][version] = 3.5
projects[paragraphs][version] = 1.0-rc5
projects[password_policy][version] = 1.16
projects[pathauto][version] = 1.3
projects[picture][version] = 2.13
projects[plupload][version] = 1.7
projects[recaptcha][version] = 2.3
projects[revisioning][version] = 1.9
projects[roleassign][version] = 1.1
projects[scheduler][version] = 1.5
projects[strongarm][version] = 2.0
projects[special_menu_items][version] = 2.0
projects[smart_trim][version] = 1.5
projects[seckit][version] = 1.11
projects[token][version] = 1.7
projects[userprotect][version] = 1.2
projects[variable][version] = 2.5
projects[views][version] = 3.23
projects[views_aggregator][version] = 1.4
projects[views_bootstrap][version] = 3.1
projects[views_bulk_operations][version] = 3.4
projects[webform][version] = 4.21
projects[webform_autofill_attribute][version] = 1.2
projects[webform_clear][version] = 2.0
projects[webform_encrypt][version] = 1.2
projects[weight][version] = 3.1
projects[wysiwyg][version] = 2.x-dev
projects[xmlsitemap][version] = 2.4

; Get a specific commit of redirect so patch below will always apply
projects[redirect][version] = 1.x-dev
projects[redirect][download][type] = "git"
projects[redirect][download][url] = "http://git.drupal.org/project/redirect.git"
projects[redirect][download][revision] = "add3c695f613fbeec23b7259e59936f60a6b6da6"

; Themes
projects[adminimal_theme] = 1.24
projects[bootstrap] = 3.22

; Patches
; Features
; Fixing bug when Features module can't include file containing exported taxonomy vocabulary because it hasn't included file integrating Features with Taxonomy yet.
; https://www.drupal.org/node/2143765#comment-10088780
projects[features][patch][2143765_7] = https://www.drupal.org/files/issues/features-hook_modules_enabled_include_file_issue-2143765-7.patch

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
projects[location][patch][2781227_4] = https://www.drupal.org/files/issues/location-google-maps-link-2781227-2.patch

; Bean
; Add migration support for Bean
; https://www.drupal.org/node/2295973#comment-11536795
projects[bean][patch][2295973_11] = https://www.drupal.org/files/issues/bean-migrate-support-2295973-11.patch

; Fix view modes for Bean blocks
; https://www.drupal.org/node/1911234
projects[bean][patch][1911234_6] = https://www.drupal.org/files/issues/select-from-enabled-view-modes-1911234-6.patch

; Views
; Add plural format to views_handler_area_result
; https://www.drupal.org/project/views/issues/1793500#comment-13114869
projects[views][patch][1793500_13] = https://www.drupal.org/files/issues/2019-05-21/views-area-results-plural-1793500-14.patch

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

; Link
; URL validation rejects existing valid content after upgrade to 7.x-1.4
; https://www.drupal.org/node/2666912
projects[link][patch][2666912] = https://www.drupal.org/files/issues/2019-01-24/link-revert_url_validation-2666912-7.x-1.5.patch

; Linkit
; Allow Linkit support for any eligible element type
; https://www.drupal.org/node/2651404
projects[linkit][patch][2651404] = https://www.drupal.org/files/issues/linkit-add-to-any-element-2651404-3.patch
; Support for default drupal menu system
; https://www.drupal.org/node/2514928
projects[linkit][patch][2514928] = https://www.drupal.org/files/issues/linkit-menu-links-2514928-9.patch

; Redirect
; Provide redirect to alias from internal path functionality from globalredirect
; https://www.drupal.org/node/905914
projects[redirect][patch][905914] = https://www.drupal.org/files/issues/redirect-merge_global_redirect-905914-246-d7.patch

; Slick
libraries[slick][download][type] = get
libraries[slick][download][url] = https://github.com/kenwheeler/slick/archive/1.8.0.zip

; Chosen
libraries[chosen][download][type] = get
libraries[chosen][download][url] = https://github.com/harvesthq/chosen/releases/download/v1.6.2/chosen_v1.6.2.zip

; CKEditor 4.14.0
libraries[ckeditor][download][type] = get
libraries[ckeditor][download][url] = https://download.cksource.com/CKEditor/CKEditor/CKEditor%204.14.0/ckeditor_4.14.0_full.zip

; Apachesolr attachments
projects[apachesolr_attachments][patch][2677866] = https://www.drupal.org/files/issues/mysql-56-compatibility-2677866-12.patch
projects[apachesolr_attachments][patch][1908484] = https://www.drupal.org/files/issues/apachesolr-attachments-index-unattached-files-1908484-13.patch

; Mass Contact - Add possibility to send mail to blocked users
projects[mass_contact][patch][787168] = https://www.drupal.org/files/issues/2019-06-06/787168-13.patch

; Bootstrap - Add labels to search form output for accessibility
projects[bootstrap][patch][2540856] = https://www.drupal.org/files/issues/label_accessibility_label_missing_from_search_block-2540856-6.patch
