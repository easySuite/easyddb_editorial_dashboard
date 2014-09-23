<?php
/**
 * @file
 * Editorial notification custom functions.
 */

/**
 * Notify a user via email.
 *
 * @param $type
 *   Type of notification.
 * @param $uid
 *   Array of user id's
 */
function easyddb_dashboard_notification_user_notify($action = NULL, $node = NULL, $roles = NULL) {
  if (!empty($node)) {
    // Get all users with specific role.
    $users = easyddb_dashboard_notification_get_users_by_role($roles);

    foreach ($users as $user) {
      $role = in_array('editor', $user->roles) ? 'editor' : 'leditor';

      $html = theme("{$role}_mail", array(
        'header' => t('Content @title status.', array('@title' => $node->title)),
        'body' => t('Content !title status set to @status-ed.', array('!title' => l($node->title, 'node/' . $node->nid, array('absolute' => TRUE)), '@status' => $action)),
        'footer' => t('Alpha (c)@year', array('@year' => date('Y'))),
      ));

      if (!empty($html)) {
        easyddb_dashboard_notification_send_mail($user->mail, $user->name, $html);
      }
    }
  }
}

/**
 * Send an email.
 *
 * @see easyddb_dashboard_notification_admin_form.
 *
 * @param $to_address
 *   Recipient mail address.
 * @param $to_name
 *   Recipient name.
 * @param $content
 *   Mail content, can be HTML.
 */
function easyddb_dashboard_notification_send_mail($to_address = '', $to_name = '', $content = '') {
  $from_address = variable_get('dashboard_mailer_from_mail', '');
  $from_name = variable_get('dashboard_mailer_from_name', '');
  $subject = variable_get('dashboard_mailer_subject', '');

  $mailer = new PHPMailer();
  $mailer->IsSendmail();
  $mailer->SetFrom($from_address, $from_name);
  $mailer->AddAddress("avoykov@yandex.ru", $to_name);
  $mailer->Subject = $subject;
  $mailer->MsgHTML($content);
  $mailer->send();
}

/**
 * Get a list of users with specicifc role.
 *
 * @return
 *   Array of users indexed by user id (uid).
 */
function easyddb_dashboard_notification_get_users_by_role($roles = array()) {
  // @todo Implement setting cache or using drupal_static.
  $users = entity_load('user');

  $result = array();
  if (!empty($roles)) {
    foreach ($users as $user) {
      $intersect = array_intersect($roles, $user->roles);
      if (!empty($intersect)) {
        $result[$user->uid] = $user;
      }
    }
  }

  return $result;
}

