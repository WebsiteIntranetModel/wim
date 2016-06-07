<?php

function wim_form_alter(array &$form, array &$form_state = array(), $form_id = NULL) {
  if ($form_id) {
    switch ($form_id) {
      case 'search_block_form':
        $form['actions']['submit']['#attributes']['title'] = t('Verzend je zoekopdracht');
        break;
    }
  }
}
