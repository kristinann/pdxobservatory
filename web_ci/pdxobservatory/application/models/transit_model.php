<?php  if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Transit_model extends CI_Model {
  function __construct( ) {
    parent::__construct( );
  }

  function get_stops ( $bounds, $data ) {
    $sql = "SELECT
              tp.location_id             AS location_id,
              round(AVG(tp.on_time)*100,2)            AS on_time,
              round(AVG(tp.early)*100,2)              AS early,
              round(AVG(tp.late)*100,2)               AS late,
              g.stop_name                AS stop_name,
              ST_AsGeoJSON(ST_Transform(g.the_geom,4326)) AS geojson
            FROM
              gtfs.route_stops AS rs,
              trimet.trip_pax     AS tp,
              gis_data.gtfs_stops AS g
             WHERE
              rs.route_id = tp.route_number AND
              rs.stop_id = tp.location_id AND
              rs.timepoint = TRUE AND
              tp.location_id = g.stop_id AND
              tp.service_key = 'W' AND
              tp.timeofday = 'AM Peak'";
              if ( $bounds != false ) {
                $sql .= " AND the_geom && ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(the_geom))";
                $sql .= " AND ST_Intersects(the_geom, ST_Transform(ST_MakeEnvelope(?, ?, ?, ?, 4326),ST_SRID(the_geom))) ";
              }

    $sql .= "GROUP BY
              tp.location_id,
              g.the_geom,
              g.stop_name";

    $query = $this->db->query ( $sql, array ( $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'], $bounds['minx'], $bounds['miny'], $bounds['maxx'], $bounds['maxy'] ) );

    return $query->result ( );
  }
}
?>
