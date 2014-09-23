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

  $form['dashboard_mailer_from_mail'] = array(
    '#type' => 'textfield',
    '#title' => t('From email address'),
    '#default_value' => variable_get('dashboard_mailer_from_mail', ''),
    '#required' => TRUE,
  );

  $form['dashboard_mailer_from_name'] = array(
    '#type' => 'textfield',
    '#title' => t('From name'),
    '#default_value' => variable_get('dashboard_mailer_from_name', ''),
    '#required' => TRUE,
  );

  $form['dashboard_mailer_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => variable_get('dashboard_mailer_subject', ''),
    '#description' => t('This will be prepended to the mail subject/title.'),
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
