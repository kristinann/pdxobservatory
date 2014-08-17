<?php

if (!defined('BASEPATH'))
    exit('No direct script access allowed');

class Guide extends CI_Controller {

    function __construct() {
        parent::__construct();
        $this->load->model("api/guides_model", "guides");
    }

    public function add() {
        $data = (object) $this->input->post();

        if ($this->guides->add($data)) {
            echo 'SAVED';
        }
    }
    

    public function edit() {
        $data = (object) $this->input->post();

        if ($this->guides->edit($data)) {
            echo 'SAVED';
        }
    }

    public function query() {
        $data = (object) $this->input->get();

        $result = $this->guides->query($data);
        if(!$result){
            die ( 'Couldn\'t connect to the Guide Service. ');
        }
        echo $result;
    }
    
    public function guide_list(){
        $result = $this->guides->get_guide_list();
        echo json_encode($result);
    }

}
