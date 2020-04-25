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
        int threadNum=3;
        bool stop=false;
        pthread_t* threads;
        EventQueue& evqueue;
        Mutex mutex;
    public:
        ThreadPool(EventQueue& evqueue_);
        ~ThreadPool();
        void start();
        void setThreadNum(int num);
    private:
        bool checkStop();
        void stopPool();
        static void* worker(void* arg);
        void run();
    };
}



#endif //ETBASE_THREADPOOL_H
