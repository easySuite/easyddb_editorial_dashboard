<?php
/**
 * @file
 * Editorial items operations.
 */

/**
 * Process the requested editorial action on a node.
 *
 * @param object $node
 *   Node object being altered.
 * @param string $action
 *   Action taking place on this node.
 */
function _easyddb_editorial_dashboard_action($node, $action) {
  $valid_actions = easyddb_editorial_dashboard_valid_actions();

  if (!array_key_exists($action, $valid_actions)) {
    $t = array(
      '@action' => $action
    );
    watchdog('editorial', t('Unknown action @action requested.'), $t, WATCHDOG_WARNING);
  }

  $callback = 'easyddb_editorial_dashboard' . $valid_actions[$action];
  if (function_exists($callback)) {
    $callback($node);

    _easyddb_editorial_dashboard_node_persist($node, $action);
  }
  else {
    $t = array(
      '@callback' => $callback,
    );
    watchdog('editorial', t('No such @callback() method defined.'), $t, WATCHDOG_ERROR);
  }
}

/**
 * Update the node object.
 *
 * Notify other modules and call the node API to save the node.
 *
 * @param object $node
 *   Node object.
 * @param string $action
 *   Action being produced.
 */
function _easyddb_editorial_dashboard_node_persist($node, $action) {
  module_invoke_all('editorial_status_changed', $action, $node);

  $node = node_load($node->nid);

  $wrapper = entity_metadata_wrapper('node', $node);
  if ($action == 'approve' && $node->field_editorial_status[LANGUAGE_NONE][0]['value'] == 'ed_new') {
    $wrapper->status->set('1');
    $wrapper->field_editorial_status->set('ed_appr');
  }
  else {
    $wrapper->field_editorial_status->set(
      $node->field_editorial_status[LANGUAGE_NONE][0]['value']
    );
  }
  $wrapper->save();
}

/**
 * Node push processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _easyddb_editorial_dashboard_action()
 * @see easyddb_editorial_dashboard_valid_actions()
 */
function easyddb_editorial_dashboard_node_push($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_PUSHED,
    ),
  );

  return EDITORIAL_NODE_PUSHED;
}

/**
 * Node approve processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _easyddb_editorial_dashboard_action()
 * @see easyddb_editorial_dashboard_valid_actions()
 */
function easyddb_editorial_dashboard_node_approve($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_APPROVED,
    ),
  );

  return EDITORIAL_NODE_APPROVED;
}

/**
 * Node reject processing.
 *
 * @param object $node
 *   Node object being altered.
 *
 * @see _easyddb_editorial_dashboard_action()
 * @see easyddb_editorial_dashboard_valid_actions()
 */
function easyddb_editorial_dashboard_node_reject($node) {
  $node->field_editorial_status[LANGUAGE_NONE] = array(
    array(
      'value' => EDITORIAL_NODE_REJECTED,
    ),
  );

  return EDITORIAL_NODE_REJECTED;
}
