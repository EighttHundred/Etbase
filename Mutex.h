//
// Created by eight on 1/17/20.
//

#ifndef ETBASE_MUTEX_H
#define ETBASE_MUTEX_H

#include <pthread.h>
namespace Etbase{

    class Mutex {
        pthread_mutex_t mutex;
        pthread_t holder;
    public:
        Mutex();
        ~Mutex();
        void lock();
        void unlock();
        pthread_t getHolder();
        void assign();
        void unassign();
    };

    class Guard{
        Mutex mutex;
    public:
        explicit Guard(const Mutex& mutex_);
        ~Guard();
    };

}



#endif //ETBASE_MUTEX_H
