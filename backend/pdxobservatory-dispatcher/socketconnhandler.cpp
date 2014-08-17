#include "socketconnhandler.h"

using namespace std;

ConnectionHandler::ConnectionHandler(int socketfd, map<string, Guide*> *guide_dictionary) :
socketfd(socketfd),
guide_dictionary(guide_dictionary){
    this->start();
}

void ConnectionHandler::run() {
    
    cout << "Waiting to recieve data..."  << endl;
    ssize_t bytes_recieved;
    char incomming_data_buffer[2000];
    while(!this->isTerminated()){
        bytes_recieved = recv(this->socketfd, incomming_data_buffer,2000, 0);
        // If no data arrives, the program will just wait here until some data arrives.
        if (bytes_recieved == 0) cout << "host shut down." << endl ;
        if (bytes_recieved == -1) cout << "recieve error!" << endl ;
        cout << bytes_recieved << " bytes recieved :" << endl ;
        
        incomming_data_buffer[bytes_recieved] = '\0';
        this->handleRequest(incomming_data_buffer,bytes_recieved);
    }
}

ssize_t ConnectionHandler::sendData(const char dataBuff[], ssize_t size) {
    cout << "sending back data..."  << endl;
    ssize_t bytes_sent;
    bytes_sent = send(this->socketfd, dataBuff, size, 0);
    return bytes_sent;
}

void ConnectionHandler::disconnect() {
    this->terminate();
    close(this->socketfd);
    delete this;
}

void ConnectionHandler::handleRequest(char dataBuff[], ssize_t size) {
    string args(dataBuff);
    cout << args << endl;
    /*
    vector<string> x = split(args, '&');
    map<string, string> params;
    for(int i=0,l=x.size();i<l;++i) {
        vector<string> pair = split(x[i], '=');
        params[pair[0]] = pair[1];
    }
    */
    utl::ParamList params(args);
    string guide_id = params["guide_id"];
    GuideReturnType * response = (*guide_dictionary)[guide_id]->pushRequest(params);
    string retVal = response->toString();
    delete response;
    this->sendData(retVal.c_str(),retVal.length());
    this->disconnect();
}