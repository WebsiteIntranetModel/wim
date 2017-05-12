/*
 Copyright (c) 2003-2009, CKSource - Frederico Knabben. All rights reserved.
 For licensing, see LICENSE.html or http://ckeditor.com/license
 */
CKEDITOR.plugins.add('ckeditor_languagebutton', {

  init: function (editor) {

    CKEDITOR.dialog.add('languageDialog', function (editor) {

      var ErrorMessage = 'Please enter a value';

      return {
        onShow: function () {
          var selection = null;
          if (CKEDITOR.env.ie) {
            selection = editor.getSelection().document.$.selection.createRange().text;
          } else {
            selection = editor.getSelection().getNative();
          }
          this.setupContent(selection);
        },

        title: 'Taal voor screenreader',
        minWidth: 250,
        minHeight: 250,
        contents: [{
          id: 'languageTab',
          label: 'first tab',
          title: 'fist tab title',
          elements: [
            {
              type: 'text',
              label: 'Tekst om weer te geven',
              id: 'languageDisplay',
              validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage),
              setup: function (element) {
                this.setValue(element);
              }
            },
            {
              type: 'select',
              label: 'Selecteer taal voor screenreader',
              id: 'languageSelect',
              'default': "",
              validate: CKEDITOR.dialog.validate.notEmpty(ErrorMessage),
              items: [['Engels', 'en'],
                ['Spaans', 'es'],
                ['Frans', 'fr'],
                ['Duits', 'de'],
                ['Portugees', 'pt']
              ]
            }
          ]
        }
        ],
        buttons: [CKEDITOR.dialog.okButton, CKEDITOR.dialog.cancelButton],
        onOk: function () {
          var languageSelect = this.getValueOf('languageTab', 'languageSelect');
          var languageDisplay = this.getValueOf('languageTab', 'languageDisplay');
          editor.insertHtml('<span class="language_selected" lang="' + languageSelect + '" xml:lang="' + languageSelect + '">' + languageDisplay + '</span>');
        }
      };
    });

    editor.addCommand('ckeditor_languagebutton', {
      exec: function (e) {
        e.openDialog('languageDialog');
      }
    });

    editor.ui.addButton('ckeditor_languagebutton', {
      label: 'Language',
      command: 'ckeditor_languagebutton',
      icon: this.path + '/language.png'
    });
  }

});
