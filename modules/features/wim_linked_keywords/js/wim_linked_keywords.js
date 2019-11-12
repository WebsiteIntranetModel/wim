(function ($) {
  'use strict';

  Drupal.linkit.dialogHelper['field'].replaceFieldValue = function (id, text) {
    var fieldId = '#' + id;
    if ($(fieldId).length) {
      if (id.includes('title')) {
        if (!$(fieldId).val().length) {
          $(fieldId).val(text);
        }
      }
      else {
        $(fieldId).val(text);
      }
    }
  }
})(jQuery);
