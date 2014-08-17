/* 
 * File:   dbconn.h
 * Author: Basem Elazzabi
 *
 */

#ifndef DBCONN_H
#define	DBCONN_H

#include <pqxx/pqxx> 
#include <cstdlib>


class DBConn{
    
    pqxx::connection *conn;
    bool open;
    
public:
    DBConn();
    ~DBConn();
    bool is_open();
    void close();
    pqxx::result* executeQuery(const std::string & sql);
    
};

#endif	/* DBCONN_H */

