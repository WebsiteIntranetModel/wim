/**
 * @file
 * wim.js
 *
 * Provides general enhancement and fixed for the Wim theme.
 */

(function ($) {
  function isMobile() {
    var breakpoint = window.getComputedStyle(document.querySelector('body'), ':after').getPropertyValue('content').replace(/\"/g, '');
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
        $('li.first.dropdown', $topTasksMenu).once('open-default').addClass(openDefaultClass);

        // Fix height of menu.
        var menuWrapperHeight = $('.menu-wrapper .menu.nav', $topTasksMenu).height(),
          $subItems = $('.menu-wrapper ul.dropdown-menu', $topTasksMenu);

        $subItems.once('fix-height').each(function (id, element) {
          var elementHeight = $(element).height();
          if (elementHeight > menuWrapperHeight) {
            $('.menu-wrapper .menu.nav', $topTasksMenu).height(elementHeight);
          }
        });
      }

      $('.menu > li', $topTasksMenu).once('top-tasks-item-dropdown').click(function (e) {
        $('.menu > li', $topTasksMenu).removeClass(openDefaultClass);

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
      $noLinkItems.once('nolink').click(function (event) {
        event.preventDefault();
      });
    }
  };

  // Global behaviour to set checkbox href links to tabindex -1.
  // Since this is handled by input checkbox.
  Drupal.behaviors.checkboxTabindex = {
    attach: function (context, settings) {
      $("a.facetapi-checkbox").attr("tabindex","-1");
    }
  };

})(jQuery);
