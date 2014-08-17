/* 
 * File:   dbconn.cpp
 * Author: Basem Elazzabi
 *
 */

#include <iostream>
#include "dbconn.h"
#include "utils.h"

using namespace pqxx;

DBConn::DBConn():
    open(false)
{
    try{ 
        std::ostringstream os;
        os <<  "dbname=" << utl::configs["db_name"] << 
              " user=" << utl::configs["db_user"] << 
              " password=" << utl::configs["db_pass"] << 
              " hostaddr=" << utl::configs["db_host"] << 
              " port=" << utl::configs["db_port"];
        this->conn = new connection(os.str());
        if (this->conn->is_open()) {
            open = true;
        } else {
            std::cout << "Can't open database" << std::endl;
        }
     }catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
     }
}

DBConn::~DBConn() {
    if(this->open){
        this->close();
    }
}

pqxx::result* DBConn::executeQuery(const std::string& sql) {
    if(!open) return NULL;
    try{
        nontransaction N(*(this->conn));
        result *res = new result( N.exec( sql ));
        return res;
    }catch (const std::exception &e){
        std::cerr << e.what() << std::endl;
        return NULL;
    }
}


bool DBConn::is_open(){
    return this->open;
}

void DBConn::close() {
    if(!open) return;
    this->conn->disconnect();
    delete this->conn;
}
