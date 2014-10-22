<?php
/**
 * @file
 * Views related items definition.
 */
class editorial_dashboard_editorial_delete extends views_handler_field_node_link {

  /**
   * Renders the link.
   */
  function render_link($node, $values) {
    global $user;

    if (!easyddb_editorial_dashboard_access_callback($node, EDITORIAL_ACTION_DELETE))  {
      return;
    }

    // @todo
    // Correct action path.
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/editorial/delete";
    $this->options['alter']['query'] = drupal_get_destination();

    $status = $node->field_editorial_status[LANGUAGE_NONE][0]['value'];
    $actions = easyddb_editorial_dashboard_workflow($status);
    $text = '';
    if (in_array(EDITORIAL_ACTION_DELETE, $actions)) {
      $text = !empty($this->options['text']) ? $this->options['text'] : t('delete');
    }

    return $text;
  }
}
