/* 
 * File:   guide.h
 * Author: basem
 *
 * Created on March 13, 2014, 7:11 PM
 */

#ifndef GUIDE_H
#define	GUIDE_H

#include <mutex>          // std::mutex
#include <map>
#include "types.h"

class Guide{
    
    long tagIDCounter;
    std::mutex *mtx;
    std::string guideID;
 
protected:
    std::map<std::string, Guide*> *guide_dictionary;
    
    long getNextTagID();
    
public:
    Guide(std::map<std::string, Guide*> *guide_dictionary, std::string guideID);
    const std::string &getGuideID(){ return guideID; }
    virtual GuideReturnType * pushRequest(utl::ParamList &params) =0;
};


#endif	/* GUIDE_H */

