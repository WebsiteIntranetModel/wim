/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */

CKEDITOR.plugins.add('ckeditor_definitionlist_button', {

  init: function (editor) {

    CKEDITOR.dialog.add('definitionDialog', function (editor) {

      var ErrorMessage = 'Please enter a value';

      return {
        onOk: function () {
          var definitionTerm = this.getValueOf('tab1', 'definitionTerm');
          var definitionData = this.getValueOf('tab1', 'definitionData');

          // the empty <p> is to get out of the scope of the definition list, otherwise you will stay in the <dd>
          var data = '<dl><dt>' + definitionTerm + '</dt><dd>' + definitionData + '</dd></dl><p></p>';
          editor.insertHtml(data);
        },
        onShow: function () {
          var selection = null;

          if (CKEDITOR.env.ie) {
            selection = editor.getSelection().document.$.selection.createRange().text;
          } else {
            selection = editor.getSelection().getNative();
          }
          this.setupContent(selection);
        },

        title: 'Definition List',
        minWidth: 450,
        minHeight: 250,
        contents: [{
          id: 'tab1',
          label: 'first tab',
          title: 'fist tab title',
          elements: [{
            type: 'text',
            label: 'Definition Term',
            id: 'definitionTerm',
            setup: function (element) {
              this.setValue(element);
            },
            validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage)
          },
            {
              type: 'text',
              label: 'Definition Data',
              id: 'definitionData',
              'default': '',
              validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage)
            }]
        }]
      };
    });

    editor.addCommand('ckeditor_definitionlist_button', {
      exec: function (e) {
        e.openDialog('definitionDialog');
      }
    });

    editor.ui.addButton('ckeditor_definitionlist_button', {
      label: 'Definition List',
      command: 'ckeditor_definitionlist_button',
      icon: this.path + '/definition-list.gif'
    });
  }
});



