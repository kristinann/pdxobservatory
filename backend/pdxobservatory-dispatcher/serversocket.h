/* 
 * File:   serversocket.h
 * Author: Basem
 *
 * Created on February 15, 2014, 6:15 PM
 */

#ifndef SERVERSOCKET_H
#define	SERVERSOCKET_H


#include <iostream>
#include <cstring>      // Needed for memset
#include <sys/socket.h> // Needed for the socket functions
#include <netdb.h>      // Needed for the socket functions
#include <map>
#include "threadlib.h"      
#include "socketconnhandler.h"

class SocketServer: public utl::Thread{
 
    int socketfd;
    int status;
    struct addrinfo host_info;       // The struct that getaddrinfo() fills up with data.
    struct addrinfo *host_info_list; // Pointer to the to the linked list of host_info's.
    const char *port;
    std::map<std::string, Guide*> *guide_dictionary;
    
    
public:
    
    SocketServer(const std::string port, std::map<std::string, Guide*> *guide_dictionary): 
    port(port.c_str()),
    guide_dictionary(guide_dictionary)
    {

        // The MAN page of getaddrinfo() states "All  the other fields in the structure pointed
        // to by hints must contain either 0 or a null pointer, as appropriate." When a struct
        // is created in c++, it will be given a block of memory. This memory is not nessesary
        // empty. Therefor we use the memset function to make sure all fields are NULL.
        memset(&this->host_info, 0, sizeof this->host_info);

        this->host_info.ai_family = AF_UNSPEC;     // IP version not specified. Can be both.
        this->host_info.ai_socktype = SOCK_STREAM; // Use SOCK_STREAM for TCP or SOCK_DGRAM for UDP.
        this->host_info.ai_flags = AI_PASSIVE;     // IP Wildcard

        // Now fill up the linked list of host_info structs with google's address information.
        this->status = getaddrinfo(NULL, this->port, &this->host_info, &this->host_info_list);
        // getaddrinfo returns 0 on succes, or some other value when an error occured.
        // (translated into human readable text by the gai_gai_strerror function).
        if (this->status != 0)  std::cout << "getaddrinfo error" << gai_strerror(this->status) ;


        std::cout << "Creating a socket..."  << std::endl;
        this->socketfd = socket(this->host_info_list->ai_family, this->host_info_list->ai_socktype,
                          this->host_info_list->ai_protocol);
        if (this->socketfd == -1)  std::cout << "socket error " ;

        std::cout << "Binding socket..."  << std::endl;
        // we use to make the setsockopt() function to make sure the port is not in use
        // by a previous execution of our code. (see man page for more information)
        int yes = 1;
        this->status = setsockopt(this->socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
        this->status = bind(this->socketfd, this->host_info_list->ai_addr, this->host_info_list->ai_addrlen);
        if (this->status == -1)  std::cout << "bind error" << std::endl ;

        std::cout << "Listen()ing for connections..."  << std::endl;
        this->status =  listen(this->socketfd, 5);
        if (status == -1)  std::cout << "listen error" << std::endl ;  
    }
    virtual ~SocketServer(){}
    
    virtual void run(){
        int new_sd;
        struct sockaddr_storage their_addr;
        socklen_t addr_size = sizeof(their_addr);
        while(!this->isTerminated()){
            new_sd = accept(socketfd, (struct sockaddr *)&their_addr, &addr_size);
            if (new_sd == -1)
            {
                std::cout << "listen error" << std::endl ;
            }
            else
            {
                std::cout << "Connection accepted. Using new socketfd : "  <<  new_sd << std::endl;
                new ConnectionHandler(new_sd, guide_dictionary);
            }
        }
    }
    
    void activate(bool status){
        
        if(status){
            this->start();
        }else{
            this->terminate();
            std::cout << "Stopping server..." << std::endl;
            freeaddrinfo(this->host_info_list);
            close(this->socketfd);
        }
    }
    
};

#endif	/* SERVERSOCKET_H */

