/* 
 * File:   temperature.cpp
 * Author: Basem Elazzabi
 *
 */

#define _CRT_SECURE_NO_DEPECATE // to keep the VS compiler happy with TBB

#include "temperature.h"
#include "../../dbconn.h"

using namespace std; 
using namespace pqxx;
using namespace utl;


int temperature_step::execute( const TempTag & t, temperature_context & c ) const{
    TempType t1;
    TempType t2;
    TempType t3;
    cout << "temp: 1"<< endl;
    c.temp_airport.get(t,t1);
    cout << "temp: 2"<< endl;
    c.temp_weather_ug.get(t,t2);
    cout << "temp: 3"<< endl;
    c.temp_deq.get(t,t3);
    cout << "temp: 4"<< endl;
    cout << t1 << endl;
    cout << t2 << endl;
    cout << t3 << endl;
    TempType *bestT = t1 < t2? &t1 : &t2;
    bestT = (*bestT) < t3? bestT : &t3;
    c.temp_temperature.put(t,*bestT);
    cout << "temp: 5"<< endl;
    return CnC::CNC_Success;
}

int airport_temp_step::execute( const TempTag & t, temperature_context & c ) const{
    DBConn conn;
    TempType temp;
    cout << "airport: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "airport: 2"<< endl;
        // Find stations within 1km. If no stations are found, the 
        // distance will be doubled and then we will check again.
        // We don't want to keep doubling the distance for infinity.
        // So, we will stop if we reach 100km
        int dist = 500; 
        string loc = t.loc.toGIS();
        string timeFrom = "timestamp '"+t.time+"' - interval '1 hours'";
        string timeTo = "timestamp '"+t.time+"' + interval '1 hours'";
        do{
            dist *= 2;
            cout << "airport: 3"<< endl;
            data = conn.executeQuery(
                "SELECT ST_X(location) lng, ST_Y(location) lat, t2.tempc, t2.reporttime, " 
                    " abs(EXTRACT(EPOCH FROM (reporttime - timestamp '" + t.time + "'))) time_dif " 
                "FROM connectportland.aq_airport_stations t1 join "
                    "connectportland.aq_airport_data t2 on t1.stationid = t2.stationid " 
                "where ST_DWithin(location, ST_GeomFromText('" + loc + "',4326), "  + numToStr(dist) + ") " 
                "and reporttime between " + timeFrom + " and " + timeTo + " " 
                "and tempc is not null ");
            if(!data) break;
            cout << "airport: 4"<< endl;
        }while((data->empty()) && dist < 100000);
        
        if(data && !data->empty()){
            cout << "airport: 5\n";
            Loc tempLoc(0.0,0.0,t.loc);
            TempType temp2;
            for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                tempLoc.setPosition(c[1].as<double>(),c[0].as<double>());
                temp2.setData(t.time, c[2].as<double>(),tempLoc,c[4].as<double>());
                if(temp.isEmpty() || temp2 < temp)
                    temp = temp2;
            }
        }
    }
    cout << "airport: 6"<< endl;
    c.temp_airport.put(t,temp);
    return CnC::CNC_Success;
}

int weather_ug_temp_step::execute( const TempTag & t, temperature_context & c ) const{
    DBConn conn;
    TempType temp;
    cout << "weather: 1" << endl;
    if(conn.is_open()){
        result *data;
        cout << "weather: 2"<< endl;
        // Find stations within 1km. If no stations are found, the 
        // distance will be doubled and then we will check again.
        // We don't want to keep doubling the distance for infinity.
        // So, we will stop if we reach 100km
        int dist = 500; 
        string loc = t.loc.toGIS();
        string timeFrom = "timestamp '"+t.time+"' - interval '1 hours'";
        string timeTo = "timestamp '"+t.time+"' + interval '1 hours'";
        do{
            dist *= 2;
            cout << "weather: 3"<< endl;
            data = conn.executeQuery(
                "SELECT ST_X(location) lng, ST_Y(location) lat, t2.temp_c, t2.observation_time, " 
                    " abs(EXTRACT(EPOCH FROM (observation_time - timestamp '" + t.time + "'))) time_dif " 
                "FROM connectportland.aq_weather_stations t1 join "
                    "connectportland.aq_weather_data t2 on t1.id = t2.station_id " 
                "where ST_DWithin(location, ST_GeomFromText('" + loc + "',4326), "  + numToStr(dist) + ") " 
                "and observation_time between " + timeFrom + " and " + timeTo + " " 
                "and temp_c is not null ");
            cout << "weather: 4"<< endl;
            if(!data) break;
        }while((data->empty()) && dist < 100000);
        
        if(data && !data->empty()){
            cout << "weather: 5\n";
            Loc tempLoc(0.0,0.0,t.loc);
            TempType temp2;
            for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                tempLoc.setPosition(c[1].as<double>(),c[0].as<double>());
                temp2.setData(t.time,c[2].as<double>(),tempLoc,c[4].as<double>());
                if(temp.isEmpty() || temp2 < temp)
                    temp = temp2;
            }
        }
    }
    cout << "weather: 6"<< endl;
    c.temp_weather_ug.put(t,temp);
    return CnC::CNC_Success;
}

int deq_temp_step::execute( const TempTag & t, temperature_context & c ) const{
    DBConn conn;
    TempType temp;
    cout << "deq: 1\n";
    if(conn.is_open()){
        cout << "deq: 2\n";
        result *data;
        // Find stations within 1km. If no stations are found, the 
        // distance will be doubled and then we will check again.
        // We don't want to keep doubling the distance for infinity.
        // So, we will stop if we reach 100km
        int dist = 500; 
        string loc = t.loc.toGIS();
        string timeFrom = "timestamp '"+t.time+"' - interval '1 hours'";
        string timeTo = "timestamp '"+t.time+"' + interval '1 hours'";
        do{
            dist *= 2;
            cout << "deq: 3\n";
            data = conn.executeQuery(
                "SELECT ST_X(location) lng, ST_Y(location) lat, t2.temperature, t2.dt_pst, "
                    " abs(EXTRACT(EPOCH FROM (dt_pst - timestamp '"+t.time+"'))) time_dif "
                "FROM connectportland.aq_deq_stations t1 join "
                    "connectportland.aq_deq_data2 t2 on t1.station_key = t2.epa_station_key "
                "where ST_DWithin(location,  ST_GeomFromText('"+loc+"',4326), " +numToStr(dist)+ ") "
                "and dt_pst between "+timeFrom+" and "+timeTo+" "
                "and temperature is not null ");
                cout << "deq: 4\n";
            if(!data) break;
        }while((data->empty()) && dist < 100000);
        
        if(data && !data->empty()){
            cout << "deq: 5\n";
            Loc tempLoc(0.0,0.0,t.loc);
            TempType temp2;
            for (result::const_iterator c = data->begin(); c != data->end(); ++c) {
                tempLoc.setPosition(c[1].as<double>(),c[0].as<double>());
                temp2.setData(t.time,c[2].as<double>(),tempLoc,c[4].as<double>());
                if(temp.isEmpty() || temp2 < temp)
                    temp = temp2;
            }
        }
    }
    cout << "deq: 6\n";
    c.temp_deq.put(t,temp);
    return CnC::CNC_Success;
}
