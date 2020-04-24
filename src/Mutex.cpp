//
// Created by eight on 1/17/20.
//

#include "../include/Mutex.h"
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
    pthread_mutex_unlock(&mutex);
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

pthread_mutex_t* Etbase::Mutex::get() {
    return &mutex;
}

Etbase::Guard::Guard( Etbase::Mutex &mutex_):
    mutex(mutex_){
    mutex.lock();
}

Etbase::Guard::~Guard() {
    mutex.unlock();
}

Etbase::Condition::Condition(Etbase::Mutex &mutex_):
    mutex(mutex_),cond(PTHREAD_COND_INITIALIZER){
}

Etbase::Condition::~Condition() {
    pthread_cond_destroy(&cond);
}

bool Etbase::Condition::wait() {
    return pthread_cond_wait(&cond,mutex.get())==0;
}

bool Etbase::Condition::signal() {
    return pthread_cond_signal(&cond)==0;
}

