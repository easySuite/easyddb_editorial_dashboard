<?php
/**
 * @file
 *
 * Admin-related stuff in this file.
 */

/**
 * Settings form for comments module.
 */
function easyddb_dashboard_comments_admin($form, &$form_state) {
  $form['easyddb_dashboard_comments_email'] = array(
    '#type' => 'checkbox',
    '#title' => t('Also send email notifications.'),
    '#default_value' => variable_get('easyddb_dashboard_comments_email', TRUE),
  );

  return system_settings_form($form);
}
