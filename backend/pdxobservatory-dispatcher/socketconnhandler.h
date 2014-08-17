/* 
 * File:   socketconnhandler.h
 * Author: Basem
 *
 * Created on February 15, 2014, 7:24 PM
 */

#ifndef SOCKETCONNHANDLER_H
#define	SOCKETCONNHANDLER_H

#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <map>
#include "guides/guide.h"
#include "threadlib.h"  
#include "utils.h"



class ConnectionHandler: public utl::Thread{
    int socketfd;
    std::map<std::string, Guide*> *guide_dictionary;
        
    virtual void run();
    
protected:
    
    virtual void handleRequest(char dataBuff[], ssize_t size);
    
public:
    ConnectionHandler(int socketfd, std::map<std::string, Guide*> *guide_dictionary);
    ssize_t sendData(const char dataBuff[], ssize_t size);
    void disconnect();
};


#endif	/* SOCKETCONNHANDLER_H */

