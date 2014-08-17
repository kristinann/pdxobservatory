<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Weather extends CI_Controller {

  function __construct( ) {
    parent::__construct( );
//    $this->load->model("types");
    $this->load->model("weather_model", "weather" );
  }

  public function weather_stations ( $bounds = null ) {
    $data = array ( );
    $data['start'] = $_GET['start'];
    $data['end'] = $_GET['end'];
    $data['start-time'] = $_GET['start-time'];
    $data['end-time'] = $_GET['end-time'];
    $data['weather_measure'] = $_GET['weather-measure'];

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

    $data['geojson'] = $this->weather->get_measured_stations ( $bounds, $data );

    $this->load->view ( "maps/geojson", $data );
  }

  public function download ( ) {
    $data = $this->uri->uri_to_assoc ( 4 );
    $data['weather_measure'] = $data['weather-measure'];
    $results = $this->weather->get_measured_stations ( false, $data );
    $fh = fopen ( 'php://output', 'w' );
    fputcsv ( $fh, array ( 'station_id', 'geojson', 'start', 'end', $data['weather_measure'], 'num_measures' ) );
    foreach ( $results as $row ) {
      fputcsv ( $fh, array ( $row->id, $row->geojson, $data['start'] . ' ' . $data['start-time'], $data['end'] . ' ' . $data['end-time'], $row->$data['weather_measure'], $row->num_measures ) );
    }
  }
}

?>