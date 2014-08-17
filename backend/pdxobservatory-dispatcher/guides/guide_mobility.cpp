
#include "guide_mobility.h"
#include "../dbconn.h"

using namespace std; 
using namespace pqxx;
using namespace utl;

Guide_Mobility::Guide_Mobility(std::map<std::string, Guide*> *guide_dictionary, std::string guideID):
Guide(guide_dictionary,guideID){
    
}

void Guide_Mobility::buildUsefiedMobilityTable() {
    /**
     * Here are the set of queries for the 15minute-based queries:
     
        DROP TABLE IF EXISTS connectportland.mobility_year_based_15min cascade;
     
        CREATE table connectportland.mobility_year_based_15min AS
        SELECT 	S.highwayid, S.stationid
                ,extract( year from starttime ) as "year"
                ,floor(extract( minute from starttime)/15)*25/100 + extract( hour from starttime) as "time"
                , sum(volume) as volume 
                ,AVG(length) as length
                ,avg(volume) as avg_volume 
                ,avg(volume)/numberlanes as avg_volume_per_lane 
                ,(CASE (sum(volume) = 0) WHEN true THEN null ELSE round2(sum(volume*speed*1.0)/sum(volume)) END) as speed
                ,avg(S.milepost) milepost
        FROM loopdata_15min_raw_bystation L, stations S 
        WHERE extract(dow from starttime) in (2,3,4)
        AND  L.stationid <= 2000
        AND L.stationid != 1110 
        AND L.stationid = S.stationid
        GROUP BY "year","time", S.stationid, S.highwayid;
     
        alter table connectportland.mobility_year_based_15min add primary key (year, stationid, time);
        
        create index mobility_year_based_stationid on connectportland.mobility_year_based_15min using btree (stationid);
      
        create index mobility_year_based_highway on connectportland.mobility_year_based_15min using btree (highwayid);
     * 
     */
}

/**
MobilityType* Guide_Mobility::generateSpeedReport(utl::ParamList &params) {
    
    DBConn conn;
    MobilityType *mobility_report = new MobilityType();
    cout << "mobility: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "mobility: 2"<< endl;
       
        int year = strToNum<int>(params["year"]);
        string by(params["by"]);
        string with(params["with"]);
        string time(params["time"]);
        string restrict_time_from(params["restrict_time_from"]);
        string restrict_time_to(params["restrict_time_to"]);
        string region(params["region"]);
        
        string station_range("<= 2000");
        if(!region.empty()){
            if(region.compare("portland") == 0)
                station_range = "< 1500";
            else if(region.compare("vancouver") == 0)
                station_range = "between 1500 and 2000";
        }
        
        bool include_speed_limit = false;
        bool include_milepost = false;
        bool include_length = false;
        if(!with.empty()){
            vector<string> options = split(with, ',');
            for(int i=0,l=options.size();i<l;++i){
                if(options[i].compare("speed-limit") == 0)
                    include_speed_limit = true;
                else if(options[i].compare("milepost") == 0)
                    include_milepost = true;
                else if(options[i].compare("length") == 0)
                    include_length = true;
            }
        }
        
        bool results_by_highyways = false;
        if(!by.empty()){
            if(by.compare("highway") == 0)
                results_by_highyways = true;
        }
        
        bool include_time_retrictions = !restrict_time_from.empty() && !restrict_time_to.empty();
        
        string time_extract("extract(hour from starttime)");
        string data_table("loopdata_1hr_raw_bystation");
        if(!time.empty()){
            if(time.compare("15minutes") == 0){
                time_extract = "floor(extract( minute from starttime)/15)*25/100 + extract( hour from starttime)";
                data_table = "loopdata_15min_raw_bystation";
            }
        }

        string base_query(
                "SELECT "+time_extract+" as \"time\", S.highwayid, S.stationid \
                    ,(CASE (sum(volume) = 0) WHEN true THEN null ELSE round2(sum(volume*speed*1.0)/sum(volume)) END) as speed\
                    "+(include_length? ",AVG(length) length ":"")+"\
                    "+(include_speed_limit? ",avg(SL.speed_limit) speed_limit ":"")+"    \
                    "+(include_milepost? ",avg(S.milepost) milepost ":"")+"    \
                FROM "+data_table+" L, stations S "+
                    (include_speed_limit? " left join connectportland.stations_speed_limit SL on S.stationid = SL.stationid ":"")+" \
                WHERE extract(dow from starttime) in (2,3,4) \
                AND starttime between '"+numToStr(year)+"-01-01 00:00:00' and '"+numToStr(year)+"-12-31 23:59:59' and L.stationid "+station_range+" \
                AND L.stationid != 1110 \
                "+(include_time_retrictions? 
                    "AND starttime::time between '"+restrict_time_from+"'::time and '"+restrict_time_to+"'::time" :"")+" \
                AND L.stationid = S.stationid\
                GROUP BY \"time\", S.stationid"
        );
        
        if(results_by_highyways){
            base_query = string(
                "SELECT \"time\", highwayid, AVG(speed) as speed ")+
                    (include_length? ",SUM(length) length ":"")+" \
                    "+(include_speed_limit? ",avg(speed_limit) speed_limit ":"")+" \
                    "+(include_milepost? ",avg(milepost) milepost ":"")+" \
                 FROM ("+base_query+") as T \
                 GROUP BY  \"time\", highwayid ";
        }
        
        data = conn.executeQuery(
            "SELECT T.*, H.highwayname || ' ' || H.direction highwayname \
            FROM highways H,( "+base_query+" ) as T\
            WHERE T.highwayid = H.highwayid\
            ORDER BY \"time\"");
        
        if(data){
            cout << "mobility: 3"<< endl;

            if(data && !data->empty()){
                cout << "mobility: 4, data size is: "+utl::numToStr(data->size())+"\n";

                std::vector<MobilityReportItem*> *report = new std::vector<MobilityReportItem*>(data->size());
                
                cout << "mobility: 5.1\n";

                int i=0;
                try{ 
                    MobilityReportItem *item;
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        item = new MobilityReportItemForSpeed( 
                            c["time"].is_null()? 0.0f : c["time"].as<float>(),
                            c["highwayid"].is_null()? 0 : c["highwayid"].as<int>(),
                            c["highwayname"].is_null()? "" : c["highwayname"].as<std::string>(),
                            results_by_highyways || c["stationid"].is_null()? 0 : c["stationid"].as<int>(),
                            c["speed"].is_null()? 0.0f : c["speed"].as<float>(),
                            !include_length || c["length"].is_null()? 0.0f : c["length"].as<float>(),
                            !include_speed_limit || c["speed_limit"].is_null()? 0.0f : c["speed_limit"].as<float>(),
                            !include_milepost || c["milepost"].is_null()? 0.0f : c["milepost"].as<float>()
                        );
                        (*report)[i++] = item;
                    }
                    
                    mobility_report->setReport(report);
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                cout << "mobility: 5.2\n";

            }
        }
    }
    cout << "mobility: 6"<< endl;
    return mobility_report;
    
}


MobilityType* Guide_Mobility::generateVolumeReport(utl::ParamList &params) {
    
    DBConn conn;
    MobilityType *mobility_report = new MobilityType();
    cout << "mobility: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "mobility: 2"<< endl;
       
        int year = strToNum<int>(params["year"]);
        string by(params["by"]);
        string with(params["with"]);
        string time(params["time"]);
        string restrict_time_from(params["restrict_time_from"]);
        string restrict_time_to(params["restrict_time_to"]);
        string region(params["region"]);
        
        string station_range("<= 2000");
        if(!region.empty()){
            if(region.compare("portland") == 0)
                station_range = "< 1500";
            else if(region.compare("vancouver") == 0)
                station_range = "between 1500 and 2000";
        }
        
        bool include_length = false;
        bool include_avg_volume = false;
        bool include_avg_volume_per_lane = false;
        if(!with.empty()){
            vector<string> options = split(with, ',');
            for(int i=0,l=options.size();i<l;++i){
                if(options[i].compare("length") == 0)
                    include_length = true;
                else if(options[i].compare("avg-volume") == 0)
                    include_avg_volume = true;
                else if(options[i].compare("avg-volume-per-lane") == 0)
                    include_avg_volume_per_lane = true;
            }
        }
        
        bool results_by_highyways = false;
        if(!by.empty()){
            if(by.compare("highway") == 0)
                results_by_highyways = true;
        }
        
        bool include_time_retrictions = !restrict_time_from.empty() && !restrict_time_to.empty();
        
        string time_extract("extract(hour from starttime)");
        string data_table("loopdata_1hr_raw_bystation");
        if(!time.empty()){
            if(time.compare("15minutes") == 0){
                time_extract = "floor(extract( minute from starttime)/15)*25/100 + extract( hour from starttime)";
                data_table = "loopdata_15min_raw_bystation";
            }
        }

        string base_query(
                "SELECT "+time_extract+" as \"time\", S.highwayid, S.stationid, sum(volume) volume \
                    "+(include_length? ",AVG(length) length ":"")+"\
                    "+(include_avg_volume? ",avg(volume) avg_volume ":"")+"    \
                    "+(include_avg_volume_per_lane? ",avg(volume)/numberlanes avg_volume_per_lane ":"")+"    \
                FROM "+data_table+" L, stations S \
                WHERE extract(dow from starttime) in (2,3,4) \
                AND starttime between '"+numToStr(year)+"-01-01 00:00:00' and '"+numToStr(year)+"-12-31 23:59:59' and L.stationid "+station_range+" \
                AND L.stationid != 1110 \
                "+(include_time_retrictions? 
                    "AND starttime::time between '"+restrict_time_from+"'::time and '"+restrict_time_to+"'::time" :"")+" \
                AND L.stationid = S.stationid\
                GROUP BY \"time\", S.stationid"
        );
        
        if(results_by_highyways){
            base_query = string(
                "SELECT \"time\", highwayid, sum(volume) as volume ")+
                    (include_length? ",SUM(length) length ":"")+" \
                    "+(include_avg_volume? ",avg(avg_volume) avg_volume ":"")+"    \
                    "+(include_avg_volume_per_lane? ",avg(avg_volume_per_lane) avg_volume_per_lane ":"")+"    \
                 FROM ("+base_query+") as T \
                 GROUP BY  \"time\", highwayid ";
        }
        
        data = conn.executeQuery(
            "SELECT T.*, H.highwayname || ' ' || H.direction highwayname \
            FROM highways H,( "+base_query+" ) as T\
            WHERE T.highwayid = H.highwayid\
            ORDER BY \"time\"");
        
        if(data){
            cout << "mobility: 3"<< endl;

            if(data && !data->empty()){
                cout << "mobility: 4, data size is: "+utl::numToStr(data->size())+"\n";

                std::vector<MobilityReportItem*> *report = new std::vector<MobilityReportItem*>(data->size());
                
                cout << "mobility: 5.1\n";

                int i=0;
                try{ 
                    MobilityReportItem *item;
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        item = new MobilityReportItemForVolume( 
                            c["time"].is_null()? 0.0f : c["time"].as<float>(),
                            c["highwayid"].is_null()? 0 : c["highwayid"].as<int>(),
                            c["highwayname"].is_null()? "" : c["highwayname"].as<std::string>(),
                            results_by_highyways || c["stationid"].is_null()? 0 : c["stationid"].as<int>(),
                            c["volume"].is_null()? 0.0f : c["volume"].as<float>(),
                            !include_length || c["length"].is_null()? 0.0f : c["length"].as<float>(),
                            !include_avg_volume || c["avg_volume"].is_null()? 0.0f : c["avg_volume"].as<float>(),
                            !include_avg_volume_per_lane || c["avg_volume_per_lane"].is_null()? 0.0f : c["avg_volume_per_lane"].as<float>()
                        );
                        (*report)[i++] = item;
                    }
                    
                    mobility_report->setReport(report);
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                cout << "mobility: 5.2\n";

            }
        }
    }
    cout << "mobility: 6"<< endl;
    return mobility_report;
    
}
*/


MobilityType* Guide_Mobility::generateSpeedReport(utl::ParamList &params) {
    
    DBConn conn;
    MobilityType *mobility_report = new MobilityType();
    cout << "mobility: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "mobility: 2"<< endl;
       
        int year = strToNum<int>(params["year"]);
        string by(params["by"]);
        string with(params["with"]);
        string time(params["time"]);
        string restrict_time_from(params["restrict_time_from"]);
        string restrict_time_to(params["restrict_time_to"]);
        string region(params["region"]);
        
        string station_range("<= 2000");
        if(!region.empty()){
            if(region.compare("portland") == 0)
                station_range = "< 1500";
            else if(region.compare("vancouver") == 0)
                station_range = "between 1500 and 2000";
        }
        
        bool include_speed_limit = false;
        bool include_milepost = false;
        bool include_length = false;
        if(!with.empty()){
            vector<string> options = split(with, ',');
            for(int i=0,l=options.size();i<l;++i){
                if(options[i].compare("speed-limit") == 0)
                    include_speed_limit = true;
                else if(options[i].compare("milepost") == 0)
                    include_milepost = true;
                else if(options[i].compare("length") == 0)
                    include_length = true;
            }
        }
        
        bool results_by_highyways = false;
        if(!by.empty()){
            if(by.compare("highway") == 0)
                results_by_highyways = true;
        }
        
        bool include_time_retrictions = !restrict_time_from.empty() && !restrict_time_to.empty();
        
        string time_extract("floor(\"time\")");
        if(!time.empty()){
            if(time.compare("15minutes") == 0){
                time_extract = "\"time\"";
            }
        }

        string base_query(
                "SELECT "+time_extract+" as \"time\", S.highwayid, S.stationid \
                    ,(CASE (sum(volume) = 0) WHEN true THEN null ELSE round2(sum(volume*speed*1.0)/sum(volume)) END) as speed\
                    "+(include_length? ",AVG(length) length ":"")+"\
                    "+(include_speed_limit? ",avg(SL.speed_limit) speed_limit ":"")+"    \
                    "+(include_milepost? ",avg(S.milepost) milepost ":"")+"    \
                FROM connectportland.mobility_year_based_15min L, stations S "+
                    (include_speed_limit? " left join connectportland.stations_speed_limit SL on S.stationid = SL.stationid ":"")+" \
                WHERE year between "+numToStr(year)+" and "+numToStr(year)+" and L.stationid "+station_range+" \
                AND L.stationid != 1110 \
                "+(include_time_retrictions? 
                    "AND \"time\" between (extract(epoch from '"+restrict_time_from+"'::time) / 3600) and (extract(epoch from '"+restrict_time_to+"'::time) / 3600)" :"")+" \
                AND L.stationid = S.stationid\
                GROUP BY \"time\", S.stationid"
        );
        
        if(results_by_highyways){
            base_query = string(
                "SELECT \"time\", highwayid, AVG(speed) as speed ")+
                    (include_length? ",SUM(length) length ":"")+" \
                    "+(include_speed_limit? ",avg(speed_limit) speed_limit ":"")+" \
                    "+(include_milepost? ",avg(milepost) milepost ":"")+" \
                 FROM ("+base_query+") as T \
                 GROUP BY  \"time\", highwayid ";
        }
        
        data = conn.executeQuery(
            "SELECT T.*, H.highwayname || ' ' || H.direction highwayname \
            FROM highways H,( "+base_query+" ) as T\
            WHERE T.highwayid = H.highwayid\
            ORDER BY \"time\"");
        
        if(data){
            cout << "mobility: 3"<< endl;

            if(data && !data->empty()){
                cout << "mobility: 4, data size is: "+utl::numToStr(data->size())+"\n";

                std::vector<MobilityReportItem*> *report = new std::vector<MobilityReportItem*>(data->size());
                
                cout << "mobility: 5.1\n";

                int i=0;
                try{ 
                    MobilityReportItem *item;
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        item = new MobilityReportItemForSpeed( 
                            c["time"].is_null()? 0.0f : c["time"].as<float>(),
                            c["highwayid"].is_null()? 0 : c["highwayid"].as<int>(),
                            c["highwayname"].is_null()? "" : c["highwayname"].as<std::string>(),
                            results_by_highyways || c["stationid"].is_null()? 0 : c["stationid"].as<int>(),
                            c["speed"].is_null()? 0.0f : c["speed"].as<float>(),
                            !include_length || c["length"].is_null()? 0.0f : c["length"].as<float>(),
                            !include_speed_limit || c["speed_limit"].is_null()? 0.0f : c["speed_limit"].as<float>(),
                            !include_milepost || c["milepost"].is_null()? 0.0f : c["milepost"].as<float>()
                        );
                        (*report)[i++] = item;
                    }
                    
                    mobility_report->setReport(report);
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                cout << "mobility: 5.2\n";

            }
        }
    }
    cout << "mobility: 6"<< endl;
    return mobility_report;
    
}


MobilityType* Guide_Mobility::generateVolumeReport(utl::ParamList &params) {
    
    DBConn conn;
    MobilityType *mobility_report = new MobilityType();
    cout << "mobility: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "mobility: 2"<< endl;
       
        int year = strToNum<int>(params["year"]);
        string by(params["by"]);
        string with(params["with"]);
        string time(params["time"]);
        string restrict_time_from(params["restrict_time_from"]);
        string restrict_time_to(params["restrict_time_to"]);
        string region(params["region"]);
        
        string station_range("<= 2000");
        if(!region.empty()){
            if(region.compare("portland") == 0)
                station_range = "< 1500";
            else if(region.compare("vancouver") == 0)
                station_range = "between 1500 and 2000";
        }
        
        bool include_length = false;
        bool include_avg_volume = false;
        bool include_avg_volume_per_lane = false;
        if(!with.empty()){
            vector<string> options = split(with, ',');
            for(int i=0,l=options.size();i<l;++i){
                if(options[i].compare("length") == 0)
                    include_length = true;
                else if(options[i].compare("avg-volume") == 0)
                    include_avg_volume = true;
                else if(options[i].compare("avg-volume-per-lane") == 0)
                    include_avg_volume_per_lane = true;
            }
        }
        
        bool results_by_highyways = false;
        if(!by.empty()){
            if(by.compare("highway") == 0)
                results_by_highyways = true;
        }
        
        bool include_time_retrictions = !restrict_time_from.empty() && !restrict_time_to.empty();
        
        string time_extract("floor(\"time\")");
        if(!time.empty()){
            if(time.compare("15minutes") == 0){
                time_extract = "\"time\"";
            }
        }

        string base_query(
                "SELECT "+time_extract+" as \"time\", S.highwayid, S.stationid, sum(volume) volume \
                    "+(include_length? ",AVG(length) length ":"")+"\
                    "+(include_avg_volume? ",avg(avg_volume) avg_volume ":"")+"    \
                    "+(include_avg_volume_per_lane? ",avg(avg_volume_per_lane) avg_volume_per_lane ":"")+"    \
                FROM connectportland.mobility_year_based_15min L, stations S \
                WHERE year between "+numToStr(year)+" and "+numToStr(year)+" and L.stationid "+station_range+" \
                AND L.stationid != 1110 \
                "+(include_time_retrictions? 
                    "AND \"time\" between (extract(epoch from '"+restrict_time_from+"'::time) / 3600) and (extract(epoch from '"+restrict_time_to+"'::time) / 3600)" :"")+" \
                AND L.stationid = S.stationid\
                GROUP BY \"time\", S.stationid"
        );
        
        if(results_by_highyways){
            base_query = string(
                "SELECT \"time\", highwayid, sum(volume) as volume ")+
                    (include_length? ",SUM(length) length ":"")+" \
                    "+(include_avg_volume? ",avg(avg_volume) avg_volume ":"")+"    \
                    "+(include_avg_volume_per_lane? ",avg(avg_volume_per_lane) avg_volume_per_lane ":"")+"    \
                 FROM ("+base_query+") as T \
                 GROUP BY  \"time\", highwayid ";
        }
        
        data = conn.executeQuery(
            "SELECT T.*, H.highwayname || ' ' || H.direction highwayname \
            FROM highways H,( "+base_query+" ) as T\
            WHERE T.highwayid = H.highwayid\
            ORDER BY \"time\"");
        
        if(data){
            cout << "mobility: 3"<< endl;

            if(data && !data->empty()){
                cout << "mobility: 4, data size is: "+utl::numToStr(data->size())+"\n";

                std::vector<MobilityReportItem*> *report = new std::vector<MobilityReportItem*>(data->size());
                
                cout << "mobility: 5.1\n";

                int i=0;
                try{ 
                    MobilityReportItem *item;
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        item = new MobilityReportItemForVolume( 
                            c["time"].is_null()? 0.0f : c["time"].as<float>(),
                            c["highwayid"].is_null()? 0 : c["highwayid"].as<int>(),
                            c["highwayname"].is_null()? "" : c["highwayname"].as<std::string>(),
                            results_by_highyways || c["stationid"].is_null()? 0 : c["stationid"].as<int>(),
                            c["volume"].is_null()? 0.0f : c["volume"].as<float>(),
                            !include_length || c["length"].is_null()? 0.0f : c["length"].as<float>(),
                            !include_avg_volume || c["avg_volume"].is_null()? 0.0f : c["avg_volume"].as<float>(),
                            !include_avg_volume_per_lane || c["avg_volume_per_lane"].is_null()? 0.0f : c["avg_volume_per_lane"].as<float>()
                        );
                        (*report)[i++] = item;
                    }
                    
                    mobility_report->setReport(report);
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                cout << "mobility: 5.2\n";

            }
        }
    }
    cout << "mobility: 6"<< endl;
    return mobility_report;
    
}

/**
MobilityType* Guide_Mobility::generateTravelTimeReportByHighway95Peaks(utl::ParamList &params) {
    
    DBConn conn;
    MobilityType *mobility_report = new MobilityType();
    cout << "mobility: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "mobility: 2"<< endl;
       
        data = conn.executeQuery(
            "SELECT hour,H.highwayid, H.highwayname || ' ' || H.direction highwayname,\
                     traveltime \
             FROM highways H,\
             (\
             SELECT doy, hour, highwayid, sum (traveltime) as traveltime\
             FROM\
             (\
             SELECT extract(hour from starttime) as hour, \
                    extract(doy from starttime) as doy, \
                    L.stationid, S.highwayid,\
                   (CASE (speed = 0) WHEN true THEN null\
                                 ELSE round2((length_mid/speed)*60) END)\
                   as traveltime\
             FROM loopdata_1hr_raw_bystation L, stations S\
             WHERE extract(dow from starttime) in (2,3,4) AND\
             extract(year from starttime) = "+numToStr(year)+" AND\
             L.stationid < 2000 AND \
             L.stationid != 1110 AND\
             L.stationid = S.stationid "+// AND 
             //highwayid = "+numToStr(highwayid)+" AND\
             //extract(hour from starttime) = "+numToStr(peakhour)+" 
             ") as TTbyS \
             GROUP BY doy, hour, highwayid\
             ORDER BY traveltime desc\
             LIMIT 1 \
             OFFSET 7 \
             ) as TTbyH\
             WHERE TTbyH.highwayid = H.highwayid ");
        if(data){
            cout << "mobility: 3"<< endl;

            if(data && !data->empty()){
                cout << "mobility: 4, data size is: "+utl::numToStr(data->size())+"\n";

                std::vector<MobilityReportItem*> *report = new std::vector<MobilityReportItem*>(data->size());
                
                cout << "mobility: 5.1\n";

                int i=0;
                try{ 
                    
                    MobilityReportItem *item;
                    for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                        item = new MobilityReportItemForTravelTime( 
                            c[0].is_null()? 0 : c[0].as<int>(),
                            c[1].is_null()? 0 : c[1].as<int>(),
                            c[2].is_null()? "" : c[2].as<std::string>(),
                            c[3].is_null()? 0.0f : c[3].as<float>()
                        );
                        (*report)[i++] = item;
                    }
                    
                    mobility_report->setReport(report);
                }catch (const std::exception &e){
                    std::cerr << e.what() << std::endl;
                }
                cout << "mobility: 5.2\n";

            }
        }
    }
    cout << "mobility: 6"<< endl;
    return mobility_report;
}
*/

GuideReturnType * Guide_Mobility::pushRequest(utl::ParamList &params) {
    cout << "\nGuide <" << this->getGuideID() << ">\n" << params;
    
    string report_type = params["report_type"];
    GuideReturnType *res;
    
    if(report_type.compare("speed") == 0){
        res = this->generateSpeedReport(params);
    }else if(report_type.compare("volume") == 0){
        res = this->generateVolumeReport(params);
    }else{
        // Unknown report type. Return an empty report.
        res = new MobilityType();
    }
    
    return res;
}

