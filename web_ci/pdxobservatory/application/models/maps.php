<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Maps extends CI_Model {

    function __construct() {
        parent::__construct();
    }

    function get_geojson($layer, $bounds, $scale) {
        // First verify that the requested layer exists as a table
        $sql = "SELECT count(*) AS numtab FROM pg_tables WHERE tablename = ? AND schemaname = 'po_gis_data'";
        $query = $this->db->query($sql, array($layer));
        $result = $query->result();

        $row = $result[0];

        if ($row->numtab != 1) {
            exit(0);
        }

        $sql = "SELECT string_agg(column_name, ',') AS attribs FROM information_schema.columns WHERE table_name = ? AND table_schema = 'po_gis_data' AND udt_name != 'geometry'";
        $query = $this->db->query($sql, array($layer));
        $result = $query->result();
        $row = $result[0];
        $attribs = $row->attribs;

        $sql = "SELECT resolution * 4 AS res FROM po_gis_data.scale_resolutions WHERE scale = ?";
        $query = $this->db->query($sql, array($scale));
        $result = $query->result();
        $row = $result[0];
        $res = $row->res;

        $sql = "SELECT ST_AsGeoJSON(ST_Transform(ST_Simplify(geom," . $res . "),4326)) AS geojson, " . $attribs . " FROM po_gis_data." . $layer;

        if ($bounds != false) {
            $sql .= " WHERE geom && ST_Transform(ST_MakeEnvelope(" . $bounds['minx'] . "," . $bounds['miny'] . "," . $bounds['maxx'] . "," . $bounds['maxy'] . ", 4326),ST_SRID(geom))";
            $sql .= " AND ST_Intersects(geom, ST_Transform(ST_MakeEnvelope(" . $bounds['minx'] . "," . $bounds['miny'] . "," . $bounds['maxx'] . "," . $bounds['maxy'] . ", 4326),ST_SRID(geom)))";
        }

        $sql .= " LIMIT 5000";

        $query = $this->db->query($sql);

        return $query->result();
    }
    
    function get_highways($bounds, $zoom){
        $scale_col = "";
        if($zoom >= 14) 
            $scale_col = "raw";
        elseif($zoom >= 12)
            $scale_col = "50k";
        elseif($zoom >= 11) 
            $scale_col = "100k";
        elseif($zoom >= 10) 
            $scale_col = "250k";
        else
            $scale_col = "500k";
        
        $scale_col = "segment_$scale_col";
        
        $sql =  "SELECT highwayid, stationid, ST_AsGeoJSON(ST_Transform($scale_col,4326)) AS geojson FROM stations ".
                "WHERE ST_Transform(ST_MakeEnvelope(" . $bounds['minx'] . "," . $bounds['miny'] . "," . $bounds['maxx'] . "," . $bounds['maxy'] . ", 4326),ST_SRID(segment_raw)) && segment_raw ".
                "order by highwayid, stationid";
        $query = $this->db->query($sql);
        return $query->result();
        
    }
}

?>
