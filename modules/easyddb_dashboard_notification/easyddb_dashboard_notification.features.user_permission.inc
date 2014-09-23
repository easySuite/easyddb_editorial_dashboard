<?php
/**
 * @file
 * ding_dashboard_comments.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function easyddb_dashboard_notification_user_default_permissions() {
  $permissions = array();

  // Exported permission: access dashboard mailer.
  $permissions['access dashboard mailer'] = array(
    'name' => 'access dashboard mailer',
    'roles' => array(
      0 => 'administrator',
      1 => 'local administrator',
    ),
    'module' => 'easyddb_dashboard_notification',
  );

  return $permissions;
}
