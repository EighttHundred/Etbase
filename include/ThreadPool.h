//
// Created by eight on 1/18/20.
//

#ifndef ETBASE_THREADPOOL_H
#define ETBASE_THREADPOOL_H

#include "EventQueue.h"
namespace Etbase{
    class ThreadPool {
    public:
        //equals to number cpu cores
        int num=3;
        bool stop=false;
        pthread_t* threads;
        EventQueue& evqueue;
        Mutex mutex;
    public:
        ThreadPool(int num_, EventQueue& evqueue_);
        ~ThreadPool();
    private:
        static void* worker(void* arg);
        void run();
    };
}



#endif //ETBASE_THREADPOOL_H
