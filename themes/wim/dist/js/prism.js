(function ($) {
  function isMobile() {
    var breakpoint = window.getComputedStyle(document.querySelector('body'), ':before').getPropertyValue('content').replace(/\"/g, '');
    if (breakpoint != "desktop") {
      return true;
    }
    return false;
  }

  var $topTasksMenu = $('section.menu-top-tasks'),
    openDefaultClass = 'open-default';

  if (!isMobile()) {
    $('li.first.dropdown', $topTasksMenu).addClass(openDefaultClass);
  }

  $('.menu > li', $topTasksMenu).click(function (e) {
    $('.menu > li', $topTasksMenu).removeClass(openDefaultClass);

    $('.menu > li', $topTasksMenu).not(this).removeClass('open');
    if (isMobile()) {
      $(this).toggleClass('open');
    } else {
      $(this).addClass('open');
    }
  });

  var $noLinkItems = $('a.nolink');
  $noLinkItems.click(function () {
    event.preventDefault();
  });

})(jQuery);