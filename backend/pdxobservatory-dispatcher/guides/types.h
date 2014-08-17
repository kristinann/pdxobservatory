/* 
 * File:   types.h
 * Author: Basem Elazzabi
 *
 */

#ifndef TYPES_H
#define	TYPES_H

#include "../utils.h"


class Loc{
    
    double lat;
    double lng;
    const Loc *refPoint;

public:    
    Loc(double lat, double lng): lat(lat), lng(lng), refPoint(NULL){};
    Loc(double lat, double lng, const Loc& refPoint): lat(lat), lng(lng), refPoint(&refPoint){};
    void setPosition(double lat, double lng);
    friend std::ostream& operator <<(std::ostream& os, const Loc& loc);
    double getLat(){ return lat; }
    double getLng(){ return lng; }
    double operator-(const Loc& loc) const;
    double getDistance() const;
    std::string toGIS() const;
};

class GuideReturnType{
public:
    GuideReturnType(){};
    virtual std::string toString() const =0;
};

class TempType: public GuideReturnType{
    std::string time;
    double temp;
    Loc loc;
    double timeDif;
    bool empty;
    static constexpr double TIME_WEIGHT = 0.003;
    static constexpr double DISTANCE_WEIGHT = 0.0005;

public:   
    TempType(): GuideReturnType(), time(std::string("")), temp(0.0), loc(0.0, 0.0), timeDif(0.0), empty(true){};
    void setData(const std::string & time, double temp,const Loc &loc, double timeDif);
    void setLoc(Loc& loc);
    friend std::ostream& operator <<(std::ostream& os, const TempType& temp);
    double getTimeDif() const;
    bool operator<(const TempType& temp) const;
    bool isEmpty() const;
    virtual std::string toString() const;
};

struct TempTag{
    const long task_id;
    const Loc loc;
    const std::string time;
    
    TempTag(long task_id, Loc loc, std::string time): task_id(task_id), loc(loc), time(time){};
    friend std::ostream& operator <<(std::ostream& os, const TempTag& tag);
    friend bool operator ==(const TempTag &lhs, const TempTag &rhs);
};


#endif	/* TYPES_H */

