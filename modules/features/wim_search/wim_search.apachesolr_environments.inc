<?php
/**
 * @file
 * wim_search.apachesolr_environments.inc
 */

/**
 * Implements hook_apachesolr_environments().
 */
function wim_search_apachesolr_environments() {
  $export = array();

  $environment = new stdClass();
  $environment->api_version = 1;
  $environment->env_id = 'solr';
  $environment->name = 'localhost server';
  $environment->url = 'http://solr:8983/solr/drupal';
  $environment->service_class = '';
  $environment->conf = array(
    'apachesolr_search_changed_boost' => '0:0',
    'apachesolr_search_comment_boost' => '0:0',
    'apachesolr_search_date_boost' => '0:0',
    'apachesolr_search_promote_boost' => '0',
    'apachesolr_search_sticky_boost' => '5.0',
    'apachesolr_search_type_boosts' => array(
      'agenda' => '3.0',
      'page' => '13.0',
      'faq' => '0',
      'news' => '8.0',
      'product' => '13.0',
      'subject_page' => '0',
      'webform' => '0',
    ),
    'field_bias' => array(
      '_version_' => '0',
      'bm_field_promoted' => '0',
      'bm_field_show_on_overview' => '0',
      'bs_field_promoted' => '0',
      'bs_field_show_on_overview' => '0',
      'bs_promote' => '0',
      'bs_status' => '0',
      'bs_sticky' => '0',
      'bs_translate' => '0',
      'bundle' => '0',
      'bundle_name' => '0',
      'content' => '1.0',
      'dm_field_agenda_date' => '0',
      'dm_field_agenda_date_end' => '0',
      'dm_field_publication_date' => '0',
      'ds_changed' => '0',
      'ds_created' => '0',
      'ds_last_comment_or_change' => '0',
      'entity_id' => '0',
      'entity_type' => '0',
      'hash' => '0',
      'id' => '0',
      'im_field_faq_category' => '0',
      'im_field_news_category' => '0',
      'im_field_tags' => '0',
      'im_vid_1' => '0',
      'im_vid_2' => '0',
      'im_vid_3' => '0',
      'is_tnid' => '0',
      'is_uid' => '0',
      'ism_nodequeue' => '0',
      'label' => '13.0',
      'path' => '0',
      'site' => '0',
      'sm_field_related_faq' => '0',
      'sm_vid_FAQ_Categories' => '0',
      'sm_vid_News_Categories' => '0',
      'sm_vid_Tags' => '0',
      'sort_label' => '0',
      'sort_language' => '0',
      'sort_name' => '0',
      'sort_name_formatted' => '0',
      'spell' => '0',
      'ss_language' => '0',
      'ss_name' => '0',
      'ss_name_formatted' => '0',
      'tags_a' => '0',
      'tags_h1' => '8.0',
      'tags_h2_h3' => '5.0',
      'tags_h4_h5_h6' => '2.0',
      'tags_inline' => '3.0',
      'taxonomy_names' => '2.0',
      'tid' => '0',
      'timestamp' => '0',
      'tm_vid_1_names' => '0',
      'tm_vid_2_names' => '0',
      'tm_vid_3_names' => '0',
      'tos_content_extra' => '0.1',
      'tos_name' => '0',
      'tos_name_formatted' => '0',
      'ts_comments' => '0.5',
      'url' => '0',
    ),
  );
  $environment->index_bundles = array(
    'node' => array(
      0 => 'agenda',
      1 => 'faq',
      2 => 'news',
      3 => 'page',
      4 => 'person',
      5 => 'product',
    ),
  );
  $export['solr'] = $environment;

  return $export;
}
