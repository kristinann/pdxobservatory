
#include <iostream>
#include <map>
#include "utils.h"
#include "serversocket.h"
#include "socketconnhandler.h"
#include "guides/guide_temperature.h"
#include "guides/guide_temperature_area.h"
#include "guides/guide_mobility.h"
#include "guides/guide_mobility_extended.h"

using namespace std; 
using namespace utl;



int main(int argc, char* argv[]){
    
    parseConfigFile("config.txt");
    
    std::map<string, Guide*> guide_dictionary;
   
    new Guide_Tempareture(&guide_dictionary,"temperature");
    new Guide_Mobility(&guide_dictionary,"traffic");
    new Guide_Mobility_Extended(&guide_dictionary,"traffic_extended");
    new Guide_TemperatureArea(&guide_dictionary,"temperature_area");
    
    SocketServer dispatcher(utl::configs["server_port"] , &guide_dictionary);
    dispatcher.activate(true);
    dispatcher.waitToFinish();
    return 0;
}