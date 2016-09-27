/**
 * @file
 * Provides integration Slick slider with paragraphs.
 */

(function ($) {
  Drupal.behaviors.slickParagraphs = {
    attach: function (context, settings) {
      var slickParagraphsSettings = settings.slickParagraphs;

      $.each(slickParagraphsSettings, function (sliderClass, sliderOptions) {
        $('.' + sliderClass + ' .field-items').once('slick-paragraphs').slick(
          sliderOptions
        );
      });
    }
  };
})(jQuery);
