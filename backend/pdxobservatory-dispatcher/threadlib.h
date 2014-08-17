/* 
 * File:   threadlib.h
 * Author: Basem
 *
 * Created on February 15, 2014, 9:55 PM
 */

#ifndef THREADLIB_H
#define	THREADLIB_H

#include <thread>

namespace utl{
    class Thread{
        
        std::thread *tid;
        bool running;
        bool terminated;
        
    public:
        Thread():running(false), terminated(false){
            
        }
        void start();
        void waitToFinish();
        void terminate();
        bool isTerminated();
        virtual void run(){}
    };
}

#endif	/* THREADLIB_H */

