<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Transit extends CI_Controller {

  function __construct( ) {
    parent::__construct( );
//    $this->load->model("types");
    $this->load->model("transit_model", "transit" );
  }

  public function stops ( $bounds = null ) {
    $data = array ( );
    $data['start'] = $_GET['start'];
    $data['end'] = $_GET['end'];
    $data['start-time'] = $_GET['start-time'];
    $data['end-time'] = $_GET['end-time'];

    if ( $bounds != null ) {
      $bounds = explode ( ",", $bounds );
      if ( count ( $bounds ) != 4 ) {
        die ( 0 );
      }
      $bounds = array ( 'minx' => $bounds[0], 'miny' => $bounds[1], 'maxx' => $bounds[2], 'maxy' => $bounds[3] );
      foreach ( $bounds as $bound ) {
        if ( !is_numeric ( $bound ) ) {
          die ( 0 );
        }
      }
    }

    $data['geojson'] = $this->transit->get_stops ( $bounds, $data );

    $this->load->view ( "maps/geojson", $data );
  }

  public function breaks ( $measure = "ons" ) {
    $data = array ( );
    $data['start'] = $_GET['start'];
    $data['end'] = $_GET['end'];
    $data['start-time'] = $_GET['start-time'];
    $data['end-time'] = $_GET['end-time'];
  }

  public function download ( ) {
    $data = $this->uri->uri_to_assoc ( 4 );
    $data['deq_measure'] = $data['deq-measure'];
    $results = $this->deq->get_measured_stations ( false, $data );
    $fh = fopen ( 'php://output', 'w' );
    fputcsv ( $fh, array ( 'station_key', 'geojson', 'start', 'end', $data['deq_measure'], 'num_measures' ) );
    foreach ( $results as $row ) {
      fputcsv ( $fh, array ( $row->station_key, $row->geojson, $data['start'] . ' ' . $data['start-time'], $data['end'] . ' ' . $data['end-time'], $row->measure, $row->num_measures ) );
    }
  }
}

?>