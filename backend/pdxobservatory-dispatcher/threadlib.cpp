
#include "threadlib.h"


void utl::Thread::start(){
    this->tid = new std::thread(&utl::Thread::run, this);     // spawn new thread that calls run()
    this->running = true;
}
void utl::Thread::terminate(){
    this->terminated = true;
}
void utl::Thread::waitToFinish(){
    if(this->tid)
        this->tid->join(); // pauses until the thread finishes
    this->running = false;
}

bool utl::Thread::isTerminated() {
    return this->terminated;
}

