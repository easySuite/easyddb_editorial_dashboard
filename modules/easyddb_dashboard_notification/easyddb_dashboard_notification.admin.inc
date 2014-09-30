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
