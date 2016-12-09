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
          {
            autoplay: !!sliderOptions.autoplay,
            autoplaySpeed: sliderOptions.autoplaySpeed,
            dots: !!sliderOptions.dots,
            fade: !!sliderOptions.fade,
            pauseOnHover: !!sliderOptions.pauseOnHover,
            prevArrow: '<button type="button" data-role="none" class="slick-prev" aria-label="Prev" role="button"><span class="element-invisible">' + Drupal.t('Prev') + '</span></button>',
            nextArrow: '<button type="button" data-role="none" class="slick-next" aria-label="Next" role="button"><span class="element-invisible">' + Drupal.t('Next') + '</span></button>'
          }
        );

        // Add pause button to slider, if it contains more than 2 slides.
        if (sliderOptions.pause && $('.slick-track>.field-item', $slider).length > 1) {

          if ($slider.length > 1) {
            $slider.each(function (i, element) {
              if ($(element).find('.slick-slide').length > 1) {
                $('.slick-list', $(element)).once('slick-pause').append(Drupal.theme('slickPause'));
              }
            });
          }

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
    return '<button type="button" data-role="none" class="slick-pause" aria-label="Pause" role="button"><span class="element-invisible">' + Drupal.t('Pause') + '</span></button>';
  };
})(jQuery);
