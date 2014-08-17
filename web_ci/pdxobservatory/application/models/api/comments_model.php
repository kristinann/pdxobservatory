<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Comments_model extends CI_Model {
  function __construct( ) {
    parent::__construct( );
  }

  function store ( $data ) {
    if ( $data->lonlat == null ) {
      $sql = "SELECT po_gis_data.insert_comment(?, ?, ?, ?)";
      $params = array ( $data->name, $data->title, $data->text, $data->layer );
    } else {
      $sql = "SELECT po_gis_data.insert_comment(?, ?, ?, ?, ?, ?)";
      $params = array ( $data->name, $data->title, $data->text, $data->layer, (float)$data->x, (float)$data->y );
    }

    $query = $this->db->query ( $sql, $params );

    return $query->result ( );
  }
}
?>
