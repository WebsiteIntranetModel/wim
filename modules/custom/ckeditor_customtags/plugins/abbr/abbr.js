/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */

CKEDITOR.plugins.add('ckeditor_abbrbutton', {
  init: function (editor) {

    CKEDITOR.dialog.add('abbrDialog', function (editor) {
      var ErrorMessage = 'Please enter a value';

      return {
        onOk: function () {
          var abbrTitle = this.getValueOf('tab1', 'abbrtitle');
          var abbrDisplay = this.getValueOf('tab1', 'abbrDisplay');
          var newElement = '';

          if (abbrTitle != '') {
            newElement = '<abbr title="' + abbrTitle + '">' + abbrDisplay + '</abbr>';
          }
          else {
            newElement = '<abbr>' + abbrDisplay + '</abbr>';
          }

          editor.insertHtml(newElement);

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
        title: 'Abbreviation',
        minWidth: 250,
        minHeight: 250,
        contents: [{
          id: 'tab1',
          label: 'first tab',
          title: 'fist tab title',
          elements: [{
            type: 'text',
            label: 'Abbreviation',
            id: 'abbrDisplay',
            setup: function (element) {
              this.setValue(element);
            },
            //validate : CKEDITOR.dialog.validate.notEmpty(ErrorMessage)

          },
            {
              type: 'text',
              label: 'Abbreviation Title (displayed on hover)',
              id: 'abbrtitle',
              'default': '',
              //validate : CKEDITOR.dialog.validate.notEmpty(ErrorMessage)
            }]
        }]
      };
    });
    editor.addCommand('ckeditor_abbrbutton', {
      exec: function (e) {
        e.openDialog('abbrDialog');
      }
    });
    editor.ui.addButton('ckeditor_abbrbutton', {
      label: 'Abbreviation',
      command: 'ckeditor_abbrbutton',
      icon: this.path + '/abbr.png'
    });
  }

});


