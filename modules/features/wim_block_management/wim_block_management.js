(function ($) {
  Drupal.behaviors.felixBlockAdminTabs = {
    attach: function(context) {

      $(document).ready(function(){
        var page = $('#block-system-main', '.page-felix-blocks-add');
        var blocks = page.find('ul.links');
        var markup = '<div class="tabs_container"><div class="tabs_heading"><ul>';

        // Loop through the available titles
        $.each(blocks, function(key, value) {
          var title = $(this).prev().text();
          if (key == 0) {
            state = 'active';
          } else {
            state = '';
          }
          markup += '<li><a href="#" data-target=".tab-' + key + '" class="' + state + '"">' + title + '</a></li>';

          // Remove the original
          $(this).prev().remove();
        });

        markup += '</ul></div><div class="tabs_content">';

        // Loop through the available links
        $.each(blocks, function(key, value){
          if (key == 0) {
            state = 'active';
          } else {
            state = '';
          }
          markup += '<div class="tab tab-' + key + ' '+ state + '"><ul>' + $(this).html() + '</ul></div>';
          // Remove the original
          $(this).remove();
        });

        markup += '</div></div>';

        // Prepend the markup to the page
        page.prepend(markup);

        // Attach click handler
        page.on('click', '.tabs_container .tabs_heading ul li a', function() {
          var target = $(this).data('target');
          $('.tabs_container .tab').hide();
          $('.tabs_container .tab' + target).show();
          $('.tabs_container .tabs_heading ul li a').removeClass('active');
          $(this).addClass('active');
        });

      });
    }
  }
});
