<?php

/**
 * @file
 * Provides class that expires custom lists on behave of expire.
 */

class ExpireCustomLists implements ExpireInterface {

  /**
   * Executes expiration actions for custom lists.
   *
   * @param $item
   *   List item object.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire list.
   */
  function expire($item, $action, $skip_action_check = FALSE) {
    $expire_urls = array();

    // Expire custom list pages.
    if ($item->data['provide-page'] && ($skip_action_check || in_array($action, array('update', 'delete')))) {
      $expire_urls['custom_lists-' . $item->lid] = $item->data['path'];
    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration($expire_urls, 'custom_lists', $item);
  }

}
