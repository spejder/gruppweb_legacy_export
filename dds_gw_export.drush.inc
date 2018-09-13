<?php

function dds_gw_export_drush_command() {
  $items = array();

  $items['gallery-export'] = array(
    'description' => 'Exports a gallery',
    'arguments' => array(
      'tid' => 'Gallery tid',
    ),
  );

  $items['gallery-export-all'] = array(
    'description' => 'Exports all galleries',
    'arguments' => array(
      'tid' => 'Gallery tid',
    ),
  );

  $items['files-export-all'] = array(
    'description' => 'Exports all attached files',
  );
  return $items;
}

function drush_dds_gw_export_gallery_export($tid = '') {
  $gallery = _dds_gw_export_load_gallery($tid);
  // Todo - multiple.
  $file_list = _dds_gw_export_gallery_to_file_list($gallery);
  print("Exporting " . count($file_list) . ' images in ');
  $zip_file = _dds_gw_zip($file_list);
  print_r("\n Exported gallery into " . $zip_file . " remember to delete it after use!\n");
}


function drush_dds_gw_export_gallery_export_all() {
  $tids = _dds_gw_load_all_gallery_tids();

  $file_list = array();
  foreach($tids as $gallery_tid) {
    $gallery = _dds_gw_export_load_gallery($gallery_tid);
    $file_list = array_merge($file_list, _dds_gw_export_gallery_to_file_list($gallery));
  }

  print("Exporting " . count($file_list) . ' images in ' . count($tids) . ' galleries');
  $zip_file = _dds_gw_zip($file_list);
  print_r("\n Exported galleries into " . $zip_file . " remember to delete it after use!\n");
}



function drush_dds_gw_export_files_export_all() {
  $file_list = _dds_gw_export_all_files();
  print("Exporting " . count($file_list) . ' files');
  $zip_file = _dds_gw_zip($file_list);
  print_r("\n Exported files into " . $zip_file . " remember to delete it after use!\n");
}


