<?php
/**
 * @file
 * keystone_customizations.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function keystone_customizations_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ammunition';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Category';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Ammunition';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Paragraphs item: Category Link */
  $handler->display->display_options['fields']['field_category_link']['id'] = 'field_category_link';
  $handler->display->display_options['fields']['field_category_link']['table'] = 'field_data_field_category_link';
  $handler->display->display_options['fields']['field_category_link']['field'] = 'field_category_link';
  $handler->display->display_options['fields']['field_category_link']['relationship'] = 'field_category_display_value';
  /* Field: Paragraphs item: Category Picture */
  $handler->display->display_options['fields']['field_category_picture']['id'] = 'field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['table'] = 'field_data_field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['field'] = 'field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['relationship'] = 'field_category_display_value';
  $handler->display->display_options['fields']['field_category_picture']['label'] = '';
  $handler->display->display_options['fields']['field_category_picture']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_category_picture']['alter']['path'] = '[field_category_link]';
  $handler->display->display_options['fields']['field_category_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_category_picture']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_category_picture']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page' => 'page',
    'top_level_page' => 'top_level_page',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Category Display (field_category_display) */
  $handler->display->display_options['relationships']['field_category_display_value']['id'] = 'field_category_display_value';
  $handler->display->display_options['relationships']['field_category_display_value']['table'] = 'field_data_field_category_display';
  $handler->display->display_options['relationships']['field_category_display_value']['field'] = 'field_category_display_value';
  $handler->display->display_options['relationships']['field_category_display_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Paragraphs item: Category Link */
  $handler->display->display_options['fields']['field_category_link']['id'] = 'field_category_link';
  $handler->display->display_options['fields']['field_category_link']['table'] = 'field_data_field_category_link';
  $handler->display->display_options['fields']['field_category_link']['field'] = 'field_category_link';
  $handler->display->display_options['fields']['field_category_link']['relationship'] = 'field_category_display_value';
  $handler->display->display_options['fields']['field_category_link']['label'] = '';
  $handler->display->display_options['fields']['field_category_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_category_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_category_link']['click_sort_column'] = 'url';
  /* Field: Paragraphs item: Category Picture */
  $handler->display->display_options['fields']['field_category_picture']['id'] = 'field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['table'] = 'field_data_field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['field'] = 'field_category_picture';
  $handler->display->display_options['fields']['field_category_picture']['relationship'] = 'field_category_display_value';
  $handler->display->display_options['fields']['field_category_picture']['label'] = '';
  $handler->display->display_options['fields']['field_category_picture']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_category_picture']['alter']['path'] = '[field_category_link]';
  $handler->display->display_options['fields']['field_category_picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_category_picture']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_category_picture']['settings'] = array(
    'image_style' => 'shooters',
    'image_link' => '',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="category-wrapper">
[field_category_picture]
<div class="category-text">
[field_category_link] 
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $export['ammunition'] = $view;

  $view = new view();
  $view->name = 'ammunitions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Ammunitions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Ammunitions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sku' => 'sku',
  );
  /* Filter criterion: Content: Category (field_category) */
  $handler->display->display_options['filters']['field_category_value']['id'] = 'field_category_value';
  $handler->display->display_options['filters']['field_category_value']['table'] = 'field_data_field_category';
  $handler->display->display_options['filters']['field_category_value']['field'] = 'field_category_value';
  $handler->display->display_options['filters']['field_category_value']['value'] = array(
    1 => '1',
  );

  /* Display: Range Block */
  $handler = $view->new_display('block', 'Range Block', 'block');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Category */
  $handler->display->display_options['fields']['field_category']['id'] = 'field_category';
  $handler->display->display_options['fields']['field_category']['table'] = 'field_data_field_category';
  $handler->display->display_options['fields']['field_category']['field'] = 'field_category';
  $handler->display->display_options['fields']['field_category']['label'] = '';
  $handler->display->display_options['fields']['field_category']['element_label_colon'] = FALSE;
  /* Field: Content: Tagline */
  $handler->display->display_options['fields']['field_tagline']['id'] = 'field_tagline';
  $handler->display->display_options['fields']['field_tagline']['table'] = 'field_data_field_tagline';
  $handler->display->display_options['fields']['field_tagline']['field'] = 'field_tagline';
  $handler->display->display_options['fields']['field_tagline']['label'] = '';
  $handler->display->display_options['fields']['field_tagline']['element_label_colon'] = FALSE;
  /* Field: Content: Caliber */
  $handler->display->display_options['fields']['field_caliber']['id'] = 'field_caliber';
  $handler->display->display_options['fields']['field_caliber']['table'] = 'field_data_field_caliber';
  $handler->display->display_options['fields']['field_caliber']['field'] = 'field_caliber';
  $handler->display->display_options['fields']['field_caliber']['element_label_colon'] = FALSE;
  /* Field: Content: Projectile */
  $handler->display->display_options['fields']['field_projectile']['id'] = 'field_projectile';
  $handler->display->display_options['fields']['field_projectile']['table'] = 'field_data_field_projectile';
  $handler->display->display_options['fields']['field_projectile']['field'] = 'field_projectile';
  $handler->display->display_options['fields']['field_projectile']['element_label_colon'] = FALSE;
  /* Field: Content: Velocity */
  $handler->display->display_options['fields']['field_velocity']['id'] = 'field_velocity';
  $handler->display->display_options['fields']['field_velocity']['table'] = 'field_data_field_velocity';
  $handler->display->display_options['fields']['field_velocity']['field'] = 'field_velocity';
  $handler->display->display_options['fields']['field_velocity']['element_label_colon'] = FALSE;
  /* Field: Content: Photos */
  $handler->display->display_options['fields']['field_photos']['id'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['label'] = '';
  $handler->display->display_options['fields']['field_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos']['settings'] = array(
    'image_style' => 'images',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photos']['delta_offset'] = '0';

  /* Display: Competition Block */
  $handler = $view->new_display('block', 'Competition Block', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Tagline */
  $handler->display->display_options['fields']['field_tagline']['id'] = 'field_tagline';
  $handler->display->display_options['fields']['field_tagline']['table'] = 'field_data_field_tagline';
  $handler->display->display_options['fields']['field_tagline']['field'] = 'field_tagline';
  $handler->display->display_options['fields']['field_tagline']['label'] = '';
  $handler->display->display_options['fields']['field_tagline']['element_label_colon'] = FALSE;
  /* Field: Content: Caliber */
  $handler->display->display_options['fields']['field_caliber']['id'] = 'field_caliber';
  $handler->display->display_options['fields']['field_caliber']['table'] = 'field_data_field_caliber';
  $handler->display->display_options['fields']['field_caliber']['field'] = 'field_caliber';
  $handler->display->display_options['fields']['field_caliber']['element_label_colon'] = FALSE;
  /* Field: Content: Projectile */
  $handler->display->display_options['fields']['field_projectile']['id'] = 'field_projectile';
  $handler->display->display_options['fields']['field_projectile']['table'] = 'field_data_field_projectile';
  $handler->display->display_options['fields']['field_projectile']['field'] = 'field_projectile';
  $handler->display->display_options['fields']['field_projectile']['element_label_colon'] = FALSE;
  /* Field: Content: Velocity */
  $handler->display->display_options['fields']['field_velocity']['id'] = 'field_velocity';
  $handler->display->display_options['fields']['field_velocity']['table'] = 'field_data_field_velocity';
  $handler->display->display_options['fields']['field_velocity']['field'] = 'field_velocity';
  $handler->display->display_options['fields']['field_velocity']['element_label_colon'] = FALSE;
  /* Field: Content: Photos */
  $handler->display->display_options['fields']['field_photos']['id'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['table'] = 'field_data_field_photos';
  $handler->display->display_options['fields']['field_photos']['field'] = 'field_photos';
  $handler->display->display_options['fields']['field_photos']['label'] = '';
  $handler->display->display_options['fields']['field_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photos']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_photos']['settings'] = array(
    'colorbox_node_style' => 'images',
    'colorbox_node_style_first' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'field_post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'none',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_photos']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_photos']['multi_type'] = 'ul';
  $handler->display->display_options['fields']['field_photos']['separator'] = '';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sku' => 'sku',
  );
  /* Filter criterion: Content: Category (field_category) */
  $handler->display->display_options['filters']['field_category_value']['id'] = 'field_category_value';
  $handler->display->display_options['filters']['field_category_value']['table'] = 'field_data_field_category';
  $handler->display->display_options['filters']['field_category_value']['field'] = 'field_category_value';
  $handler->display->display_options['filters']['field_category_value']['value'] = array(
    0 => '0',
  );
  $export['ammunitions'] = $view;

  $view = new view();
  $view->name = 'gallery';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gallery';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Gallery';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Gallery Photos */
  $handler->display->display_options['fields']['field_gallery_photos']['id'] = 'field_gallery_photos';
  $handler->display->display_options['fields']['field_gallery_photos']['table'] = 'field_data_field_gallery_photos';
  $handler->display->display_options['fields']['field_gallery_photos']['field'] = 'field_gallery_photos';
  $handler->display->display_options['fields']['field_gallery_photos']['label'] = '';
  $handler->display->display_options['fields']['field_gallery_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gallery_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_gallery_photos']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_gallery_photos']['settings'] = array(
    'colorbox_node_style' => 'frontpage',
    'colorbox_node_style_first' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'field_post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'none',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_gallery_photos']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_gallery_photos']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'photos' => 'photos',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['gallery'] = $view;

  $view = new view();
  $view->name = 'page';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Page';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Page';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'page' => 'page',
  );

  /* Display: Banner Image Block */
  $handler = $view->new_display('block', 'Banner Image Block', 'block');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Banner Image */
  $handler->display->display_options['fields']['field_banner_image']['id'] = 'field_banner_image';
  $handler->display->display_options['fields']['field_banner_image']['table'] = 'field_data_field_banner_image';
  $handler->display->display_options['fields']['field_banner_image']['field'] = 'field_banner_image';
  $handler->display->display_options['fields']['field_banner_image']['label'] = '';
  $handler->display->display_options['fields']['field_banner_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner_image']['settings'] = array(
    'image_style' => 'banner_image',
    'image_link' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'page' => 'page',
  );
  $export['page'] = $view;

  $view = new view();
  $view->name = 'shooters';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Shooters';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Shooters';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'shooter' => 'shooter',
  );

  /* Display: Frontpage Block */
  $handler = $view->new_display('block', 'Frontpage Block', 'block');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<h3>Our Shooters</h3>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Action Photo */
  $handler->display->display_options['fields']['field_action_photo']['id'] = 'field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['table'] = 'field_data_field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['field'] = 'field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['label'] = '';
  $handler->display->display_options['fields']['field_action_photo']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_action_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_action_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_action_photo']['settings'] = array(
    'image_style' => 'shooters',
    'image_link' => 'content',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="shooter-wrapper">
[field_action_photo]
<div class="name-of-person">
[title]
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'shooter' => 'shooter',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Shooters Block */
  $handler = $view->new_display('block', 'Shooters Block', 'block_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Action Photo */
  $handler->display->display_options['fields']['field_action_photo']['id'] = 'field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['table'] = 'field_data_field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['field'] = 'field_action_photo';
  $handler->display->display_options['fields']['field_action_photo']['label'] = '';
  $handler->display->display_options['fields']['field_action_photo']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_action_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_action_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_action_photo']['settings'] = array(
    'image_style' => 'shooters',
    'image_link' => 'content',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="shooter-wrapper">
[field_action_photo]
<div class="name-of-person">
[title]
</div>
</div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $export['shooters'] = $view;

  $view = new view();
  $view->name = 'webform';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Webform';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Webform';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'webform' => 'webform',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Webform: Webform form body */
  $handler->display->display_options['fields']['webform_form_body']['id'] = 'webform_form_body';
  $handler->display->display_options['fields']['webform_form_body']['table'] = 'node';
  $handler->display->display_options['fields']['webform_form_body']['field'] = 'webform_form_body';
  $handler->display->display_options['fields']['webform_form_body']['label'] = '';
  $handler->display->display_options['fields']['webform_form_body']['element_label_colon'] = FALSE;
  $export['webform'] = $view;

  return $export;
}
