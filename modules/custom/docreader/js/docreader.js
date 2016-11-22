/**
 * @file
 * JS file to add docReader links to files.
 */
(function ($) {
  Drupal.behaviors.slickParagraphs = {
    attach: function (context, settings) {
      var docReaderSettings = settings.docReader;
      var $fileLinks = $('a').filter('[type]');
      var cid = docReaderSettings.cid;
      var language = docReaderSettings.language;
      var supported_file_extensions = docReaderSettings.supported_file_extensions;
      var iconSrc = docReaderSettings.icon;
      var buttonText = docReaderSettings.button_text;

      $fileLinks.once('docreader').each(function (index, link) {
        var match_extension_regexp = new RegExp(/\.([a-zA-Z0-9]+)$/);
        var extension = null;
        if (match_extension_regexp.test($(link).attr("href")) === true) {
          extension = $(link).attr("href").match(match_extension_regexp)[1];
        } else if (match_extension_regexp.test($(link).text()) === true) {
          extension = $(link).text().match(match_extension_regexp)[1];
        }

        if ($.inArray(extension, supported_file_extensions)) {
          var fileUrl = $(link).attr("href");
          var docReaderLink = Drupal.theme('docReaderLink', cid, language, buttonText, fileUrl, iconSrc);
          $(docReaderLink).once('docread-button').insertAfter($(link));
        }
      })
    }
  };

  /**
   * docReaderLink theme function.
   */
  Drupal.theme.prototype.docReaderLink = function (cid, language, text, fileURL, iconSrc) {
    return '<a rel="nofollow" class="docreader" title="' + text + '" href="http://docreader.readspeaker.com/docreader/?cid=' + cid + '&amp;lang=' + language + '&amp;url=' + fileURL + '"><img src="/' + iconSrc + '"> ' + text + '</a>';
  };

})(jQuery);
