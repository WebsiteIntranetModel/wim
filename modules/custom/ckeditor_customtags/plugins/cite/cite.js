/*
Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
For licensing, see LICENSE.html or http://ckeditor.com/license
*/
CKEDITOR.plugins.add('ckeditor_citebutton', {
  init: function( editor ) {
    editor.addCommand('ckeditor_citebutton', {
      exec: function(e) {
        var mySelection = editor.getSelection();
        if (CKEDITOR.env.ie) {
            mySelection.unlock(true);
            selectedText = mySelection.getNative().createRange().text;
        } else {
            selectedText = mySelection.getNative();
        }
        
        var element = '<cite>' + selectedText + '</cite>';
        editor.insertHtml(element);
      }
    });
    editor.ui.addButton('ckeditor_citebutton', {
      label: 'Citation',
      command: 'ckeditor_citebutton',
      icon: this.path + '/cite.png'
    }); 
  }
});