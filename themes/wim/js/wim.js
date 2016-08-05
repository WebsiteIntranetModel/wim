/**
 * @file
 * wim.js
 *
 * Provides general enhancement and fixed for the Wim theme.
 */

(function ($) {
  function isMobile() {
    var breakpoint = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content').replace(/\"/g, '');
    if(breakpoint != "desktop"){
      return true;
    }
    return false;
  }

  Drupal.behaviors.mobileMenu = {
    attach: function (context, settings) {
      var $navMenu = $('.navbar-nav.primary'),
        expandedClass = 'expanded',
        $navMenuDropdownItems = $('.parent-dropdown > a', $navMenu);

      $navMenuDropdownItems.once('nav-item-dropdown').click(function (e) {
        if (isMobile()) {
          event.preventDefault();
          $(this).parent().toggleClass(expandedClass);
        }
      });
    }
  };

})(jQuery);