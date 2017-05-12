/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */
CKEDITOR.plugins.add('ckeditor_insertionbutton', {
  init: function (editor) {
    editor.addCommand('ckeditor_insertionbutton', {
      exec: function (e) {
        var mySelection = editor.getSelection();
        var selectedText = '';

        if (CKEDITOR.env.ie) {
          mySelection.unlock(true);
          selectedText = mySelection.getNative().createRange().text;
        } else {
          selectedText = mySelection.getNative();
        }

        var element = '<ins>' + selectedText + '</ins>';
        editor.insertHtml(element);
      }
    });
    editor.ui.addButton('ckeditor_insertionbutton', {
      label: 'Insertion',
      command: 'ckeditor_insertionbutton',
      icon: this.path + '/insertion.png'
    });
  }
});
