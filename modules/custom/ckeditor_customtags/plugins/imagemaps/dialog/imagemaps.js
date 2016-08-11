(function() {

/**
 *	Functions to use with imgmap
 *	@author amla
 *	@author adam
 *	@author sroebj
 */

var myimgmap,
	img_obj,
	map_obj,
	previousModeImg,
	theDialog;

// We need to store here the area id because if the user clicks on an area,
// then the onSelectArea event will fire before the onchange or onblur of the editing inputs
var currentAreaId = null;


// An area has been selected in the image
function onSelectArea(obj) {
	setPropertiesVisible( true );

	updateAreaValues();

	currentAreaId = obj.aid;
	theDialog.setValueOf( 'info', 'href', obj.ahref);
	theDialog.setValueOf( 'info', 'target', obj.atarget || 'notSet' );
	theDialog.setValueOf( 'info', 'alt', obj.aalt);
	theDialog.setValueOf( 'info', 'title', obj.atitle);
}

// A new area has been added
function onAddArea(id) {
	setPropertiesVisible( true );

	updateAreaValues();

	currentAreaId = id;
	theDialog.getContentElement( 'info', 'href' ).setValue( '', true );
	theDialog.getContentElement( 'info', 'target' ).setValue( 'notSet', true );
	theDialog.getContentElement( 'info', 'alt' ).setValue( '', true );
	theDialog.getContentElement( 'info', 'title' ).setValue( '', true );
}

function onRemoveArea()
{
	currentAreaId = null;
	setPropertiesVisible( false );
}

function setPropertiesVisible( show )
{
	for(var i=1; i<=2; i++)
	{
		var row = theDialog.getContentElement('info', 'properties' + i),
			element = row.getElement();
		if (show)
			element.setStyle('visibility', '');
		else
			element.setStyle('visibility', 'hidden');
	}
}

function updateAreaValues()
{
	if (currentAreaId !== null)
	{
		myimgmap.areas[currentAreaId].ahref = theDialog.getValueOf( 'info', 'href' );
		myimgmap.areas[currentAreaId].aalt = theDialog.getValueOf( 'info', 'alt' );
		myimgmap.areas[currentAreaId].atitle = theDialog.getValueOf( 'info', 'title' );
	}
}

function setMode(mode)
{
	if (mode == 'pointer') {
		myimgmap.is_drawing = 0;
		myimgmap.nextShape = '';
	}
	else {
		myimgmap.nextShape = mode;
	}

	highlightMode(mode);
}

function highlightMode(mode)
{
	// Reset previous button
	if ( previousModeImg )
		previousModeImg.removeClass( 'imgmapButtonActive' );

	// Highlight new mode
	previousModeImg = theDialog.getContentElement('info', 'btn_' + mode).getElement();
	previousModeImg.addClass( 'imgmapButtonActive' );
}


/* Call our custom version to protect URLs */

function getMapInnerHTML( imgmap )
{
	var html = '';
	//foreach area properties
	for (var i=0; i< imgmap.areas.length; i++) {
		html+= getAreaHtml( imgmap.areas[i] );
	}
	return html;
}

// Protect urls and add only the used attributes
function getAreaHtml(area)
{
	if ( !area || area.shape === '')
		return '';

	var html = '<area shape="' + area.shape + '"' +
					' coords="' + area.lastInput + '"';

	if ( area.aalt ) html+= ' alt="' + area.aalt + '"';
	if ( area.atitle ) html+= ' title="' + area.atitle + '"';
	if ( area.ahref ) html+= ' href="' +	area.ahref + '" data-cke-saved-href="' + area.ahref + '"';
	if ( area.atarget && area.atarget != 'notSet' ) html+= ' target="' + area.atarget + '"';

	html+='/>';
	return html;
}

/* edit the properties of an area */

function SetAreaProperty()
{
	var id = currentAreaId;
	if ( id !== null)
	{
		myimgmap.areas[id][ "a" + this.id ] = this.getValue();
		myimgmap._recalculate(id);
	}
}


CKEDITOR.dialog.add( 'ImageMaps', function( editor )
{
	var lang = editor.lang.imagemaps,
		generalLabel = editor.lang.common.generalTab,
		pic_containerId = 'pic_container' + CKEDITOR.tools.getNextNumber(),
		statusContainerId = 'StatusContainer' + CKEDITOR.tools.getNextNumber(),
		plugin = editor.plugins.imagemaps,
		dialogReady = false;

	if (CKEDITOR.env.ie && typeof window.CanvasRenderingContext2D == 'undefined')
		CKEDITOR.scriptLoader.load( plugin.path + "dialog/excanvas.js", show);

	if (typeof imgmap=='undefined')
		CKEDITOR.scriptLoader.load( plugin.path + "dialog/imgmap.js", show);
//		CKEDITOR.scriptLoader.load( plugin.path + "dialog/imgmap_packed.js", show);

	var content = "",
		node = CKEDITOR.document.getHead().append( 'style' );
	node.setAttribute( "type", "text/css" );
	content += '.imgmapButton {cursor:pointer; background: url("' + plugin.path + 'images/sprite.png") no-repeat top left; width: 16px; height: 16px; display:inline-block;}';
	content += '.imgmapButtonActive {outline:1px solid #666; background-color:#ddd;}';

	if ( CKEDITOR.env.ie )
		node.$.styleSheet.cssText = content;
	else
		node.$.innerHTML = content;


function show()
{
	if (!dialogReady)
		return;

	if (typeof imgmap=='undefined')
		return;

	if (CKEDITOR.env.ie && typeof window.CanvasRenderingContext2D == 'undefined')
		return;

	currentAreaId = null;
	map_obj = null;

	img_obj = editor.getSelection().getSelectedElement();

	// On rare situations it's possible to launch the dialog without an image selected
	// -> in IE select an image, click outside the editor and the button will remain enabled,
	//		but img_obj will be null
	if ( !img_obj || !img_obj.is("img") )
	{
		alert( lang.msgImageNotSelected );
		theDialog.hide();
		return;
	}

	var src = img_obj.data ? img_obj.data("cke-saved-src") : img_obj.getAttribute("_cke_saved_src");

	//late init
	myimgmap = new imgmap({
		mode : "editor2",
		custom_callbacks : {
			'onSelectArea' : onSelectArea,
			'onRemoveArea'	: onRemoveArea,
			'onStatusMessage' : function(str) {
				//to display status messages on gui
				document.getElementById(statusContainerId).innerHTML = str;
			},
			'onLoadImage' : function(pic) {
				// avoid the anti-cache busting as it slow us down
				//pic.src=src;
				// Due to the width:auto;height:auto; values in the reset.css the image
				// needs the dimensions as styles, not attributes
				var width = pic.getAttribute("width"),
					height = pic.getAttribute("height");
				if (width) pic.style.width = width + "px";
				if (height) pic.style.height = height + "px";

				// Avoid drag&drop of the image
				var ckPic = new CKEDITOR.dom.element(pic);
				ckPic.on("dragstart", function(e) {
					e.data.preventDefault();
				});

			}

		},
		pic_container: document.getElementById(pic_containerId),
		bounding_box : false,
		lang : ''
	});

	//we need this to load languages
	myimgmap.loadStrings(imgmapStrings);

	img_obj = img_obj.$;

	myimgmap.loadImage(src, parseInt(img_obj.style.width || 0, 10), parseInt(img_obj.style.height || 0, 10));

	//check if the image has a valid map already assigned
	var mapname = img_obj.getAttribute('usemap', 2) || img_obj.usemap;

	if ( typeof mapname == 'string' && mapname !== '') {
		mapname = mapname.substr(1);
		var maps = editor.document.$.getElementsByTagName('MAP');

		for (var i=0; i < maps.length; i++) {
			if (maps[i].name == mapname || maps[i].id == mapname) {
				map_obj = maps[i];
				myimgmap.setMapHTML(map_obj);

				theDialog.setValueOf('info', 'MapName', mapname);
				break;
			}
		}
	}

	// We must set up this listener only after the current data has been read
	myimgmap.config.custom_callbacks.onAddArea = onAddArea;

	if ( map_obj )
	{
		// Select the first area:
		myimgmap.selectedId = 0;
		onSelectArea( myimgmap.areas[0] );

		setMode( 'pointer' );
	}
	else
		highlightMode( 'rect' );

	RefreshSize();
	// Firefox problems...
	window.setTimeout(RefreshSize, 1000);
}

function removeMap()
{
	// Remove the map object and unset the usemap attribute
	editor.fire( 'saveSnapshot' );	// Save undo step.

	if ( img_obj && img_obj.nodeName == "IMG" )
		img_obj.removeAttribute('usemap', 0);

	if ( map_obj )
		map_obj.parentNode.removeChild(map_obj);

	theDialog.hide();
}


function RefreshSize()
{
	// buggy resize in old versions, not worth debugging it
	var revision = parseInt( CKEDITOR.revision, 10 );
	if ( !isNaN(revision) && revision < 7296 )
		return;

	var contents = theDialog.parts.contents,
		table = contents.getFirst().getFirst(),
		picContainer = document.getElementById(pic_containerId);

	picContainer.style.width = (parseInt(contents.$.style.width, 10)) + "px";
	picContainer.style.height = parseInt(picContainer.style.height, 10) + (parseInt(contents.$.style.height, 10) - table.$.offsetHeight) + "px";
}

	// [7296] enable file browser in fieldset:
	var areasContainer = 'fieldset',
		revision = parseInt( CKEDITOR.revision, 10 );
	if ( !isNaN(revision) && revision < 7296 )
		areasContainer = 'vbox';

	return {
		title : lang.title,
		minWidth : 500,
		minHeight : 510,
		buttons : [
			{
				type:'button',
				label: lang.imgmapBtnRemove,
				onClick: removeMap
			},
			CKEDITOR.dialog.okButton,
			CKEDITOR.dialog.cancelButton
		],
		contents :
		[
			{
				id : 'info',
				label : generalLabel,
				title : generalLabel,
				elements :
				[
					{
						type: areasContainer,
						label: lang.imgmapMap,
						id : 'ContainerMapName',
						hidden: true,
						children :
						[
							{
								id:'MapName',
								type:'text',
								label: lang.imgmapMapName,
								labelLayout : 'horizontal',
								onChange : function() {
									myimgmap.mapname = this.getValue();
								}
							}
						]
					},
					{
						type: areasContainer,
						label: lang.imgmapMapAreas,
						children :
						[
							{
								type:'hbox',
								id:'button_container',
								style:'margin-bottom:10px',
								widths: ['20px','18px','18px','18px','26px','230px', '100px'],
								children:
								[
								{
										type:'html',
										id:'btn_pointer',
										onClick: function() { setMode('pointer');},
										html: '<span style="background-position: 0 -64px;" class="imgmapButton" title="' + lang.imgmapPointer + '"></span>'
									},
									{
										type:'html',
										id:'btn_rect',
										onClick: function() { setMode('rect');},
										html: '<span style="background-position: 0 -128px;" class="imgmapButton" title="' + lang.imgmapRectangle + '"></span>'
									},
									{
										type:'html',
										id:'btn_circle',
										onClick: function() { setMode('circle');},
										html: '<span style="background-position: 0 0;" class="imgmapButton" title="' + lang.imgmapCircle + '"></span>'
									},
									{
										type:'html',
										id:'btn_poly',
										onClick: function() { setMode('poly');},
										html: '<span style="background-position: 0 -96px;" class="imgmapButton" title="' + lang.imgmapPolygon + '"></span>'
									},
									{
										type:'html',
										onClick: function() { myimgmap.removeArea(myimgmap.currentid); },
										html: '<span style="background-position: 0 -32px;" class="imgmapButton" title="' + lang.imgmapDeleteArea + '"></span>'
									},
									{
										type:'html',
										html:'<div id="' + statusContainerId + '">&nbsp;</div>'
									},
									{
										type:'select',
										id:'zoom',
										labelLayout : 'horizontal',
										label : lang.imgmapLabelZoom,
										onChange: function()
										{
											var scale = this.getValue();
											var pic = document.getElementById(pic_containerId).getElementsByTagName('img')[0];
											if ( !pic ) return;

											if ( !pic.oldwidth )
												pic.oldwidth = pic.width;

											if ( !pic.oldheight )
												pic.oldheight = pic.height;

											pic.style.width = pic.oldwidth * scale + "px";
											pic.style.height = pic.oldheight * scale + "px";
											myimgmap.scaleAllAreas(scale);
										},
										'default':'1',
										items :
										[
											[ '25%', '0.25'],
											[ '50%', '0.5'],
											[ '100%', '1'],
											[ '200%', '2'],
											[ '300%', '3']
										]
									}
								]
							},
							{
								type:'hbox',
								id:'properties1',
								style: 'visibility:hidden',
								children:
								[
									{
										type:'text',
										id:'href',
										label:lang.linkURL,
										onChange: SetAreaProperty
									},
									{
										type : 'button',
										id : 'browse',
										label : editor.lang.common.browseServer,
										style : 'display:inline-block;margin-top:10px;',
										align : 'center',
										hidden : 'true',
										filebrowser : 'info:href'
									},
									{
										id : 'target',
										type : 'select',
										label : lang.linkTarget,
										onChange: SetAreaProperty,
										items :
										[
											[ lang.notSet, 'notSet'],
											[ lang.linkTargetSelf, '_self'],
											[ lang.linkTargetBlank, '_blank'],
											[ lang.linkTargetTop, '_top']
										]
									}

								]
							},
							{
								type:'hbox',
								id:'properties2',
								style: 'visibility:hidden',
								children:
								[
									{
										type:'text',
										id:'title',
										label:lang.advisoryTitle,
										onChange: SetAreaProperty
									},
									{
										type:'text',
										id:'alt',
										hidden: true,
										label:lang.altText,
										onChange: SetAreaProperty
									}

								]
							}
						]
					},
					{
						type: areasContainer,
						style: 'border:0; padding:0',

						label: '&nbsp;',
						children :
						[
							{
								type:'html',
								html:'<div id="' + pic_containerId + '" style="overflow:auto;width:500px;height:390px;position:relative;"></div>'
							}
						]
					}
				]
			}
		],
		onLoad : function()
		{
			theDialog = this;
			theDialog.on('resize', RefreshSize);
		},
		onShow : function()
		{
			dialogReady = true;
			show();
		},
		onHide : function()
		{
			if ( previousModeImg )
			{
				previousModeImg.removeClass( 'imgmapButtonActive' );
				previousModeImg = null;
			}
			document.getElementById( pic_containerId ).innerHTML = '';
		},
		onOk : function()
		{
			updateAreaValues();

			if (img_obj && img_obj.nodeName == "IMG")
			{
				var MapInnerHTML = getMapInnerHTML(myimgmap);

				// If there are no areas, then exit (and remove if neccesary the map).
				if ( !MapInnerHTML )
				{
					removeMap();
					return;
				}

				myimgmap.mapid = myimgmap.mapname = theDialog.getValueOf( 'info', 'MapName');

				// Fire event for custom validation
				var result = editor.fire( 'imagemaps.validate', myimgmap );

				// in v3 cancel() returns true and in v4 returns false
				// if not canceled it's the myimgmap object, so let's use that.
				if ( typeof result == 'boolean' )
					return false;

				editor.fire( 'saveSnapshot' );	// Save undo step.

				// Update the HTML if the data was modified in the 'imagemaps.validate' event
				MapInnerHTML = getMapInnerHTML(myimgmap);

				if ( !map_obj )
				{
					map_obj = editor.document.$.createElement('map');
					img_obj.parentNode.appendChild(map_obj);
				}

				map_obj.innerHTML = MapInnerHTML;

				// IE bug: it's not possible to directly assign the name and make it work easily
				// We remove the previous name
				if ( map_obj.name )
					map_obj.removeAttribute( 'name' );

				map_obj.name = myimgmap.getMapName();
				map_obj.id   = myimgmap.getMapId();

				img_obj.setAttribute('usemap', "#" + map_obj.name, 0);

				if (CKEDITOR.plugins.imagemaps && CKEDITOR.plugins.imagemaps.drawMap)
					CKEDITOR.plugins.imagemaps.drawMap(img_obj, map_obj);
			}

		}

	};
});

})();