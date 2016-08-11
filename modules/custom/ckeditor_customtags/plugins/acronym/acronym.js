/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */

CKEDITOR.plugins.add('ckeditor_acronym_button', {

  init: function (editor) {

    CKEDITOR.dialog.add('acronymDialog', function (editor) {

      var ErrorMessage = 'Please enter a value';

      return {
        onOk: function () {

          var acronymTitle = this.getValueOf('acronymTab', 'acronymtitle');
          var acronymDisplay = this.getValueOf('acronymTab', 'acronymDisplay');
          var newElement = CKEDITOR.dom.element.createFromHtml('<acronym title="' + acronymTitle + '">' + acronymDisplay + '</acronym>');
          editor.insertElement(newElement);

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

        title: 'Acronym',
        minWidth: 250,
        minHeight: 250,
        contents: [{
          id: 'acronymTab',
          label: 'first tab',
          title: 'fist tab title',
          elements: [{
            type: 'text',
            label: 'Acronym',
            id: 'acronymDisplay',
            setup: function (element) {
              this.setValue(element);
            },
            validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage)

          },
            {
              type: 'text',
              label: 'Acronym Title (displayed on hover)',
              id: 'acronymtitle',
              'default': '',
              validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage)
            }]
        }]
      };
    });

    editor.addCommand('ckeditor_acronym_button', {
      exec: function (e) {
        e.openDialog('acronymDialog');
      }
    });

    editor.ui.addButton('ckeditor_acronym_button', {
      label: 'Acronym',
      command: 'ckeditor_acronym_button',
      icon: this.path + '/acronym.png'
    });
  }
});



