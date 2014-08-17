<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Bt_model extends CI_Model {
  function __construct( ) {
    parent::__construct( );
  }

  function get_bt_segments ( $bounds, $data ) {
    $sql = "SELECT
              count(*) AS volume,
              avg(md.traveltime) AS traveltime,
              avg(md.traveltime)/pat.expected_traveltime * 100 AS pct_avg_tt,
              pat.expected_traveltime AS expected_traveltime,
              bt.start_station AS start_station,
              bt.end_station AS end_station,
              ST_AsGeoJSON(ST_Transform(bt.geom, 4326)) AS geojson
            FROM
              po_gis_data.btsegments AS bt
              LEFT OUTER JOIN arterial.portal_arterial_bluetooth_match_data AS md ON ( bt.start_station = md.stationid_start AND bt.end_station = md.stationid_end AND md.starttime BETWEEN ? AND ? AND md.starttime::time BETWEEN ? AND ? )
              INNER JOIN arterial.portal_arterial_trips AS pat ON ( bt.start_station = pat.stationid_start AND bt.end_station = pat.stationid_end )
            WHERE
              ";

    if ( $bounds != false ) {
      $sql .= " geom && ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom))";
      $sql .= " AND ST_Intersects(geom, ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom)))";
    }

    $sql .= " GROUP BY
              bt.start_station,
              bt.end_station,
              bt.geom,
              pat.expected_traveltime";

    $query = $this->db->query ( $sql, array ( $data['start'] . ' ' . $data['start-time'], $data['end'] . ' ' . $data['end-time'], $data['start-time'], $data['end-time'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'] ) );

    return $query->result ( );
  }
}
?>
