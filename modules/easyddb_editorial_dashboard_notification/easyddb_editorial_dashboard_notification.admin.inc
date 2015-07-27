<?php
/**
 * @file
 *
 * Admin-related stuff in this file.
 *
 */

/**
 * Module settings form.
 *
 * Set basic info for future mailing.
 */
function easyddb_editorial_dashboard_notification_admin_form() {
  $form = array('#tree' => TRUE);

  $form['easyddb_editorial_dashboard_notification_from_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('From email address'),
    '#default_value' => variable_get('easyddb_editorial_dashboard_notification_from_mail', ''),
    '#required' => TRUE,
  );

  $form['easyddb_editorial_dashboard_notification_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('From name'),
    '#default_value' => variable_get('easyddb_editorial_dashboard_notification_from_name', ''),
    '#required' => TRUE,
  );

  $form['easyddb_editorial_dashboard_notification_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('easyddb_editorial_dashboard_notification_subject', ''),
    '#description' => t('This will be prepended to the mail subject/title.'),
    '#required' => TRUE,
  );

  $form['easyddb_editorial_dashboard_notification_footer'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer'),
    '#default_value' => variable_get('easyddb_editorial_dashboard_notification_footer', ''),
    '#description' => t('This will be prepended to the mail footer. You can use placeholder @year.'),
    '#required' => TRUE,
  );

  $roles = user_roles(TRUE);
  // Exludes anon and authenticated roles.
  $roles = array_slice($roles, 2);
  // And make copy value to keys.
  $roles = array_combine($roles, $roles);
  // Makes header translatible.
  $header = array_map(function($v) { return t($v);}, $roles);
  // Adds custom elem to header.
  array_unshift($header, 'Action');

  // Define all actions.
  $actions = array(
   EDITORIAL_ACTION_PUSH  => t('Push'),
   EDITORIAL_ACTION_APPROVE => t('Approve'),
   EDITORIAL_ACTION_REJECT => t('Reject'),
   EDITORIAL_ACTION_DELETE => t('Delete'),
   EDITORIAL_ACTION_COMMENTED => t('Commented'),
  );

  $form['notifications'] = array(
    '#theme' => 'ed_notifications_table',
    '#header' => $header,
    '#actions' => $actions,
  );

  $values = variable_get('easyddb_editorial_dashboard_notification_settings', array());
  foreach ($actions as $action => $name) {
    foreach ($roles as $role) {
      $form['notifications'][$action][$role] = array(
        '#type' => 'checkbox',
        '#default_value' => isset($values[$action][$role]) ? $values[$action][$role] : 0,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save')
  );
  return $form;
}

/**
 * Validate editorial dashboard notification admin form.
 *
 * @see easyddb_editorial_dashboard_notification_admin_form().
 */
function easyddb_editorial_dashboard_notification_admin_form_validate($form, &$form_state) {
  $values = &$form_state['values'];

  if (!filter_var($values['easyddb_editorial_dashboard_notification_from_mail'], FILTER_VALIDATE_EMAIL)) {
    form_set_error('easyddb_editorial_dashboard_notification_from_mail', t('Email not valid.'));
  }

  $values['easyddb_editorial_dashboard_notification_from_name'] = check_plain(trim($values['easyddb_editorial_dashboard_notification_from_name']));
  $values['easyddb_editorial_dashboard_notification_subject'] = check_plain(trim($values['easyddb_editorial_dashboard_notification_subject']));
  $values['easyddb_editorial_dashboard_notification_footer'] = check_plain(trim($values['easyddb_editorial_dashboard_notification_footer']));
}

/**
 * Validate editorial dashboard notification admin form.
 *
 * @see easyddb_editorial_dashboard_notification_admin_form().
 */
function easyddb_editorial_dashboard_notification_admin_form_submit($form, &$form_state) {
  $values = &$form_state['values'];

  variable_set('easyddb_editorial_dashboard_notification_from_mail', $values['easyddb_editorial_dashboard_notification_from_mail']);
  variable_set('easyddb_editorial_dashboard_notification_from_name', $values['easyddb_editorial_dashboard_notification_from_name']);
  variable_set('easyddb_editorial_dashboard_notification_subject', $values['easyddb_editorial_dashboard_notification_subject']);
  variable_set('easyddb_editorial_dashboard_notification_footer', $values['easyddb_editorial_dashboard_notification_footer']);
  variable_set('easyddb_editorial_dashboard_notification_settings', $values['notifications']);
}
