<?php
/**
 * @file
 * wim_text_formats.features.wysiwyg.inc
 */

/**
 * Implements hook_wysiwyg_default_profiles().
 */
function wim_text_formats_wysiwyg_default_profiles() {
  $profiles = array();

  // Exported profile: filtered_html.
  $profiles['filtered_html'] = array(
    'format' => 'filtered_html',
    'editor' => 'ckeditor',
    'settings' => array(
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Undo' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Anchor' => 1,
          'Blockquote' => 1,
          'Source' => 1,
          'PasteText' => 1,
          'PasteFromWord' => 1,
          'RemoveFormat' => 1,
          'SpecialChar' => 1,
          'Format' => 1,
          'Table' => 1,
          'Find' => 1,
          'Replace' => 1,
          'Iframe' => 1,
          'Maximize' => 1,
        ),
        'ckeditor_abbrbutton' => array(
          'ckeditor_abbrbutton' => 1,
        ),
        'ckeditor_acronym_button' => array(
          'ckeditor_acronym_button' => 1,
        ),
        'ckeditor_definitionlist_button' => array(
          'ckeditor_definitionlist_button' => 1,
        ),
        'ckeditor_insertionbutton' => array(
          'ckeditor_insertionbutton' => 1,
        ),
        'ckeditor_languagebutton' => array(
          'ckeditor_languagebutton' => 1,
        ),
        'ckeditor_deletionbutton' => array(
          'ckeditor_deletionbutton' => 1,
        ),
        'a11ychecker' => array(
          'A11ychecker' => 1,
        ),
        'balloonpanel' => array(
          'Balloonpanel' => 1,
        ),
        'linkit' => array(
          'linkit' => 1,
        ),
        'drupal' => array(
          'media' => 1,
        ),
      ),
      'theme' => '',
      'language' => 'en',
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'acf_mode' => 0,
      'acf_allowed_content' => '',
      'css_setting' => 'none',
      'css_theme' => 'adminimal',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'forcePasteAsPlainText' => 0,
      'pasteFromWordPromptCleanup' => 0,
      'pasteFromWordRemoveFontStyles' => 0,
    ),
    'preferences' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'add_to_summaries' => 1,
      'version' => '4.10.1.59246e9',
    ),
    'name' => 'formatfiltered_html',
  );

  // Exported profile: full_html.
  $profiles['full_html'] = array(
    'format' => 'full_html',
    'editor' => 'ckeditor',
    'settings' => array(
      'buttons' => array(
        'default' => array(
          'Bold' => 1,
          'Italic' => 1,
          'BulletedList' => 1,
          'NumberedList' => 1,
          'Undo' => 1,
          'Link' => 1,
          'Unlink' => 1,
          'Anchor' => 1,
          'Blockquote' => 1,
          'Source' => 1,
          'PasteText' => 1,
          'PasteFromWord' => 1,
          'RemoveFormat' => 1,
          'SpecialChar' => 1,
          'Format' => 1,
          'Table' => 1,
          'Find' => 1,
          'Replace' => 1,
          'Iframe' => 1,
          'Maximize' => 1,
        ),
        'bootstrap_tabs' => array(
          'addTab' => 1,
        ),
        'ckeditor_abbrbutton' => array(
          'ckeditor_abbrbutton' => 1,
        ),
        'ckeditor_acronym_button' => array(
          'ckeditor_acronym_button' => 1,
        ),
        'ckeditor_definitionlist_button' => array(
          'ckeditor_definitionlist_button' => 1,
        ),
        'ckeditor_insertionbutton' => array(
          'ckeditor_insertionbutton' => 1,
        ),
        'ckeditor_languagebutton' => array(
          'ckeditor_languagebutton' => 1,
        ),
        'ckeditor_deletionbutton' => array(
          'ckeditor_deletionbutton' => 1,
        ),
        'a11ychecker' => array(
          'A11ychecker' => 1,
        ),
        'balloonpanel' => array(
          'Balloonpanel' => 1,
        ),
        'linkit' => array(
          'linkit' => 1,
        ),
        'drupal' => array(
          'media' => 1,
        ),
      ),
      'theme' => '',
      'language' => 'en',
      'toolbarLocation' => 'top',
      'resize_enabled' => 1,
      'default_toolbar_grouping' => 0,
      'simple_source_formatting' => 0,
      'acf_mode' => 0,
      'acf_allowed_content' => '',
      'css_setting' => 'none',
      'css_theme' => 'adminimal',
      'css_path' => '',
      'stylesSet' => '',
      'block_formats' => 'p,address,pre,h2,h3,h4,h5,h6,div',
      'forcePasteAsPlainText' => 0,
      'pasteFromWordPromptCleanup' => 0,
      'pasteFromWordRemoveFontStyles' => 0,
    ),
    'preferences' => array(
      'default' => 1,
      'user_choose' => 0,
      'show_toggle' => 1,
      'add_to_summaries' => 1,
      'version' => '4.10.1.59246e9',
    ),
    'name' => 'formatfull_html',
  );

  return $profiles;
}
