<?php

/**
 * @file
 * Utility functions.
 */

/**
 * Remove old log entries.
 */
function sduconnect_flush_log_entries() {
  $interval = variable_get('sduconnect_delete_logs_after', 86400 * 30);
  db_delete('sduconnect_log')
    ->condition('date', REQUEST_TIME - $interval, '<')
    ->execute();
}
