
#include "guide_mobility_extended.h"

using namespace std; 
using namespace utl;

Guide_Mobility_Extended::Guide_Mobility_Extended(std::map<std::string, Guide*> *guide_dictionary, std::string guideID):
Guide(guide_dictionary,guideID){
    
}

MobilityType* Guide_Mobility_Extended::generateSpeedLimitPercReport(utl::ParamList &params){
    
    cout << "mobility advanced: 1" << endl;
    
    utl::ParamList new_params(string("report_type=speed&with=speed-limit"));
    params.copyOverParamsTo(string("region,by,time,restrict_time_from,restrict_time_to,year"),new_params);
    
    MobilityType * response = (MobilityType*)((*guide_dictionary)["mobility"]->pushRequest(new_params));
    
    cout << "mobility advanced: 2" << endl;
    
    std::vector<MobilityReportItem*> * report = response->getReport();
    
    if(report){
        
        cout << "mobility advanced: 3" << endl;
        
        for(int i=0,l=report->size();i<l;++i){
            (*report)[i] = (MobilityReportItem*) new MobilityReportItemForSpeedAsPercOfSpeedLimit( 
                            (MobilityReportItemForSpeed*)((*report)[i]));
        }
        
        cout << "mobility advanced: 4" << endl;
    }
    
    cout << "mobility advanced: 5" << endl;
    return response;
}

MobilityType* Guide_Mobility_Extended::generateTraveltimeReport(utl::ParamList &params){
    
    cout << "mobility advanced: 1" << endl;
    
    string with = params["with"];
    
    if(with.empty())
        with = string("length");
    else
        with += ",length";
                
    utl::ParamList new_params(string("report_type=speed&with="+with));
    params.copyOverParamsTo(string("region,by,time,restrict_time_from,restrict_time_to,year"),new_params);
    
    MobilityType * response = (MobilityType*)((*guide_dictionary)["mobility"]->pushRequest(new_params));
    
    cout << "mobility advanced: 2" << endl;
    
    std::vector<MobilityReportItem*> * report = response->getReport();
    
    if(report){
        
        cout << "mobility advanced: 3" << endl;
        
        for(int i=0,l=report->size();i<l;++i){
            (*report)[i] = (MobilityReportItem*) new MobilityReportItemForTravelTime( 
                            (MobilityReportItemForSpeed*)((*report)[i]));
        }
        
        cout << "mobility advanced: 4" << endl;
    }
    
    cout << "mobility advanced: 5" << endl;
    return response;
}

GuideReturnType * Guide_Mobility_Extended::pushRequest(utl::ParamList &params) {
    cout << "\nGuide <" << this->getGuideID() << ">\n" << params;
    string report_type = params["report_type"];
    
    GuideReturnType *res; 
    if(report_type.compare("speed-as-perc-of-speed-limit") == 0){
        res = this->generateSpeedLimitPercReport(params);
    }else if(report_type.compare("traveltime") == 0){
        res = this->generateTraveltimeReport(params);
    }else{
        // Unknown report type. Return an empty report.
        res = new MobilityType();
    }
    
    return res;
}

