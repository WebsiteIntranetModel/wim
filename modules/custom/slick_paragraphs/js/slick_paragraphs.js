/**
 * @file
 * Provides integration Slick slider with paragraphs.
 */

(function ($) {
  Drupal.behaviors.slickParagraphs = {
    attach: function (context, settings) {
      var slickParagraphsSettings = settings.slickParagraphs;

      $.each(slickParagraphsSettings, function (sliderClass, sliderOptions) {
        var $slider = $('.' + sliderClass + '>.field-items');
        $slider.once('slick-paragraphs').slick(
          sliderOptions
        );

        // Add pause button to slider.
        if (sliderOptions.pause) {
          $slider.once('slick-pause').append(Drupal.theme('slickPause'));
          $('.slick-pause', $slider).on('click', function () {
            var $pauseBtn = $(this);
            if ($pauseBtn.hasClass('paused')) {
              $slider.slick('slickPlay');
              $pauseBtn.removeClass('paused');
            } else {
              $slider.slick('slickPause');
              $pauseBtn.addClass('paused');
            }
          })
        }
      });
    }
  };

  /**
   * docReaderLink theme function.
   */
  Drupal.theme.prototype.slickPause = function () {
    return '<button type="button" data-role="none" class="slick-pause" aria-label="Pause" role="button">' + Drupal.t('Pause') + '</button>';
  };
})(jQuery);
