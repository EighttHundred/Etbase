//
// Created by eight on 1/17/20.
//

#include "Mutex.h"

Etbase::Mutex::Mutex():
    mutex(PTHREAD_MUTEX_INITIALIZER),holder(0){
}

Etbase::Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex);
}

void Etbase::Mutex::lock() {
    pthread_mutex_lock(&mutex);
    assign();
}

void Etbase::Mutex::unlock() {
    unassign();
    pthread_mutex_unlock(&mutex)
}

pthread_t Etbase::Mutex::getHolder() {
    return holder;
}

void Etbase::Mutex::assign() {
    holder=pthread_self();
}

void Etbase::Mutex::unassign() {
    holder=0;
}

Etbase::Guard::Guard(const Etbase::Mutex &mutex_):
    mutex(mutex_){
    mutex.lock();
}

Etbase::Guard::~Guard() {
    mutex.unlock();
}
