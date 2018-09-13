<?php
/**
 * @file
 * Admin settings for DDS Gruppeweb Export
 */


/**
 * Main settings form.
 */
function dds_gw_export_admin_form(&$form_state) {
  $form = array();
  $weight = 0;

  $form['info'] = array(
    '#value' => '<h2>Eksport af gruppeweb data (beta)</h2><p>Bemærk at der kan gå noget tid før downloaden starter, samt at filen kan være meget stor. Du er velkommen til at kontakte gruppeweb@dds.dk hvis du har problemer, eller vil have filen tilsendt på en anden måde.</p>',
    '#weight' => $weight++,
  );

  $form['files'] = array(
    '#type' => 'fieldset',
    '#title' => 'Filer',
    '#weight' => $weight++,
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#description' => 'Download alle vedhæftede filer på sitet. Bemærk at det kan tage lang tid før downloaden starter.'
  );

  $nodes = _dds_gw_get_all_nodes_with_attachments();
  $sum = array_reduce($nodes, function($carry, $nodeData) { return $carry + $nodeData['count'];}, 0);
  $form['files']['download'] = array(
    '#type' => 'submit',
    '#value' => 'Hent alle ' . $sum . ' filer',
    '#name' => 'download_files',
    '#submit' => array('dds_gw_export_download_files_submit'),
    '#weight' => $weight++,
  );
  $form['files']['list'] = array(
    '#type' => 'fieldset',
    '#title' => 'Enkelte artikler',
    '#weight' => $weight++,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Download enkelte artiklers vedhæftede filer'
  );


  $links_ra = array_map(
    function ($nodeData) {
      $node = $nodeData['node'];
      $count = $nodeData['count'];
      return l($node->title, 'node/' . $node->nid . '/' . DDS_GW_EXPORT_FILES_PATH)
        . ' - ' . $count . ' filer '
        . ' - '
        . l('vis artikel', 'node/' . $node->nid)
        . '';
    },
    $nodes
  );

  $form['files']['list']['links'] = array(
    '#value' => theme_item_list($links_ra),
    '#weight' => $weight++,
  );

  $form['gallery'] = array(
    '#type' => 'fieldset',
    '#title' => 'Gallerier',
    '#weight' => $weight++,
    '#collapsible' => FALSE,
    '#description' => 'Download alle gallerier på sitet. Bemærk at det kan tage lang tid før downloaden starter.'
  );

  $galleryTids = _dds_gw_load_all_gallery_tids();
  $galleries = array_map('_dds_gw_export_load_gallery', $galleryTids);
  $countImages= array_reduce($galleries, function($carry, $galleryData) { return $carry + count($galleryData['images']);}, 0);
  $form['gallery']['download'] = array(
    '#type' => 'submit',
    '#value' => 'Hent alle ' . count($galleries) . ' gallerier med ' . $countImages . ' billeder',
    '#name' => 'download_galleries',
    '#submit' => array('dds_gw_export_download_galleries_submit'),
    '#weight' => $weight++,
  );

  $form['gallery']['list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Enkelte gallerier'),
    '#weight' => $weight++,
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => 'Download enkelte gallerier'
  );


  $links_ra = array_map(
    function ($galleryData) {
      $term = $galleryData['term'];
      return l($term->name, 'galleri/' . $term->tid . '/' . DDS_GW_EXPORT_GALLERY_PATH)
        . ' - '
        . count($galleryData['images']) . ' billeder'
        . ' - ('
        . l('vis galleri', 'galleri/' . $term->tid)
        . ')';
    },
    $galleries
  );


  $form['gallery']['list']['links'] = array(
    '#value' => theme_item_list($links_ra),
    '#weight' => $weight++,
  );




  return $form;
}
