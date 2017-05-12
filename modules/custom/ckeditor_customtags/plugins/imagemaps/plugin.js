CKEDITOR.plugins.add('imagemaps',
  {
    requires: ['dialog'],
    // translations
    lang: ['en', 'de', 'el', 'es', 'it', 'nl', 'sv', 'tr'],

    init: function (editor) {
      var icon = this.path + 'icon.png';

      CKEDITOR.dialog.add('ImageMaps', this.path + 'dialog/imagemaps.js');

      var imagemapCommand = editor.addCommand('ImageMaps', new CKEDITOR.dialogCommand('ImageMaps', {
        allowedContent: 'img[usemap];map[id,name];area[alt,coords,shape,target,title,url]'
      }));

      imagemapCommand.startDisabled = true;

      editor.ui.addButton('ImageMaps',
        {
          label: editor.lang.imagemaps.toolbar,
          command: 'ImageMaps',
          icon: icon
        });

      // If the "menu" plugin is loaded, register the menu items.
      if (editor.addMenuItems) {
        editor.addMenuItems(
          {
            imagemap: {
              label: editor.lang.imagemaps.menu,
              command: 'ImageMaps',
              group: 'image',
              order: 1,
              icon: icon
            }
          });
      }

      // If the "contextmenu" plugin is loaded, register the listeners.
      if (editor.contextMenu) {
        // check the image
        editor.contextMenu.addListener(function (element, selection) {
          if (!element || !element.is('img') || (element.data && element.data('cke-realelement')) || element.isReadOnly())
            return null;

          // And say that this context menu item must be shown
          return {imagemap: ( element.hasAttribute('usemap') ? CKEDITOR.TRISTATE_ON : CKEDITOR.TRISTATE_ON )};
        });
      }

      // Open our dialog on double click
      editor.on('doubleclick', function (evt) {
        var element = evt.data.element,
          editor = evt.editor;

        // Firefox: we can click on the "area" element, and then we won't get the good img node
        if (element.is('area')) {
          var map = element.getParent().$,
            id = map.getAttribute('id'),
            doc = editor.document.$,
            img;

          if (doc.querySelector) {
            img = doc.querySelector('img[usemap="#' + id + '"]');
          }
          if (img) {
            editor.getSelection().selectElement(new CKEDITOR.dom.element(img));

            evt.data.dialog = 'ImageMaps';
            return;
          }
        }

        if (element.is('img') && element.hasAttribute('usemap')) {
          editor.getSelection().selectElement(element);
          evt.data.dialog = 'ImageMaps';
        }
        // set the listener after the default ones
      }, null, null, 20);

      // Register the state changing handlers.
      editor.on('selectionChange', CKEDITOR.tools.bind(function (evt) {
        var editor = evt.editor,
          elementPath = evt.data.path,
          element = elementPath.lastElement;

        if (!element || !element.is('img')) {
          this.setState(CKEDITOR.TRISTATE_DISABLED);
          return;
        }

        this.setState(element.hasAttribute('usemap') ? CKEDITOR.TRISTATE_ON : CKEDITOR.TRISTATE_OFF);
      }, imagemapCommand));


      // IE already provides its own preview
      if (CKEDITOR.env.ie)
        return;

      // Watch image dialog
      CKEDITOR.on('dialogDefinition', function (e) {
        if (e.data.name != 'image')
          return;

        var definition = e.data.definition;

        e.removeListener();

        definition.onOk = CKEDITOR.tools.override(definition.onOk, function (original) {
          return function () {
            original.call(this);
            var img = this.imageElement,
              mapName = img.getAttribute('usemap');

            if (!mapName)
              return;
            var map = editor.document.getById(mapName.substr(1));
            if (!map)
              return;

            CKEDITOR.plugins.imagemaps.drawMap(img.$, map.$);

          };
        });
      });

      editor.on('contentDom', function (e) {
        var doc = e.editor.document.$,
          maps = doc.getElementsByTagName('map');

        for (var i = 0; i < maps.length; i++) {
          var map = maps[i],
            name = map.name,
            img = doc.querySelector('img[usemap="#' + name + '"]');
          if (img)
            CKEDITOR.plugins.imagemaps.drawMap(img, map);
        }

      });

      if (!CKEDITOR.plugins.imagemaps)
        CKEDITOR.plugins.imagemaps = {};

      CKEDITOR.plugins.imagemaps.drawMap = function (img, map) {
        if (CKEDITOR.env.ie)
          return;

        if (!img.width) {
          var onLoad = function (ev) {
            img.removeEventListener('load', onLoad);
            CKEDITOR.plugins.imagemaps.drawMap(img, map);
          };

          img.addEventListener('load', onLoad, false);
          return;
        }

        var doc = img.ownerDocument,
          canvas = doc.createElement('canvas');

        canvas.setAttribute('width', img.width);
        canvas.setAttribute('height', img.height);

        var context = canvas.getContext('2d'),
          src = img.src;
        if (img.attributes['data-cke-saved-src']) {
          var tmpImg = new Image();
          src = img.attributes['data-cke-saved-src'].nodeValue;
          tmpImg.src = src;
          tmpImg.width = img.width;
          tmpImg.height = img.height;

          context.drawImage(tmpImg, 0, 0, img.width, img.height);
        }
        else
          context.drawImage(img, 0, 0, img.width, img.height);

        context.strokeStyle = "#DDDDDD";
        context.lineWidth = 1;

        context.shadowOffsetX = 0;
        context.shadowOffsetY = 0;
        context.shadowBlur = 3;
        context.shadowColor = "#333333";

        for (var i = 0; i < map.areas.length; i++) {
          var area = map.areas[i],
            coords = area.coords.split(',');
          switch (area.shape) {
            case 'circle':
              context.beginPath();
              context.arc(coords[0], coords[1], coords[2], 0, Math.PI * 2, true);
              context.closePath();
              context.stroke();
              break;

            case 'poly':
              context.beginPath();
              context.moveTo(coords[0], coords[1]);
              for (var j = 2; j < coords.length; j += 2) {
                context.lineTo(coords[j], coords[j + 1]);
              }
              context.closePath();
              context.stroke();
              break;

            default:
              context.strokeRect(coords[0], coords[1], coords[2] - coords[0], coords[3] - coords[1]);
              break;
          }
        }

        try {
          img.src = canvas.toDataURL();
        }
        catch (e) {
          // Ignore security exceptions if the image is external and can't be used
        }
      }
    }, //init

    afterInit: function (editor) {
      var dataProcessor = editor.dataProcessor,
        htmlFilter = dataProcessor && dataProcessor.htmlFilter,
        dataFilter = dataProcessor && dataProcessor.dataFilter;

      // htmlFilter : conversion from internal data to html output.
      htmlFilter.addRules(
        {
          elements: {
            map: function (element) {
              // IE in quirks sets id on the map but not the name
              if (element.attributes.id && !element.attributes.name) {
                element.attributes.name = element.attributes.id;
              }

              // Clean up orphan maps
              if (editor.document.$.querySelector) {
                var img = editor.document.$.querySelector('img[usemap="#' + element.attributes.name + '"]');
                if (!img)
                  return false;
              }

              return element;
            }
          }
        });
    } // afterInit
  });

/*
 Compatibility between CKEditor 3 and 4
 */
if (CKEDITOR.skins) {
  CKEDITOR.plugins.setLang = CKEDITOR.tools.override(CKEDITOR.plugins.setLang, function (originalFunction) {
    return function (plugin, lang, obj) {
      if (plugin != "devtools" && typeof obj[plugin] != 'object') {
        var newObj = {};
        newObj[plugin] = obj;
        obj = newObj;
      }
      originalFunction.call(this, plugin, lang, obj);
    }
  });
}
