
#include "guide_temperature.h"


Guide_Tempareture::Guide_Tempareture(std::map<std::string, Guide*> *guide_dictionary, std::string guideID):
Guide(guide_dictionary,guideID),
ctxt(new temperature_context()){
    
}

GuideReturnType * Guide_Tempareture::pushRequest(utl::ParamList &params) {
    std::cout << "\nGuide <" << this->getGuideID() << ">\n" << params;
    
    double lat = utl::strToNum<double>(params["lat"]);
    double lng = utl::strToNum<double>(params["lng"]);
    std::string time = params["time"];
            
    TempTag t(this->getNextTagID(),Loc(lat,lng),time); 
    
    ctxt->temperature_tags.put( t );
    // get result
    TempType *res = new TempType();
    ctxt->temp_temperature.get( t, *res );
    return res;
}

