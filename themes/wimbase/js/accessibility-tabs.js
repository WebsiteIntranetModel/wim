(function ($) {
  Drupal.behaviors.wcagTabs = {
    attach: function (context, settings) {
      Drupal.wcagTabs.init(context, settings);
    }
  }

  Drupal.wcagTabs = Drupal.wcagTabs || {};

  Drupal.wcagTabs.init = function (context, settings) {
    var self = this;
    // Define keyboard controls, tabs and current tab, control clicks.
    var $keys = {
      left: 37,
      up: 38,
      right: 39,
      down: 40,
      end: 35,
      home: 36,
      tab: 9,
      space: 32
    };

    var $tablist = $('.tabnav ul', context);

    // Do nothing if there are no tabs.
    if ($tablist.length === 0) {
      return false;
    }

    // Bind event handlers.
    self.bindHandlers($tablist, $keys, context);
  };

  /**
   * Bind event handlers for tab controls.
   * @param {Object} $tablist
   * @param {Object} $keys
   * @param {Object} context
   */
  Drupal.wcagTabs.bindHandlers = function ($tablist, $keys, context) {
    var self = this;
    var click = true;

    // Use each to handle multiple sets of tabs on a single page.
    $tablist.each(function (i, element) {
      var $tabs = $(element).find('li');
      var $panels = $('.tab-content', context).find('div.tab-pane');

      self.initTabs($tabs);
      // Add keyboard and click event self for tabs and tab panels.
      $tabs.keydown(function (e) {
        self.handleTabKeyDown($(this), e, $keys, $tabs);
      });

      $tabs.once("tabClick").click(function (e) {
        self.switchTabs($(this), click);
      });

      $panels.keydown(function (e) {
        var $currentTab = $(element).find('li.active');

        // Ensure only one set of tabs gets affected here, in case there are
        // multiple levels of tabs inside tabs.
        var paneId = $currentTab.find('a').attr('aria-controls');
        var $focused = $('#' + paneId).find(':focus');

        if ($focused.length !== 0) {
          if ($(e.target).closest('.tab-pane').attr('id') === paneId) {

            self.handlePanelKeyDown($currentTab, e, $keys, $tabs);
            e.stopImmediatePropagation();
          }
        }
      });
    });
  };

  /**
   * Add initial accessibility-related set of attributes to tabs.
   * @param {Object} $tabs current set of tabs
   */
  Drupal.wcagTabs.initTabs = function ($tabs) {
    $tabs.each(function (i, tab) {
      var $link = $(tab).find('a');

      if (i !== 0) {
        $link.attr('aria-selected', 'false');
      } else {
        $link.attr('aria-selected', 'true');
        $link.attr('tabindex', '0');
      }
    });
  };

  /**
   * Handler for tab switching.
   * @param {Object} $newTab new Tab to switch to.
   * @param {Boolean} click Determines if click is needed.
   */
  Drupal.wcagTabs.switchTabs = function ($newTab, click) {
    $newTab.siblings().find('a').attr('aria-selected', 'false');

    var $newTabLink = $newTab.find('a');

    $newTabLink.attr('aria-selected', 'true');
    $newTabLink.attr('tabindex', '0');

    $newTabLink.focus();
    if (click !== true) {
      $newTabLink.trigger('click');
    }
  };

  /**
   * Handler for Tab keydown.
   * @param {Object} $tab Current tab.
   * @param {Object} e Keydown event.
   * @param {Object} $keys Controls keycodes array.
   * @param {Object} $tabs Current set of tabs.
   * @returns {Boolean}
   */
  Drupal.wcagTabs.handleTabKeyDown = function ($tab, e, $keys, $tabs) {
    var self = this;

    switch (e.keyCode) {
      case $keys.right:
      case $keys.down:
        // Move to the next tab on right and down keys.
        self.nextTab($tab, $tabs);
        e.stopPropagation();
        e.preventDefault();
        return false;

      case $keys.left:
      case $keys.up:
        if (e.ctrlKey) {
          e.preventDefault();
          return true;
        }

        // Move to the previous tab on right and down keys.
        self.prevTab($tab, $tabs);
        e.stopPropagation();
        e.preventDefault();
        return false;

      case $keys.home:
        // Switch to the first tab on Home key.
        self.switchTabs($tabs.first());
        e.stopPropagation();
        e.preventDefault();
        return false;
      case $keys.end:
        // Switch to the last tab on End key.
        self.switchTabs($tabs.last());
        e.stopPropagation();
        e.preventDefault();
        return false;

      case $keys.tab:
        if (e.shiftKey) {
          return true;
        }
        return false;
      case $keys.space:
        var paneId = '#' + $tab.find('a').attr('aria-controls');

        if ($(paneId).find(':focusable').length === 0) {
          self.currentTab($tab);
          e.stopPropagation();
          e.preventDefault();
        }
        return false;
    }
  };

  /**
   * Handler for Panel keydown.
   * @param {Object} $currentTab Current tab.
   * @param {Object} e Keydown event.
   * @param {Object} $keys Controls keycodes array.
   * @param {Object} $tabs Current set of tabs.
   * @returns {Boolean}
   */
  Drupal.wcagTabs.handlePanelKeyDown = function ($currentTab, e, $keys, $tabs) {
    var self = this;

    switch (e.keyCode) {
      case $keys.left:
      case $keys.up:
        // Move to Tab header on Ctrl+Up/Left keys.
        if (!e.ctrlKey) {
          return true;
        }

        $currentTab.find('a').focus();
        e.preventDefault();
        return false;

      case $keys.tab:
        if (e.shiftKey) {
          return true;
        }
        return false;
    }
  };

  /**
   * Helper function to choose a current tab.
   * @param {Object} $tab Current tab.
   */
  Drupal.wcagTabs.currentTab = function ($tab) {
    var self = this;
    self.switchTabs($tab);
  };

  /**
   * Helper function to switch to the next tab.
   * @param {Object} $tab Current tab.
   * @param {Object} $tabs Current set of tabs.
   */
  Drupal.wcagTabs.nextTab = function ($tab, $tabs) {
    var self = this;
    var curNdx = $tabs.index($tab);

    // Check for the last tab.
    if (curNdx === $tabs.length - 1) {
      $newTab = $tabs.first();
    } else {
      var $newTab = $tabs.eq(curNdx + 1);
    }

    self.switchTabs($newTab);
  };

  /**
   * Helper function to switch to the previous tab.
   * @param {Object} $tab Current tab.
   * @param {Object} $tabs Current set of tabs.
   */
  Drupal.wcagTabs.prevTab = function ($tab, $tabs) {
    var self = this;
    var curNdx = $tabs.index($tab);

    // Check for the first tab.
    if (curNdx === 0) {
      $newTab = $tabs.last();
    } else {
      var $newTab = $tabs.eq(curNdx - 1);
    }

    self.switchTabs($newTab);
  };
})(jQuery);
