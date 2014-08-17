<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Map extends CI_Controller {

    function __construct() {
        parent::__construct();
//    $this->load->model("types");
        $this->load->model("maps");
    }

    /*
      /api/map/geojson/layer/<layername>/bounds/[<miny,minx,maxy,maxx|null>]
      Returns a geojson object of the requested layer. If an optional
      bounds object is supplied, output will be constrained to those
      features which are contained within or intersect the given bounds.
      Bounds should be supplied in EPSG:4326
     */

    public function geojson($layer, $bounds = null, $scale = 11) {
        if (!isset($layer)) {
            die(0);
        }

        if ($bounds != null) {
            $bounds = explode(",", $bounds);
            if (count($bounds) != 4) {
                die(0);
            }
            $bounds = array('minx' => $bounds[0], 'miny' => $bounds[1], 'maxx' => $bounds[2], 'maxy' => $bounds[3]);
            foreach ($bounds as $bound) {
                if (!is_numeric($bound)) {
                    die(0);
                }
            }
        }

        if (!is_numeric($scale)) {
            die(0);
        }

        $data = array();
        $data['geojson'] = $this->maps->get_geojson($layer, $bounds, $scale);

        $this->load->view("maps/geojson", $data);
    }

    public function highways($bounds, $zoom) {
        
        if (!isset($bounds,$zoom)) {
            die(0);
        }
        $bounds = explode(",", $bounds);
        if (count($bounds) != 4) {
            die(0);
        }
        $bounds = array('minx' => $bounds[0], 'miny' => $bounds[1], 'maxx' => $bounds[2], 'maxy' => $bounds[3]);
        foreach ($bounds as $bound) {
            if (!is_numeric($bound)) {
                die(0);
            }
        }
        $data = array('geojson' => $this->maps->get_highways($bounds, $zoom));
        $this->load->view("maps/geojson", $data);
    }

}

?>