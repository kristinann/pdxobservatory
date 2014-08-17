<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Submit extends CI_Controller {

  function __construct( ) {
    parent::__construct( );
  }

  public function comment ( ) {
    $this->load->model("api/comments_model", "comments");
    $data = (object)$this->input->post();

    if ( !empty ( $data->lonlat ) ) {
      list( $x, $y ) = explode ( ', ', $data->lonlat, 2 );
      if ( !is_numeric($x) || !is_numeric($y) ) {
        die ( 'Invalid coordinate pair.' );
      } else {
        $data->x = $x;
        $data->y = $y;
      }
    } else {
      $data->lonlat = null;
    }

    $outcome = $this->comments->store ( $data );

  }
}

?>