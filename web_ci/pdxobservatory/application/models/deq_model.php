<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Deq_model extends CI_Model {
  function __construct( ) {
    parent::__construct( );
  }

  function get_measured_stations ( $bounds, $data ) {
    $sql = "SELECT count(*) AS numcols FROM information_schema.columns WHERE table_schema = 'connectportland' AND table_name = 'aq_deq_data2' AND column_name = ?";
    $query = $this->db->query ( $sql, array ( $data['deq_measure'] ) );
    $result = $query->result ( );

    $row = $result[0];

    if ( $row->numcols != 1 ) {
      exit(0);
    }

    $sql = "SELECT
              ds.station_key,
              ST_AsGeoJSON(ST_Transform(ds.geom,4326)) AS geojson,
              round(avg(dm." . $data['deq_measure'] . ")::numeric,2) AS " . $data['deq_measure'] . ",
              count(*) AS num_measures
            FROM
              po_gis_data.deq_stations AS ds,
              connectportland.aq_deq_data2 AS dm
            WHERE
              dm.dt_pst::date BETWEEN ? AND ? AND
              ds.station_key = dm.epa_station_key AND
              dm.dt_pst::time BETWEEN ? AND ?";

    if ( $bounds != false ) {
      $sql .= " AND geom && ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom))";
      $sql .= " AND ST_Intersects(geom, ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom)))";
    }

    $sql .= " GROUP BY
              ds.station_key,
              ds.geom";

    $query = $this->db->query ( $sql, array ( $data['start'], $data['end'], $data['start-time'], $data['end-time'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'] ) );

    return $query->result ( );
  }
}
?>
