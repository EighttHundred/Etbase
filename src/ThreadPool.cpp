//
// Created by eight on 1/18/20.
//

#include "../include/ThreadPool.h"



void *Etbase::ThreadPool::worker(void *arg) {
    auto pool=(ThreadPool*)arg;
    pool->run();
    return pool;
}

Etbase::ThreadPool::~ThreadPool() {
    stopPool();
    if(threads){
//        for(int i=0;i<threadNum;++i){
//            pthread_join(threads[i], nullptr);
//        }
        delete[] threads;
    }
}

void Etbase::ThreadPool::run() {
    while(true){
        if(checkStop()) break;
        Event event=evqueue.get();
        if(event.fd>0)
            event.runTask();
    }
//    pthread_exit(nullptr);
}

bool Etbase::ThreadPool::checkStop() {
    Guard guard(mutex);
    return stop;
}

void Etbase::ThreadPool::stopPool() {
    Guard guard(mutex);
    stop=true;
}

void Etbase::ThreadPool::setThreadNum(int num) {
    threadNum=num;
}

void Etbase::ThreadPool::start() {
    threads=new pthread_t[threadNum];
    for(int i=0;i<threadNum;++i){
        pthread_create(threads+i,nullptr,worker,this);
        pthread_detach(threads[i]);
    }
}

Etbase::ThreadPool::ThreadPool(Etbase::EventQueue &evqueue_)
    :evqueue(evqueue_){
}

