/* 
 * File:   guide_mobility_extended.h
 * Author: basem
 *
 * Created on March 20, 2014, 5:35 PM
 */

#ifndef GUIDEMOBILITYEXTENDED_H
#define	GUIDEMOBILITYEXTENDED_H

#include "guide_mobility.h"
#include "types.h"

struct MobilityReportItemForSpeedAsPercOfSpeedLimit: public MobilityReportItemForSpeed{
    
    float speedperc;
    
    MobilityReportItemForSpeedAsPercOfSpeedLimit(): MobilityReportItemForSpeed(){};
    
    MobilityReportItemForSpeedAsPercOfSpeedLimit(MobilityReportItemForSpeed * speed_item): 
        MobilityReportItemForSpeed(*speed_item), 
        speedperc(speed_item->speedlimit? speed_item->speed / speed_item->speedlimit * 100 : 0){};
    
    virtual std::string toString() const{
        return MobilityReportItemForSpeed::toString()+
                ",\"percent\":"+utl::numToStr(this->speedperc);
    }
};

struct MobilityReportItemForTravelTime: public MobilityReportItemForSpeed{
    
    float traveltime;
    
    MobilityReportItemForTravelTime(): MobilityReportItemForSpeed(){};
    
    MobilityReportItemForTravelTime(MobilityReportItemForSpeed * speed_item): 
        MobilityReportItemForSpeed(*speed_item), 
        traveltime(speed_item->speed && speed_item->length? speed_item->length / speed_item->speed * 60 : 0){};
    
    virtual std::string toString() const{
        return MobilityReportItemForSpeed::toString()+
                ",\"traveltime\":"+utl::numToStr(this->traveltime);
    }
};


class Guide_Mobility_Extended: public Guide{

private:
    
    MobilityType * generateSpeedLimitPercReport(utl::ParamList &params);
    MobilityType * generateTraveltimeReport(utl::ParamList &params);
    
public:
    Guide_Mobility_Extended(std::map<std::string, Guide*> *guide_dictionary, std::string guideID);
    virtual GuideReturnType * pushRequest(utl::ParamList &params);
};

#endif	/* GUIDEMOBILITYEXTENDED_H */

