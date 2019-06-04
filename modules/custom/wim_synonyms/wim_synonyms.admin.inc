<?php

/**
 * Form for callback 'admin/config/search/apachesolr/synonyms'.
 */
function wim_synonyms_admin_list_form($form, &$form_state) {
  $form['synonyms'] = array(
    '#title' => t("Synonyms"),
    '#type' => 'fieldset',
    '#tree' => TRUE,
    '#theme' => 'wim_synonyms_table_synonyms',
  );
  $rs = db_select('wim_synonyms', 's')
    ->fields('s', array('keyword', 'synonyms'))
    ->orderBy('s.keyword', 'ASC')
    ->execute();

  foreach ($rs as $row) {
    $form['synonyms'][$row->keyword] = array(
      '#tree' => TRUE,
    );
    $form['synonyms'][$row->keyword][$row->keyword . '_keyword'] = array(
      '#type' => 'textfield',
      '#disabled' => TRUE,
      '#default_value' => $row->keyword,
    );
    $form['synonyms'][$row->keyword][$row->keyword . '_synonyms'] = array(
      '#type' => 'textfield',
      '#disabled' => TRUE,
      '#default_value' => $row->synonyms,
    );
    $form['synonyms'][$row->keyword][$row->keyword . '_delete'] = array(
      '#type' => 'markup',
      '#markup' => l(t('Delete'), 'admin/config/search/apachesolr/synonyms/delete/' . $row->keyword),
    );

    $form['synonyms']['save-button'] = array(
      '#type' => 'submit',
      '#value' => t('Reload core (required for new changes to take effect)'),
      '#submit' => array('wim_synonyms_save_submit'),
    );
  }

  $form['new-synonym'] = array(
    '#title' => t("New synonym"),
    '#type' => 'fieldset',
    '#tree' => TRUE,
  );
  $form['new-synonym']['keyword'] = array(
    '#type' => 'textfield',
    '#title' => t('Keyword'),
  );
  $form['new-synonym']['synonyms'] = array(
    '#type' => 'textfield',
    '#title' => t('Synonyms'),
    '#description' => t("Comma-separated")
  );
  $form['new-synonym']['add'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
    '#submit' => array('wim_synonyms_add_synonym_submit'),
    '#validate' => array('wim_synonyms_add_synonym_validate'),
  );

  return $form;
}

/**
 * Submit handler for saving synonyms.
 */
function wim_synonyms_save_submit($form, $form_state) {
  foreach ($form_state['values']['synonyms'] as $key => $synonym_row) {
    if (isset($form_state['values']['synonyms'][$key][$key . '_keyword'])) {
      $keyword = $form_state['values']['synonyms'][$key][$key . '_keyword'];
      $synonyms = $form_state['values']['synonyms'][$key][$key . '_synonyms'];

      db_update('wim_synonyms')
        ->fields(array('synonyms' => $synonyms))
        ->condition('keyword', $keyword)
        ->execute();
    }
  }

  // Get the Solr environment.
  $env_id = apachesolr_default_environment();
  $environment = apachesolr_environment_load($env_id);
  $environment = parse_url($environment['url']);
  $environment['core'] = explode('/', $environment['path']);
  $environment['core'] = end($environment['core']);

  // Reload the core.
  $url = $environment['scheme'] . '://' . $environment['host'] . ':' . $environment['port'] . '/solr/admin/cores?action=RELOAD&core=' . $environment['core'];

  $ch = curl_init();
  curl_setopt($ch, CURLOPT_URL, $url);
  curl_exec($ch);

  drupal_set_message(t("Synonyms have been updated and the core has been reloaded."));
}

/**
 * Submit handler for adding synonyms.
 */
function wim_synonyms_add_synonym_validate($form, $form_state) {
  $new_keyword = $form_state['values']['new-synonym']['keyword'];
  $new_synonyms = $form_state['values']['new-synonym']['synonyms'];

  $keyword_exists = db_select('wim_synonyms', 's')
    ->condition('keyword', $new_keyword)
    ->fields('s', array('keyword'))
    ->execute()
    ->fetchField();

  if ($keyword_exists) {
    form_set_error('keyword', t('This keyword has already been used.'));
  }
}

/**
 * Submit handler for adding synonyms.
 */
function wim_synonyms_add_synonym_submit($form, $form_state) {
  $new_keyword = $form_state['values']['new-synonym']['keyword'];
  $new_synonyms = $form_state['values']['new-synonym']['synonyms'];
  drupal_set_message(
    t('Added @keyword with synonyms @synonyms',
      array(
        '@keyword' => $new_keyword,
        '@synonyms' => $new_synonyms,
      )
    )
  );

  db_insert('wim_synonyms')
    ->fields(array(
      'keyword' => $new_keyword,
      'synonyms' => $new_synonyms,
    ))
    ->execute();

  // Add to the managed SOLR service.
  require __DIR__ . '/vendor/autoload.php';

  // Get the Solr environment.
  $env_id = apachesolr_default_environment();
  $environment = apachesolr_environment_load($env_id);
  $environment = parse_url($environment['url']);
  $environment['core'] = explode('/', $environment['path']);
  $environment['core'] = end($environment['core']);

  // Add the new synonyms.
  $factory = new \SolrRestApiClient\Common\Factory();
  $repository = $factory->getSynonymRepository($environment['host'], $environment['port'], $environment['path'] . '/');

  $synonymCollection = new \SolrRestApiClient\Api\Client\Domain\Synonym\SynonymCollection();

  $synonym = new \SolrRestApiClient\Api\Client\Domain\Synonym\Synonym();
  $synonym->setMainWord($new_keyword);

  $new_synonyms = explode(',',$new_synonyms);

  foreach ($new_synonyms as $new_synonym) {
    $synonym->addWordsWithSameMeaning($new_synonym);
  }

  $synonymCollection->add($synonym);
  $repository->addAll($synonymCollection,'mytag');
}

/**
 * Theme hook for synonyms table form.
 */
function theme_wim_synonyms_table_synonyms($form) {
  $syn_form = &$form['synonyms']; // Shortcut

  $rows = array();
  $unrendered = array();
  foreach (element_children($syn_form) as $key) {
    if (!isset($syn_form[$key]['#type'])) {
      $row = array();
      $row[] = drupal_render($syn_form[$key][$key . '_keyword']);
      $row[] = drupal_render($syn_form[$key][$key . '_synonyms']);
      $row[] = drupal_render($syn_form[$key][$key . '_delete']);
      drupal_render($syn_form[$key]);
      $rows[] = $row;
    }
    else {
      $unrendered[] = $key;
    }
  }

  $header = array(t('Trefwoord'), t('Synonyms'), t('Actions'));
  $output = theme('table', array('header' => $header, 'rows' => $rows));

  foreach ($unrendered as $key) {
    $output .= drupal_render($syn_form[$key]);
  }

  return $output;
}

/**
 * Form callback from 'admin/config/search/apachesolr/synonyms/list/delete/%'.
 */
function wim_synonyms_admin_list_delete_form($form, $form_state, $keyword) {
  return confirm_form(array(
    'keyword' => array(
      '#type' => 'value',
      '#value' => $keyword,
    ),
  ), t('Are you sure you want to remove the synonyms from the keyword %keyword?', array('%keyword' => $keyword)), 'admin/config/search/apachesolr/synonyms', t('This action cannot be undone.'), t('Remove keyword'), t('Cancel'));
}

/**
 * Submit handler for removing a keyword.
 */
function wim_synonyms_admin_list_delete_form_submit($form, &$form_state) {
  db_delete('wim_synonyms')
    ->condition('keyword', $form_state['values']['keyword'])
    ->execute();

  // Add to the managed SOLR service.
  require __DIR__ . '/vendor/autoload.php';

  // Get the Solr environment.
  $env_id = apachesolr_default_environment();
  $environment = apachesolr_environment_load($env_id);
  $environment = parse_url($environment['url']);
  $environment['core'] = explode('/', $environment['path']);
  $environment['core'] = end($environment['core']);

  // Add the new synonyms.
  $factory = new \SolrRestApiClient\Common\Factory();
  $repository = $factory->getSynonymRepository($environment['host'], $environment['port'], $environment['path'] . '/');
  $repository->deleteByMainWord($form_state['values']['keyword'], 'mytag');

  drupal_set_message(t('The keyword %keyword has been removed.', array('%keyword' => $form_state['values']['keyword'])));

  $form_state['redirect'] = array(
    'admin/config/search/apachesolr/synonyms',
  );
}