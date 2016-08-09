/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */

CKEDITOR.plugins.add('ckeditor_deletionbutton', {
  init: function (editor) {
    editor.addCommand('ckeditor_deletionbutton', {
      exec: function (e) {
        var mySelection = editor.getSelection();
        var selectedText = '';
        if (CKEDITOR.env.ie) {
          mySelection.unlock(true);
          selectedText = mySelection.getNative().createRange().text;
        } else {
          selectedText = mySelection.getNative();
        }

        var element = '<del>' + selectedText + '</del>';
        editor.insertHtml(element);
      }
    });

    editor.ui.addButton('ckeditor_deletionbutton', {
      label: 'Deletion',
      command: 'ckeditor_deletionbutton',
      icon: this.path + '/deletion.png'
    });

  }
});
