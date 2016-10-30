<?php
/**
 * @file
 * keystone_customizations.features.contact_categories.inc
 */

/**
 * Implements hook_contact_categories_defaults().
 */
function keystone_customizations_contact_categories_defaults() {
  return array(
    'Contact Us' => array(
      'category' => 'Contact Us',
      'recipients' => 'monica@keystonemunitions.com,jeremy@keystonemunitions.com',
      'reply' => 'Thank you so much for reaching out to us. We\'ll get back to you shortly with your answer. ',
      'weight' => 0,
      'selected' => 0,
    ),
  );
}
