/* 
 * File:   guide_mobility.h
 * Author: basem
 *
 * Created on March 20, 2014, 5:35 PM
 */

#ifndef GUIDEMOBILITY_H
#define	GUIDEMOBILITY_H

#include "guide.h"
#include "types.h"

struct MobilityReportItem{
    float time;
    int highwayid;
    std::string highwayname;
    int stationid;
    
    
    MobilityReportItem(){};
    
    MobilityReportItem(float time, int highwayid,const std::string &highwayname):
        time(time),highwayid(highwayid),highwayname(std::string(highwayname)),stationid(0){};
    
    MobilityReportItem(float time, int highwayid,const std::string &highwayname, int stationid):
        time(time),highwayid(highwayid),highwayname(std::string(highwayname)),stationid(stationid){};
    
    virtual std::string toString() const{
        return "\"time\":"+utl::numToStr(this->time)+
                ",\"highwayid\":"+utl::numToStr(this->highwayid)+
                ",\"highwayname\":\""+this->highwayname+"\""+
                (this->stationid? ",\"stationid\":"+utl::numToStr(this->stationid):"");
    }
};

struct MobilityReportItemForSpeed: public MobilityReportItem {
    
    float speed;
    float speedlimit;
    float length;
    float milepost;
    
    MobilityReportItemForSpeed(): MobilityReportItem(){};
    
    MobilityReportItemForSpeed(float time, int highwayid,const std::string &highwayname, 
                int stationid,float speed, float length, float speedlimit, float milepost): 
        MobilityReportItem(time, highwayid, highwayname,stationid), 
        speed(speed), length(length), speedlimit(speedlimit),milepost(milepost){};    
        
        
    virtual std::string toString() const{
        return MobilityReportItem::toString()+
                ",\"speed\":"+utl::numToStr(this->speed)+
                (this->length? ",\"length\":"+utl::numToStr(this->length):"")+
                (this->speedlimit? ",\"speedlimit\":"+utl::numToStr(this->speedlimit):"")+
                (this->milepost? ",\"milepost\":"+utl::numToStr(this->milepost):"");
    }
};

struct MobilityReportItemForVolume: public MobilityReportItem {
    
    float volume;
    float length;
    float avgvolume;
    float avgvolumepl;
    
    MobilityReportItemForVolume(): MobilityReportItem(){};
    
    MobilityReportItemForVolume(float time, int highwayid,const std::string &highwayname, 
                int stationid,float volume, float length, float avgvolume, float avgvolumepl): 
        MobilityReportItem(time, highwayid, highwayname,stationid), 
        volume(volume), length(length), avgvolume(avgvolume),avgvolumepl(avgvolumepl){};    
        
        
    virtual std::string toString() const{
        return MobilityReportItem::toString()+
                ",\"volume\":"+utl::numToStr(this->volume)+
                (this->length? ",\"length\":"+utl::numToStr(this->length):"")+
                (this->avgvolume? ",\"avgvolume\":"+utl::numToStr(this->avgvolume):"")+
                (this->avgvolumepl? ",\"avgvolumepl\":"+utl::numToStr(this->avgvolumepl):"");
    }
};

class MobilityType: public GuideReturnType{
protected:    
    std::vector<MobilityReportItem*> *report;

public:   
    MobilityType(): GuideReturnType(), report(NULL){};
    
    
    virtual std::string toString() const{
        std::ostringstream ss;
        ss << "[";
        if(this->report){
            std::cout << "Report size: " << this->report->size() << std::endl;
            for (int i=0,l=this->report->size();i<l;++i) {
                if(i>0) ss << ",";
                ss << "{" << (*this->report)[i]->toString() << "}";
            }
        }
        ss << "]";
        return ss.str();
    }
    std::vector<MobilityReportItem*> * getReport(){
        return this->report;
    }
    void setReport(std::vector<MobilityReportItem*> *report){
        this->report = report;
    }
    
    friend std::ostream& operator <<(std::ostream& os, const MobilityType& mobility){
        os << mobility.toString();
        return os;
    }
};

class Guide_Mobility: public Guide{
private:
    MobilityType * generateSpeedReport(utl::ParamList &params);
    MobilityType * generateVolumeReport(utl::ParamList &params);
    
    void buildUsefiedMobilityTable();
    
public:
    Guide_Mobility(std::map<std::string, Guide*> *guide_dictionary, std::string guideID);
    virtual GuideReturnType * pushRequest(utl::ParamList &params);
};

#endif	/* GUIDEMOBILITY_H */

