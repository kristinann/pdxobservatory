
#include "utils.h"

using namespace std; 


map<std::string, std::string> utl::configs;

void utl::parseConfigFile(char* fileName){
    std::string id, eq, val;
    std::ifstream cfgfile(fileName);
    while(cfgfile >> id >> eq >> val)
    {
      if (id[0] == '#') continue;  // skip comments
      if (eq != "=") throw std::runtime_error("Parse error");

      configs[id] = val;
    }
}

utl::ParamList::ParamList(std::string args) {
    vector<string> x = split(args, '&');
    for(int i=0,l=x.size();i<l;++i) {
        vector<string> pair = split(x[i], '=');
        params[trim(pair[0])] = trim(pair[1]);
    }
}

std::string utl::ParamList::getParamValue(std::string name) {
    map<string,string>::iterator i = params.find(name);
    if (i == params.end()) return string("");
    return i->second;
}

string utl::ParamList::toString() const{
    std::ostringstream ss;
    ss << "----------------\n";
    ss << "Param List\n";
    ss << "----------------\n";
    for(std::map<string,string>::const_iterator iter = this->params.begin(); iter != this->params.end(); ++iter){
        ss << iter->first << ": " << iter->second << endl;
    }
    ss << "----------------\n";
    return ss.str();
}

void utl::ParamList::copyOverParamsTo(const std::string& names, utl::ParamList& paramList) {
    vector<string> name_list = split(names, ',');
    for(int i=0,l=name_list.size();i<l;++i){
        if(!(*this)[name_list[i]].empty()){
            paramList.setParamValue(name_list[i], (*this)[name_list[i]]);
        }
    }
}



std::string utl::trimLeft(const std::string& s)
{
    size_t startpos = s.find_first_not_of(" \n\r\t");
    return (startpos == std::string::npos) ? "" : s.substr(startpos);
}

std::string utl::trimRight(const std::string& s)
{
    size_t endpos = s.find_last_not_of(" \n\r\t");
    return (endpos == std::string::npos) ? "" : s.substr(0, endpos+1);
}
std::string utl::trim(const std::string& s)
{
    return trimRight(trimLeft(s));
}


std::vector<std::string> & std::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> std::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}