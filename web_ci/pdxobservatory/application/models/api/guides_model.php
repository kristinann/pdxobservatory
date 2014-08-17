<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Guides_model extends CI_Model {

    function __construct() {
        parent::__construct();
    }

    function get_guide_list(){
        $sql = 'select id, name, guide_id, descrip as "desc", array_to_string(layers,\'|\') layers, array_to_string(params,\'|\')  params from connectportland.guide_captures order by name';
        $query = $this->db->query($sql);
        return $query->result();
    }
    
    function query($data) {
        $sql =    'select \'guide_id\' as "name", guide_id as value from connectportland.guide_captures '
                . 'where id = ? '
                . 'union '
                . 'select (param).name as "name", (param).value as value from ( '
                .   'select unnest(params) param from connectportland.guide_captures '
                .   'where id = ? '
                . ') t1';
        $query = $this->db->query($sql, array($data->guide_id, $data->guide_id));
        $params = $query->result();
        
        $url = "$_SERVER[GUIDE_SERVICE_URL]?";
        foreach($params as $param){
            $url .= "$param->name=$param->value&";
        }
        
        $ctx = stream_context_create(array(
            'http' => array(
                'timeout' => 120
            )
                )
        );
        $result = file_get_contents($url, 0, $ctx);
        if (!$result) {
            return false;
        }
        return $result;
    }

    function add($data) {
        //$sql = "SELECT po_gis_data.insert_guide(?, ?, ?, ?, ?, ?)";
        $guide_id = '';
        $guide_params = '';
        $params = NULL;
        switch($data->guide_type){
            case 'traffic-volume':
                $guide_params = 'ARRAY[' .
                                    "ROW('report_type','volume')," .
                                    "ROW('region',?)," .
                                    "ROW('with','avg-volume-per-lane')," .
                                    "ROW('by','station')," .
                                    "ROW('time','15minutes')," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)," .
                                    "ROW('year',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'traffic', $data->desc, $data->region, $data->start_time, $data->end_time, $data->year);
                break;
            case 'traffic-speed':
                $guide_params = 'ARRAY[' .
                                    "ROW('report_type','speed')," .
                                    "ROW('region',?)," .
                                    "ROW('by','station')," .
                                    "ROW('time','15minutes')," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)," .
                                    "ROW('year',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'traffic', $data->desc, $data->region, $data->start_time, $data->end_time, $data->year);
                break;
            case 'weather-temp':
                $guide_params = 'ARRAY[' .
                                    "ROW('city',?)," .
                                    "ROW('date',?)," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'temperature_area', $data->desc, $data->region, $data->date, $data->start_time, $data->end_time);
                break;
            default:
                echo 'Error: unknown guide type.';
                die();
        }
        $sql = 'insert into connectportland.guide_captures (name, guide_id, descrip, params, layers) values(?,?,?,'.$guide_params;

        // Preparing the layer array
        if (empty($data->layers)) {
            $sql .= 'NULL';
        } else {
            $sql .= 'ARRAY[';
            $first = true;
            foreach ($data->layers as $value) {
                $sql .= (!$first ? ',' : '') . '?';
                $first = false;
                $params[] = $value;
            }
            $sql .= ']';
        }
        $sql .= ')';


        $this->db->query($sql, $params);

        return true;
    }
    
    function edit($data){
        //$sql = "SELECT po_gis_data.insert_guide(?, ?, ?, ?, ?, ?)";
        
        $guide_id = '';
        $guide_params = '';
        $params = NULL;
        switch($data->guide_type){
            case 'traffic-volume':
                $guide_params = 'params = ARRAY[' .
                                    "ROW('report_type','volume')," .
                                    "ROW('region',?)," .
                                    "ROW('with','avg-volume-per-lane')," .
                                    "ROW('by','station')," .
                                    "ROW('time','15minutes')," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)," .
                                    "ROW('year',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'traffic', $data->desc, $data->region, $data->start_time, $data->end_time, $data->year);
                break;
            case 'traffic-speed':
                $guide_params = 'params = ARRAY[' .
                                    "ROW('report_type','speed')," .
                                    "ROW('region',?)," .
                                    "ROW('by','station')," .
                                    "ROW('time','15minutes')," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)," .
                                    "ROW('year',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'traffic', $data->desc, $data->region, $data->start_time, $data->end_time, $data->year);
                break;
            case 'weather-temp':
                $guide_params = 'params = ARRAY[' .
                                    "ROW('city',?)," .
                                    "ROW('date',?)," .
                                    "ROW('restrict_time_from',?)," .
                                    "ROW('restrict_time_to',?)" .
                                ']::guide_param[],';
                $params = array($data->name, 'temperature_area', $data->desc, $data->region, $data->date, $data->start_time, $data->end_time);
                break;
            default:
                echo 'Error: unknown guide type.';
                die();
        }
        
        $sql = 'update connectportland.guide_captures set name = ?, guide_id = ?, descrip = ?, '.$guide_params;

        // Preparing the layer array
        if (empty($data->layers)) {
            $sql .= 'layers = NULL ';
        } else {
            $sql .= 'layers = ARRAY[';
            $first = true;
            foreach ($data->layers as $value) {
                $sql .= (!$first ? ',' : '') . '?';
                $first = false;
                $params[] = $value;
            }
            $sql .= '] ';
        }
        $sql .= ' where id = ?';
        $params[] = $data->guide_id;

        $this->db->query($sql, $params);

        return true;
    }

}

?>
