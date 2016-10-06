CKEDITOR.dialog.add('tab_title_dialog', function (editor) {
  return {
    title: Drupal.t('Tab title'),
    minWidth: 400,
    minHeight: 200,

    contents: [
      {
        id: 'tab-title',
        label: Drupal.t('Tab title'),
        elements: [
          {
            type: 'text',
            id: 'title',
            label: Drupal.t('Title'),
            validate: CKEDITOR.dialog.validate.notEmpty(Drupal.t('Tab title cannot be empty.')),
            setup: function (element) {
              this.setValue(element.getHtml());
            },
            commit: function (element) {
              element.setHtml(this.getValue());
            }
          }
        ]
      }
    ],
    onOk: function () {
      var dialog = this;
      this.commitContent(this.element);
    },
    onShow: function () {
      var selection = editor.getSelection();

      this.element = selection.getStartElement();
      this.setupContent(this.element);
    }
  };
});
