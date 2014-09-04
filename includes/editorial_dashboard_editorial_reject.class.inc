<?php
/**
 * @file
 * Views related items definition.
 */
class editorial_dashboard_editorial_reject extends views_handler_field_node_link {

  /**
   * Renders the link.
   */
  function render_link($node, $values) {
    // @todo
    // Permissions module.
    // Ensure user has access to edit this node.
    /*if (!node_access('update', $node)) {
      return;
    }*/

    // @todo
    // Correct action path.
    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/editorial/reject";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('reject');

    return $text;
  }
}

