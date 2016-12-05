<?php
/**
 * @file
 * keystone_customizations.features.inc
 */

/**
 * Implements hook_views_api().
 */
function keystone_customizations_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function keystone_customizations_image_default_styles() {
  $styles = array();

  // Exported image style: banner_image.
  $styles['banner_image'] = array(
    'label' => 'Banner Image',
    'effects' => array(
      2 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1600,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: category.
  $styles['category'] = array(
    'label' => 'Category',
    'effects' => array(
      5 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1600,
          'height' => 400,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: frontpage.
  $styles['frontpage'] = array(
    'label' => 'Frontpage',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1920,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: images.
  $styles['images'] = array(
    'label' => 'Images',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 900,
          'height' => 900,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: shooters.
  $styles['shooters'] = array(
    'label' => 'Shooters',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 800,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function keystone_customizations_node_info() {
  $items = array(
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'photos' => array(
      'name' => t('Photos'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'shooter' => array(
      'name' => t('Shooter'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name of Shooter'),
      'help' => '',
    ),
    'sku' => array(
      'name' => t('SKU'),
      'base' => 'node_content',
      'description' => t('Your SKU Product type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'top_level_page' => array(
      'name' => t('Top-Level Page'),
      'base' => 'node_content',
      'description' => t('This is the homepage. There should only be one instance of this content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}

/**
 * Implements hook_paragraphs_info().
 */
function keystone_customizations_paragraphs_info() {
  $items = array(
    'category' => array(
      'name' => 'Category',
      'bundle' => 'category',
      'locked' => '1',
    ),
    'sponsors' => array(
      'name' => 'Sponsors',
      'bundle' => 'sponsors',
      'locked' => '1',
    ),
  );
  return $items;
}
