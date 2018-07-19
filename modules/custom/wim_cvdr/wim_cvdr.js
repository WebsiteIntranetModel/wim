jQuery(document).ready(function ($) {
  // Retrieve variables.
  var maxItems = Drupal.settings.wim_cvdr.maxItems;

  // Hide the items on ready.
  $('.block-wim-cvdr').each(function () {
    if ($('ul.cvdr-wim li', this).length > maxItems) {
      $('ul.cvdr-wim li:gt(' + maxItems + ')', this).hide();
      $(this).append('<div class="show-more btn-flat"><span>' + Drupal.t('Show more') + '</span></div>');
    }
  });

  // Add event listener to show-more button.
  $('.block-wim-cvdr').on('click', 'div.show-more', function() {
    // Show the hidden items.
    $(this).siblings('ul.cvdr-wim').find('li:gt(' + maxItems + ')').toggle(500);

    // Change text according to current status.
    if ($(this).text() === Drupal.t('Show more')) {
      $(this).text(Drupal.t('Show less'));
    }
    else {
      $(this).text(Drupal.t('Show more'));
    }
  });
});
