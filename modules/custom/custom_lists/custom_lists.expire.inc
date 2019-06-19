<?php
/**
 * @file
 * Provides class that expires custom lists on behave of expire.
 */

/**
 * Class ExpireCustomLists.
 */
class ExpireCustomLists implements ExpireInterface {

  /**
   * Executes expiration actions for custom lists.
   *
   * @param object $item
   *   List item object.
   * @param string $action
   *   Action that has been executed.
   * @param bool $skip_action_check
   *   Shows whether should we check executed action or just expire list.
   */
  public function expire($item, $action, $skip_action_check = FALSE) {
    $expire_urls = [];
    $actions = [
      'update',
      'delete',
    ];

    // Expire custom list pages.
    if ($item->data['provide-page'] && ($skip_action_check || in_array($action, $actions))) {
      $expire_urls['custom_lists-' . $item->lid] = $item->data['path'];
    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration($expire_urls, 'custom_lists', $item);
  }

}
