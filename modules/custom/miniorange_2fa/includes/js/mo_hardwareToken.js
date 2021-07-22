document.addEventListener('DOMContentLoaded', function() {
  var e = jQuery("div[data-id='hardware-token']");
  document.getElementById('edit-mo-auth-method-hardware-token').disabled = true;
  e.parent().disabled = true;
});
