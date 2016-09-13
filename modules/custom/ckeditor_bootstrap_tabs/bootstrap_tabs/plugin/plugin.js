/**
 * @file
 * Session Schedules plugin.
 *
 * @ignore
 */
/**
(function() {

 // "use strict";

  CKEDITOR.plugins.add('bootstrap_tabs', {
    requires: 'widget,dialog',
    icons: 'bootstrap_tabs',

    init: function(editor) {
      var maxGridColumns = 12;

      CKEDITOR.dialog.add('bootstrap_tabs', function(editor) {
        return {
          title: Drupal.t('Session Schedules'),
          minWidth: 200,
          minHeight: 100,
          contents: [{
            id: 'info',
            elements: [{
              id: 'type',
              type: 'select',
              label: Drupal.t('Columns count'),
              items: [
                [1, '1'],
                [2, '2'],
                [3, '3'],
                [4, '4'],
                [5, '5']
              ],
              required: true,
              setup: function(widget) {
                this.setValue(widget.data.colCount !== undefined ? widget.data.colCount : 5);
              },
              commit: function(widget) {
                widget.setData('colCount', this.getValue());
              }
            }]
          }]
        };
      });

      // Add widget
      editor.ui.addButton('SessionSchedules', {
        label: Drupal.t('Session Schedules'),
        command: 'bootstrap_tabs',
        icon: this.path + 'icons/bootstrap_tabs.png'
      });

      editor.widgets.add('bootstrap_tabs', {
        allowedContent: 'div(!bootstrap_tabs);',
        requiredContent: 'div(bootstrap_tabs)',
        parts: {
          bootstrap_tabs: 'div.bootstrap_tabs'
        },
        editables: {
          content: ''
        },
        template: '<div class="bootstrap_tabs"></div>',
        dialog: 'bootstrap_tabs',
        // Before init.
        upcast: function(element) {
          return element.name == 'div' && element.hasClass('bootstrap_tabs');
        },
        // Init function is useful after copy paste rebuild.
        init: function() {
          this.createEditable(maxGridColumns);
        },
        // Prepare data
        data: function() {
          if (this.data.colCount && this.element.getChildCount() < 1) {
            var colCount = this.data.colCount;
            var row = this.parts.bootstrap_tabs;
            this.createGrid(colCount, row);
          }
        },
        // Create grid
        createGrid: function(colCount, row) {
          var content = '<div class="container"><div class="row"><h2>SESSION SCHEDULES</h2>';
          for (var i = 1; i <= colCount; i++) {
            content = content + '<div class="columns">' +
              '  <h4>Session ' + i + ':</h4>' +
              '    <div class="date">{{ date }}</div>' +
              '    <div class="register-label">Registration opens:</div>' +
              '    <div class="register-date">{{ date }}</div>' +
              '</div>';
          }
          content = content + '</div></div>';
          row.appendHtml(content);
          this.createEditable(colCount);
        },
        // Create editable.
        createEditable: function(colCount) {
          this.initEditable('title', {
            selector: '.row h2'
          });
          for (var i = 1; i <= colCount; i++) {
            this.initEditable('h4' + i, {
              selector: '.row > .columns:nth-child(' + (i + 1) + ') h4'
            });
            this.initEditable('date' + i, {
              selector: '.row > .columns:nth-child(' + (i + 1) + ') .date'
            });
            this.initEditable('register-label' + i, {
              selector: '.row > .columns:nth-child(' + (i + 1) + ') .register-label'
            });
            this.initEditable('register-date' + i, {
              selector: '.row > .columns:nth-child(' + (i + 1) + ') .register-date'
            });
          }
        }
      });
    }
  });

})();
*/

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

      CKEDITOR.dialog.add( 'bootstrap_tabs', this.path + 'dialogs/dialog.js' );

      // Add CSS for edition state
      var cssPath = this.path + 'tabber.css';
      editor.on('mode', function () {
        if (editor.mode == 'wysiwyg') {
          this.document.appendStyleSheet(cssPath);
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
          content: ''
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
        // Num of plugins
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
            active = (i === 1) ? 'active' : '';
            tab_titles += '<li class="tab' + num + i + ' ' + active + '">' +
              '<a class="tab-title" href="#tab' + num + i + '" aria-controls="tab' + num + i + '" role="tab" data-toggle="tab">Tab' + i + '</a>' +
              '</li>';
            tab_content += '<div class="tab-pane ' + active + '" id="tab' + num + i + '">Content for tab' + i + '</div>';
          }
          // @todo user drupal theme
          content = '<div><ul class="nav nav-tabs" role="tablist">' + tab_titles + '</ul></div>' +
            '<div class="tab-content">' + tab_content + '</div>';
          row.appendHtml(content);
          this.createEditable(tabCount);
        },
        // Create editable.
        createEditable: function (tabCount) {
          console.log(tabCount);
          for (var i = 1; i <= tabCount; i++) {
            this.initEditable('tab_content' + i, {
              selector: '.tab-pane:nth-child(' + i + ')'
            });
          }
        }
      });

      // Context menu
      if (editor.contextMenu) {
        editor.addMenuGroup('tabGroup');
        editor.addMenuItem('tabBeforeItem', {
          label: Drupal.t('Add tab before'),
          icon: this.path + 'icons/' + iconToUse(),
          command: 'addTabBefore',
          group: 'tabGroup'
        });
        editor.addMenuItem('tabAfterItem', {
          label: Drupal.t('Add tab after'),
          icon: this.path + 'icons/' + iconToUse(),
          command: 'addTabAfter',
          group: 'tabGroup'
        });
        editor.addMenuItem('removeTab', {
          label: Drupal.t('Remove tab'),
          icon: this.path + 'icons/' + iconToUse(),
          command: 'removeTab',
          group: 'tabGroup'
        });

        editor.contextMenu.addListener(function (element) {
          console.log(element);
          if (element.getAscendant('a', true)) {
            return {
              //tabBeforeItem: CKEDITOR.TRISTATE_OFF,
              //tabAfterItem: CKEDITOR.TRISTATE_OFF,
              removeTab: CKEDITOR.TRISTATE_OFF
            };
          }
        });
      }

      editor.addCommand('removeTab', {
        exec: function (editor) {
          var element = editor.getSelection().getStartElement();
          var rm_element = null;
          console.log(element);
          if (element.getAscendant('div', true)) {
            rm_element = element.getAscendant('div', true);
            console.log(rm_element.getAttribute('id'));
            //a.getNext().remove();
            //a.remove();
          }
          else {
            var a = element.getAscendant('dd', true);
            a.getPrevious().remove();
            a.remove();
          }
        }
      });

      /*
      // Prevent nesting DLs by disabling button
      editor.on('selectionChange', function (evt) {
        if (editor.readOnly)
          return;
        var command = editor.getCommand('addTab'),
          element = evt.data.path.lastElement && evt.data.path.lastElement.getAscendant('dl', true);
        if (element)
          command.setState(CKEDITOR.TRISTATE_DISABLED);
        else
          command.setState(CKEDITOR.TRISTATE_OFF);
      });

      var allowedContent = 'dl dd dt (ckeditor-tabber)';



      // Other command to manipulate tabs
      editor.addCommand('addTabBefore', {
        allowedContent: allowedContent,

        exec: function (editor) {
          var element = editor.getSelection().getStartElement();
          var newHeader = new CKEDITOR.dom.element.createFromHtml('<dt>New tab title</dt>');
          var newContent = new CKEDITOR.dom.element.createFromHtml('<dd><p>New tab content</p></dd>');
          if (element.getAscendant('dd', true)) {
            element = element.getAscendant('dd', true).getPrevious();
          }
          else {
            element = element.getAscendant('dt', true);
          }
          newHeader.insertBefore(element);
          newContent.insertBefore(element);
        }
      });
      editor.addCommand('addTabAfter', {
        allowedContent: allowedContent,

        exec: function (editor) {
          var element = editor.getSelection().getStartElement();
          var newHeader = new CKEDITOR.dom.element.createFromHtml('<dt>New tab title</dt>');
          var newContent = new CKEDITOR.dom.element.createFromHtml('<dd><p>New tab content</p></dd>');
          if (element.getAscendant('dt', true)) {
            element = element.getAscendant('dt', true).getNext();
          }
          else {
            element = element.getAscendant('dd', true);
          }
          newContent.insertAfter(element);
          newHeader.insertAfter(element);
        }
      });


      */
    }
  });
})();
