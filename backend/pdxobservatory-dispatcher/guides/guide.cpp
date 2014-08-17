#include "guide.h"

Guide::Guide(std::map<std::string, Guide*> *guide_dictionary, std::string guideID): 
guide_dictionary(guide_dictionary),
guideID(guideID), 
mtx(new std::mutex()),
tagIDCounter(0){
    (*guide_dictionary)[guideID] = this;
}

long Guide::getNextTagID() {
    long tagID;
    mtx->lock();
    tagID = ++this->tagIDCounter;
    mtx->unlock();
    return tagID;
}
