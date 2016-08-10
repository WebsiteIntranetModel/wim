/**
 * @file
 * wim.js
 *
 * Provides general enhancement and fixed for the Wim theme.
 */

(function ($) {
  function isMobile() {
    var breakpoint = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content').replace(/\"/g, '');
    if (breakpoint != "desktop") {
      return true;
    }
    return false;
  }

  Drupal.behaviors.mobileMainMenu = {
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

  Drupal.behaviors.mobileTopTasksMenu = {
    attach: function (context, settings) {
      var $topTasksMenu = $('section.menu-top-tasks'),
        openDefaultClass = 'open-default';

      if (!isMobile()) {
        $('li.first.dropdown', $topTasksMenu).addClass(openDefaultClass);
      }
      $('.menu > li', $topTasksMenu).once('top-tasks-item-dropdown').click(function (e) {
        $('.menu > li', $topTasksMenu).removeClass(openDefaultClass);
        console.log($(this));
        $('.menu > li', $topTasksMenu).not(this).removeClass('open');
        if (isMobile()) {
          $(this).toggleClass('open');
        } else {
          $(this).addClass('open');
        }
      });
    }
  };

  // Global behavior for nolink items.
  Drupal.behaviors.noLink = {
    attach: function (context, settings) {
      var $noLinkItems = $('a.nolink');
      $noLinkItems.once('nolink').click(function () {
        event.preventDefault();
      });
    }
  };

})(jQuery);