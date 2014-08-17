<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Weather_model extends CI_Model {
  function __construct( ) {
    parent::__construct( );
  }

  function get_measured_stations ( $bounds, $data ) {
    $sql = "SELECT count(*) AS numcols FROM information_schema.columns WHERE table_schema = 'connectportland' AND table_name = 'aq_weather_data' AND column_name = ?";
    $query = $this->db->query ( $sql, array ( $data['weather_measure'] ) );
    $result = $query->result ( );

    $row = $result[0];

    if ( $row->numcols != 1 ) {
      exit(0);
    }

    $sql = "SELECT
              ws.id,
              ST_AsGeoJSON(ST_Transform(ws.geom,4326)) AS geojson,";

    if ( $data['weather_measure'] == 'temp_c' ) {
              $sql .= "round(avg(wm." . $data['weather_measure'] . ")::numeric,2) AS " . $data['weather_measure'] . ",";
    } else {
              $sql .= "round(sum(wm." . $data['weather_measure'] . ")::numeric,2) AS " . $data['weather_measure'] . ",";
    }

    $sql .= "count(*) AS num_measures
            FROM
              po_gis_data.weather_stations AS ws,
              connectportland.aq_weather_data AS wm
            WHERE
              wm.observation_time::date BETWEEN ? AND ? AND
              ws.id = wm.station_id AND
              wm.observation_time::time BETWEEN ? AND ?";

    if ( $bounds != false ) {
      $sql .= " AND geom && ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom))";
      $sql .= " AND ST_Intersects(geom, ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(geom)))";
    }

    $sql .= " GROUP BY
              ws.id,
              ws.geom";

    $query = $this->db->query ( $sql, array ( $data['start'], $data['end'], $data['start-time'], $data['end-time'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'] ) );

    return $query->result ( );
  }
}
?>
