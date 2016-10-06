(function () {
  // Detect icon.
  function iconToUse() {
    var ua = window.navigator.userAgent;
    var msie = ua.indexOf("MSIE ");

    if (msie > 0) {
      return 'tab.png';
    }
    return 'tab.svg';
  }

  // Register plugin
  CKEDITOR.plugins.add('bootstrap_tabs', {
    requires: 'widget',

    init: function (editor) {

      var maxTabColumns = 12;
      // Add single button.
      editor.ui.addButton('addTab', {
        command: 'bootstrap_tabs',
        icon: this.path + 'icons/' + iconToUse(),
        label: Drupal.t('Insert tabs')
      });

      CKEDITOR.dialog.add('bootstrap_tabs', this.path + 'dialogs/dialog.js');
      CKEDITOR.dialog.add('tab_title_dialog', this.path + 'dialogs/title.js');

      // Add CSS for edition state
      var Path = this.path;
      editor.on('mode', function () {
        if (editor.mode == 'wysiwyg') {
          this.document.appendStyleSheet(Path + 'additional.css');
        }
      });

      // Add widget.
      editor.widgets.add('bootstrap_tabs', {
        allowedContent: 'div(!bootstrap-tab);',
        requiredContent: 'div(bootstrap-tab)',
        parts: {
          bootstrap_tabs: 'div.bootstrap-tab'
        },
        editables: {
          content: '',
          nav: {selector: '.tabnav', allowedContent: 'ul[!role](nav, nav-tabs); li[!role](active); a[!href, !aria-controls, !role, !data-toggle]'}
        },
        template: '<div class="bootstrap-tab"></div>',
        dialog: 'bootstrap_tabs',
        // Before init.
        upcast: function (element) {
          return element.name == 'div' && element.hasClass('bootstrap-tab');
        },
        // Init function is useful after copy paste rebuild.
        init: function () {
          this.createEditable(maxTabColumns);
        },
        // Prepare data
        data: function () {
          if (this.data.tabCount && this.element.getChildCount() < 1) {
            var tabCount = this.data.tabCount;
            var row = this.parts.bootstrap_tabs;
            this.createGrid(tabCount, row, this.numOfWidgets());
          }
        },
        // Number of widgets.
        numOfWidgets: function () {
          var length = 0;
          for (var key in editor.widgets.instances) {
            if (editor.widgets.instances.hasOwnProperty(key)) {
              length++;
            }
          }
          return length;
        },
        // Create grid
        createGrid: function (tabCount, row, num) {
          var active = '';
          var tab_titles = '';
          var tab_content = '';
          for (var i = 1; i <= tabCount; i++) {
            active = (i === 1) ? ' active' : '';
            tab_titles += '<li role="presentation" class="' + active + '">' +
              '<a href="#tab' + num + '-' + i + '" aria-controls="tab' + num + '-' + i + '" role="tab" data-toggle="tab">Tab' + i + '</a>' +
              '</li>';
            tab_content += '<div role="tabpanel" class="tab-pane' + active + '" id="tab' + num + '-' + i + '">Content for tab' + i + '</div>';
          }
          var content = '<div class="tabnav"><ul class="nav nav-tabs" role="tablist">' + tab_titles + '</ul></div>' +
            '<div class="tab-content">' + tab_content + '</div>';
          row.appendHtml(content);
          this.createEditable(tabCount);
          this.initEditable('nav', {selector: '.tabnav', allowedContent: 'ul[!role](nav, nav-tabs); li[!role](active); a[!href, !aria-controls, !role, !data-toggle]'});
        },
        // Create editable.
        createEditable: function (tabCount) {
          for (var i = 1; i <= tabCount; i++) {
            this.initEditable('tab_content' + i, {
              selector: '.tab-pane:nth-child(' + i + ')'
            });
          }
        }
      });

      // Context menu
      if (editor.contextMenu) {
        var icon = iconToUse();
        editor.addMenuGroup('tabGroup');
        editor.addMenuItem('tabBeforeItem', {
          label: Drupal.t('Add tab before'),
          icon: this.path + 'icons/' + icon,
          command: 'tabBefore',
          group: 'tabGroup'
        });
        editor.addMenuItem('tabAfterItem', {
          label: Drupal.t('Add tab after'),
          icon: this.path + 'icons/' + icon,
          command: 'tabAfter',
          group: 'tabGroup'
        });
        editor.addMenuItem('removeTab', {
          label: Drupal.t('Remove tab'),
          icon: this.path + 'icons/' + icon,
          command: 'tabRemove',
          group: 'tabGroup'
        });
        editor.addMenuItem('titleText', {
          label: Drupal.t('Tab title'),
          icon: this.path + 'icons/' + icon,
          command: 'tabTitle',
          group: 'tabGroup',
          order: 1
        });

        editor.contextMenu.addListener(function (element) {
          if (element.getAscendant('a', true)) {
            return {
              tabBeforeItem: CKEDITOR.TRISTATE_OFF,
              tabAfterItem: CKEDITOR.TRISTATE_OFF,
              titleText: CKEDITOR.TRISTATE_OFF,
              removeTab: CKEDITOR.TRISTATE_OFF
            };
          }
        });
      }

      editor.addCommand('tabTitle', new CKEDITOR.dialogCommand('tab_title_dialog', {
        allowedContent: ''
      }));

      editor.addCommand('tabRemove', {
        exec: function (editor) {
          var element = editor.getSelection().getStartElement();
          var id = element.getAttribute('href');
          if (element.hasAscendant('li') && id) {
            if (id.substring(0, 1) == '#') {
              id = id.substring(1);
            }
            element.getAscendant('li').remove();
            editor.document.getById(id).remove();
          }
        }
      });

      // Function to reinit new tab.
      var initEditableTab = function (i) {
        for (var key in editor.widgets.instances) {
          if (editor.widgets.instances.hasOwnProperty(key)) {
            if (editor.widgets.instances[key].name === 'bootstrap_tabs') {
              editor.widgets.instances[key].initEditable('tab_content' + i, {
                selector: '#' + i
              });
            }
          }
        }
      };

      /**
       * Add tab helper function.
       *
       * @param {CKEDITOR.editor} editor The nested editable name.
       * @param {string} where Accept 'before' and 'after'.
       */
      var addTab = function (editor, where) {
        var element = editor.getSelection().getStartElement();
        if (element) {
          var id = element.getAttribute('href');

          if (element.hasAscendant('li') && id) {
            if (id.substring(0, 1) == '#') {
              id = id.substring(1);
            }
            var parts = id.split('-');
            var num = parts[0];
            var listItem = element.getAscendant('li');
            var count = listItem.getParent().getChildCount() + 1;
            var tab = '<li role="presentation">' +
              '<a href="#tab' + num + '-' + count + '" aria-controls="tab' + num + '-' + count + '" role="tab" data-toggle="tab">Tab' + count + '</a>' +
              '</li>';
            var newTab = new CKEDITOR.dom.element.createFromHtml(tab);
            var content = '<div role="tabpanel" class="tab-pane" id="tab' + num + '-' + count + '">Content for tab' + count + '</div>';
            var newTabContent = new CKEDITOR.dom.element.createFromHtml(content);
            if (where === 'before') {
              newTab.insertBefore(listItem);
              newTabContent.insertBefore(editor.document.getById(id));
            } else {
              newTab.insertAfter(listItem);
              newTabContent.insertAfter(editor.document.getById(id));
            }

            initEditableTab('tab' + num + '-' + count);
          }
        }
      };

      editor.addCommand('tabBefore', {
        exec: function (editor) {
          addTab(editor, 'before');
        }
      });

      editor.addCommand('tabAfter', {
        exec: function (editor) {
          addTab(editor, 'after');
        }
      });
    }
  });
})();
