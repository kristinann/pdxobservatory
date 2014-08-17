/* 
 * File:   guide_temperature_area.h
 * Author: basem
 *
 * Created on March 20, 2014, 5:35 PM
 */

#ifndef GUIDETEMPERATURE_AREA_H
#define	GUIDETEMPERATURE_AREA_H

#include "guide.h"
#include "types.h"

class TemperatureListType: public GuideReturnType{
protected:    
    std::vector<TempType*> *report;

public:   
    TemperatureListType(): GuideReturnType(), report(NULL){};
    
    
    virtual std::string toString() const{
        std::ostringstream ss;
        ss << "[";
        if(this->report){
            for (int i=0,l=this->report->size();i<l;++i) {
                if(i>0) ss << ",";
                ss << (*(*this->report)[i]);
            }
        }
        ss << "]";
        return ss.str();
    }
    std::vector<TempType*> * getReport(){
        return this->report;
    }
    void setReport(std::vector<TempType*> *report){
        this->report = report;
    }
    
    friend std::ostream& operator <<(std::ostream& os, const TemperatureListType& tempRep){
        os << tempRep.toString();
        return os;
    }
};


class Guide_TemperatureArea: public Guide{
private:
    Loc * getCityLocation(const std::string & city);
    TempType * getTempForCityAndTime(utl::ParamList &params);
    TemperatureListType * getTempForCityAndDate(utl::ParamList &params);
    
public:
    Guide_TemperatureArea(std::map<std::string, Guide*> *guide_dictionary, std::string guideID);
    virtual GuideReturnType * pushRequest(utl::ParamList &params);
};

#endif	/* GUIDETEMPERATURE_AREA_H */

