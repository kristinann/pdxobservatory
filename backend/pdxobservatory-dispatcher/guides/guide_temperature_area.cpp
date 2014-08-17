
#include "guide_temperature_area.h"
#include "../dbconn.h"

using namespace std; 
using namespace pqxx;
using namespace utl;

Guide_TemperatureArea::Guide_TemperatureArea(std::map<std::string, Guide*> *guide_dictionary, std::string guideID):
Guide(guide_dictionary,guideID){
    
}


Loc * Guide_TemperatureArea::getCityLocation(const string & city){
    Loc * loc = NULL;
    DBConn conn;
    cout << "temperature: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "temperature: 2"<< endl;
        
        data = conn.executeQuery(
            "select ST_X(point) lng, ST_Y(point) lat \
                from (\
                        select ST_Transform(ST_Centroid(geom),4326) point \
                        from po_gis_data.cty_fill_2013_05 \
                        where cityname ~* '"+city+"' \
                ) t1"
        );
        
        if(data){
            cout << "temperature: 3"<< endl;
            if(data && !data->empty()){
                cout << "temperature: 5.1\n";
                try{ 
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        loc = new Loc(c["lat"].as<double>(),c["lng"].as<double>());
                        break;
                    }
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
            }
        }
    }
    return loc;
}

TempType* Guide_TemperatureArea::getTempForCityAndTime(utl::ParamList &params) {
    string city(params["city"]);
    Loc * loc = this->getCityLocation(city);
    TempType *res = new TempType();
    if(loc){
        string time(params["time"]);

        utl::ParamList new_params(string("lat="+numToStr(loc->getLat())+"&lng="+numToStr(loc->getLng())+"&time="+time));

        res = (TempType*)((*guide_dictionary)["temperature"]->pushRequest(new_params));

        cout << "temperature: 5.2\n";
    }
    cout << "temperature: 6"<< endl;
    return res;
    
}


TemperatureListType* Guide_TemperatureArea::getTempForCityAndDate(utl::ParamList &params) {
    TemperatureListType *res = new TemperatureListType();
    string city(params["city"]);
    Loc * loc = this->getCityLocation(city);
    if(loc){
        string date(params["date"]);
        std::vector<TempType*> *report = new std::vector<TempType*>(24);
        
        utl::ParamList new_params(string("lat="+numToStr(loc->getLat())+"&lng="+numToStr(loc->getLng())));
        for(int i=0;i<=23;++i){
            new_params.setParamValue("time", date+" "+numToStr(i)+":00:00");
            (*report)[i] = (TempType*)((*guide_dictionary)["temperature"]->pushRequest(new_params));
        }
        
        res->setReport(report);

        cout << "temperature: 5.2\n";
    }
    cout << "temperature: 6"<< endl;
    return res;
    
}


GuideReturnType * Guide_TemperatureArea::pushRequest(utl::ParamList &params) {
    cout << "\nGuide <" << this->getGuideID() << ">\n" << params;
    
    GuideReturnType *res;
    
    string time(params["time"]);
    string date(params["date"]);
    
    if(!time.empty())
        res = this->getTempForCityAndTime(params);
    else if(!date.empty())
        res = this->getTempForCityAndDate(params);
    
    return res;
}

