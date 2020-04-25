//
// Created by eight on 1/18/20.
//

#include "../include/ThreadPool.h"


Etbase::ThreadPool::ThreadPool(int num_,  Etbase::EventQueue &evqueue_):
    evqueue(evqueue_){
    Guard guard(mutex);
    num=num_;
    threads=new pthread_t[num];
    for(int i=0;i<num;++i){
        pthread_create(threads+i,nullptr,worker,this);
        pthread_detach(threads[i]);
    }
}

void *Etbase::ThreadPool::worker(void *arg) {
    auto pool=(ThreadPool*)arg;
    pool->run();
    return pool;
}

Etbase::ThreadPool::~ThreadPool() {
    Guard guard(mutex);
    delete[] threads;
    stop=true;
}

void Etbase::ThreadPool::run() {
    while(true){
        mutex.lock();
        if(stop) break;
        mutex.unlock();
        Event event=evqueue.get();
        if(event.fd>0)
            event.doCallback();
    }
}

