(function($) {
  $(document).ready(
      function() {
        var authForm = document.getElementById('mo-authenticate-user');
        if (authForm != null && authForm != undefined) {
          document.getElementById("user-login-form").hidden = true;
        }
        $('.mo2f-method').click( function() {
          var path = Drupal.settings.mo_settings.path;
          var id = jQuery(this).data("id");
          var configured = jQuery(this).data("configured");
          if (configured === false) {
            var url = path + id;
            window.location.href = url;
          }
        });
        $(".mo2f-pricing-button").click( function(e) {
          document.getElementsByName("requestOrigin")[0].value = jQuery(this).data("plan");
        });
      });
}(jQuery));