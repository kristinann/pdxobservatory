/* 
 * File:   sweaterguide.h
 * Author: basem
 *
 * Created on March 20, 2014, 5:35 PM
 */

#ifndef SWEATERGUIDE_H
#define	SWEATERGUIDE_H

#include "guide.h"
#include "types.h"
#include "cnc_context/temperature.h"

class Guide_Tempareture: public Guide{
protected:    
    temperature_context *ctxt;
    
public:
    Guide_Tempareture(std::map<std::string, Guide*> *guide_dictionary, std::string guideID);
    virtual GuideReturnType * pushRequest(utl::ParamList &params);
};

#endif	/* SWEATERGUIDE_H */

