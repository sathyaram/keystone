<?php
/**
 * @file
 * keystone_customizations.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function keystone_customizations_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_about:node/5.
  $menu_links['main-menu_about:node/5'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/5',
    'router_path' => 'node/%',
    'link_title' => 'About',
    'options' => array(
      'identifier' => 'main-menu_about:node/5',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: main-menu_ammunition:node/2.
  $menu_links['main-menu_ammunition:node/2'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/2',
    'router_path' => 'node/%',
    'link_title' => 'Ammunition',
    'options' => array(
      'identifier' => 'main-menu_ammunition:node/2',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: main-menu_competition:node/19.
  $menu_links['main-menu_competition:node/19'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/19',
    'router_path' => 'node/%',
    'link_title' => 'Competition',
    'options' => array(
      'identifier' => 'main-menu_competition:node/19',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_ammunition:node/2',
  );
  // Exported menu link: main-menu_contact:contact.
  $menu_links['main-menu_contact:contact'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'contact',
    'router_path' => 'contact',
    'link_title' => 'Contact',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_contact:contact',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: main-menu_find-a-dealer:http://keystonemunitions.dd:8083/findadealer.
  $menu_links['main-menu_find-a-dealer:http://keystonemunitions.dd:8083/findadealer'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'http://keystonemunitions.dd:8083/findadealer',
    'router_path' => '',
    'link_title' => 'Find A Dealer',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'identifier' => 'main-menu_find-a-dealer:http://keystonemunitions.dd:8083/findadealer',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: main-menu_gallery:node/20.
  $menu_links['main-menu_gallery:node/20'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/20',
    'router_path' => 'node/%',
    'link_title' => 'Gallery',
    'options' => array(
      'identifier' => 'main-menu_gallery:node/20',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: main-menu_our-shooters:node/3.
  $menu_links['main-menu_our-shooters:node/3'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/3',
    'router_path' => 'node/%',
    'link_title' => 'Our Shooters',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'main-menu_our-shooters:node/3',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: main-menu_range:node/18.
  $menu_links['main-menu_range:node/18'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'node/18',
    'router_path' => 'node/%',
    'link_title' => 'Range',
    'options' => array(
      'identifier' => 'main-menu_range:node/18',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'main-menu_ammunition:node/2',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('About');
  t('Ammunition');
  t('Competition');
  t('Contact');
  t('Find A Dealer');
  t('Gallery');
  t('Our Shooters');
  t('Range');

  return $menu_links;
}
