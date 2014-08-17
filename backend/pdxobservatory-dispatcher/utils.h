/* 
 * File:   utils.h
 * Author: basem
 */

#ifndef UTILS_H
#define	UTILS_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <map>
#include <fstream>
#include <vector>

namespace utl{

    template <typename T>
      std::string numToStr ( T Number )
      {
         std::ostringstream ss;
         ss << Number;
         return ss.str();
      }

    template <typename T>
      T strToNum ( const std::string &Text )
      {
         std::istringstream ss(Text);
         T result;
         return ss >> result ? result : 0;
      }

    template <typename T>
      T strToNum (char* Text )
      {
         std::istringstream ss(Text);
         T result;
         return ss >> result ? result : 0;
      }


    extern std::map<std::string, std::string> configs;

    void parseConfigFile(char* fileName);

    std::string trimLeft(const std::string& s);

    std::string trimRight(const std::string& s);
    
    std::string trim(const std::string& s);
    
    class ParamList{
        std::map<std::string, std::string> params;
        
    public:
        
        ParamList(){}
        ParamList(std::string args);
        
        void setParamValue(const std::string & name, const std::string & value){
            params[name] = value;
        }
        
        std::string getParamValue(std::string name);
        
        void copyOverParamsTo(const std::string & names, ParamList & paramList);
       
        std::string operator[](std::string paramName) {
            return this->getParamValue(paramName);
        };
        
        
        friend std::ostream& operator <<(std::ostream& os, const ParamList& params){
            os << params.toString();
            return os;
        }
        
        
        std::string toString() const;
        
    };
}

namespace std{
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);
}

#endif	/* UTILS_H */

