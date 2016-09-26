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
          this.document.appendStyleSheet(Path + 'tabber.css');
        }
      });

      editor.on('instanceReady', function(event){
        if (event.name == 'mode' && event.editor.mode == 'source') {
          return;
        }

        var jQueryScriptTag = document.createElement('script');
        var editorHead = event.editor.document.$.head;
        jQueryScriptTag.src = Path + 'show-hide.js';
        editorHead.appendChild(jQueryScriptTag);
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
          nav: {selector: '.nav', allowedContent: 'ul li a'}
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
            tab_titles += '<li role="tabber" class="tab' + num + i + ' ' + active + '">' +
              '<a contenteditable="true" class="tab-title" href="#tab' + num + i + '" aria-controls="tab' + num + i + '" role="tab" data-toggle="tab">Tab' + i + '</a>' +
              '</li>';
            tab_content += '<div role="tabpanel" class="tab-pane ' + active + '" id="tab' + num + i + '">Content for tab' + i + '</div>';
          }
          // @todo user drupal theme
          content = '<ul class="nav nav-tabs" role="tablist">' + tab_titles + '</ul>' +
            '<div class="tab-content">' + tab_content + '</div>';
          row.appendHtml(content);
          this.createEditable(tabCount);
          this.initEditable('nav', {selector: '.nav', allowedContent: 'div ul li a'});
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
        editor.addMenuItem('titleText', {
          label: Drupal.t('Tab title'),
          icon: this.path + 'icons/' + iconToUse(),
          command: 'tabTitle',
          group: 'tabGroup',
          order: 1
        });

        editor.contextMenu.addListener(function (element) {
          if (element.getAscendant('a', true)) {
            return {
              //tabBeforeItem: CKEDITOR.TRISTATE_OFF,
              //tabAfterItem: CKEDITOR.TRISTATE_OFF,
              titleText: CKEDITOR.TRISTATE_OFF,
              removeTab: CKEDITOR.TRISTATE_OFF
            };
          }
        });
      }

      editor.addCommand('tabTitle', new CKEDITOR.dialogCommand('tab_title_dialog', {
        allowedContent: ''
      }));

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
