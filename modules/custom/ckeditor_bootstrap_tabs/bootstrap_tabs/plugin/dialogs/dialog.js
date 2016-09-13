CKEDITOR.dialog.add('bootstrap_tabs', function (editor) {
  return {
    title: Drupal.t('Number of tabs'),
    minWidth: 200,
    minHeight: 100,
    contents: [
      {
        id: 'info',
        elements: [
          {
            id: 'type',
            type: 'select',
            label: Drupal.t('Number of tabs'),
            items: [
              [2, '2'],
              [3, '3'],
              [4, '4'],
              [5, '5'],
              [6, '6'],
              [7, '7'],
              [8, '8'],
              [9, '9'],
              [10, '10'],
              [11, '11'],
              [12, '12']
            ],
            required: true,
            setup: function(widget) {
              this.setValue(widget.data.tabCount !== undefined ? widget.data.tabCount : 5);
            },
            commit: function(widget) {
              widget.setData('tabCount', this.getValue());
            }
          }
        ]
      }
    ]
  };
});
