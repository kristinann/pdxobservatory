/* 
 * File:   types.cpp
 * Author: Basem Elazzabi
 *
 */
 
#include "types.h"
#include <cmath>



std::string Loc::toGIS() const {
    return "POINT(" +utl::numToStr(this->lng)+ " " +utl::numToStr(this->lat)+ ")";
}

void Loc::setPosition(double lat, double lng) {
    this->lat = lat;
    this->lng = lng;
}

double Loc::operator-(const Loc& loc) const {
    double d2r = M_PI/180;
    return 6376136 * acos(
                sin(this->lat*d2r) * sin(loc.lat*d2r)
                + cos(this->lat*d2r) * cos(loc.lat*d2r) *
                cos(loc.lng*d2r - this->lng*d2r));
}

double Loc::getDistance() const{
    if(!this->refPoint) return 0.0;
    return (*this) - (*this->refPoint);
}


std::ostream& operator <<(std::ostream& os, const Loc& loc){
    os << "{\"lat\": " << loc.lat << ",\"lng\":" << loc.lng;
    if(loc.refPoint)
        os << ",\"diff\": " << loc.getDistance();
    os << "}";
    return os;
}


void TempType::setData(const std::string & time, double temp, const Loc &loc, double timeDif) {
    this->time = time;
    this->temp = temp;
    this->loc = loc;
    this->timeDif = timeDif;
    this->empty = false;
}

double TempType::getTimeDif() const {
    return this->timeDif;
}

bool TempType::isEmpty() const {
    return this->empty;
}


void TempType::setLoc(Loc& loc) {
    this->loc = loc;
}

bool TempType::operator<(const TempType& temp) const {
    if(temp.isEmpty()) return true;
    if(this->isEmpty()) return false;
    return ((this->timeDif * TIME_WEIGHT + 1) * (this->loc.getDistance() * DISTANCE_WEIGHT + 1)) < 
           ((temp.timeDif * TIME_WEIGHT + 1 ) * (temp.loc.getDistance() * DISTANCE_WEIGHT + 1));
}


std::ostream& operator <<(std::ostream& os, const TempType& temp) {
    os << "{\"time\":\"" << temp.time << "\",\"timediff\": " << temp.timeDif << ",\"locinfo\": " << temp.loc << ", \"temperature\": " << temp.temp << "}";
    return os;
}

std::string TempType::toString() const {
    std::ostringstream ss;
    ss << (*this);
    return ss.str();
}



bool operator ==(const TempTag &lhs, const TempTag &rhs){
    return lhs.task_id == rhs.task_id;
}

std::ostream& operator <<(std::ostream& os, const TempTag& tag){
    os << tag.task_id << "#[" << tag.time << ": " << tag.loc << "]" ;
    return os;
}


