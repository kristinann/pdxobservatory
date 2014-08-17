<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Main extends CI_Controller {
    public function index ( ) {
        $this->load->view('template/header');
        $this->load->view('main/about');
        $this->load->view('template/footer');
    }

    public function about ( ) {
        $this->load->view('template/header');
        $this->load->view('main/about');
        $this->load->view('template/footer');
    }

    public function map ( ) {
        $this->load->view('template/header');
        $data = array();
        $this->load->model("api/guides_model", "guides");
        $data["guide_list"] = $this->guides->get_guide_list();
        $this->load->view('main/map',$data);
        $this->load->view('template/footer');
    }

    public function contact ( ) {
        $this->load->view('template/header');
        $this->load->view('main/contact');
        $this->load->view('template/footer');
    }
}

/* End of file welcome.php */
/* Location: ./application/controllers/welcome.php */
