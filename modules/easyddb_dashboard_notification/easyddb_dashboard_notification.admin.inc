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
function easyddb_dashboard_notification_admin_form() {
  $form = array();

  $form['easyddb_dashboard_notification_from_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('From email address'),
    '#default_value' => variable_get('easyddb_dashboard_notification_from_mail', ''),
    '#required' => TRUE,
  );

  $form['easyddb_dashboard_notification_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('From name'),
    '#default_value' => variable_get('easyddb_dashboard_notification_from_name', ''),
    '#required' => TRUE,
  );

  $form['easyddb_dashboard_notification_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('easyddb_dashboard_notification_subject', ''),
    '#description' => t('This will be prepended to the mail subject/title.'),
    '#required' => TRUE,
  );

  $form['easyddb_dashboard_notification_footer'] = array(
    '#type' => 'textfield',
    '#title' => t('Footer'),
    '#default_value' => variable_get('easyddb_dashboard_notification_footer', ''),
    '#description' => t('This will be prepended to the mail footer. You can use placeholder @year.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}

/**
 * Validate editorial dashboard notification admin form.
 *
 * @see easyddb_dashboard_notification_admin_form().
 */
function easyddb_dashboard_notification_admin_form_validate($form, &$form_state) {
  $values = &$form_state['values'];

  if (!filter_var($values['easyddb_dashboard_notification_from_mail'], FILTER_VALIDATE_EMAIL)) {
    form_set_error('easyddb_dashboard_notification_from_mail', t('Email not valid.'));
  }

  $values['easyddb_dashboard_notification_from_name'] = check_plain(trim($values['easyddb_dashboard_notification_from_name']));
  $values['easyddb_dashboard_notification_subject'] = check_plain(trim($values['easyddb_dashboard_notification_subject']));
  $values['easyddb_dashboard_notification_footer'] = check_plain(trim($values['easyddb_dashboard_notification_footer']));
}
