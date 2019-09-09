#ifndef ETBASE_MUTEX_H
#define ETBASE_MUTEX_H

#include <pthread.h>
#include <assert.h>

#ifndef THREADOP
#define ZEROCHECK(num) assert(num==0)
#endif

namespace Etbase
{
    class Mutex {
    public:
        Mutex():mutex(PTHREAD_MUTEX_INITIALIZER),holder(0){}
        ~Mutex()
        {
            ZEROCHECK(pthread_mutex_destroy(&mutex));
        }
        void lock()
        {
            ZEROCHECK(pthread_mutex_lock(&mutex));
            assignHolder();
        }
        void unlock()
        {
            unassignHolder();
            ZEROCHECK(pthread_mutex_unlock(&mutex));
        }
        pthread_t getHolder()
        {
            return holder;
        }
        pthread_mutex_t* getMutexPtr()
        {
            return &mutex;
        }
        void assignHolder()
        {
            holder=pthread_self();
        }
        void unassignHolder()
        {
            holder=0;
        }
    private:
        pthread_mutex_t mutex;
        pthread_t holder;
    };
    class LockGuard{
    public:
        explicit LockGuard(Mutex& mutex_):mutex(mutex_)
        {
            mutex.lock();
        }
        ~LockGuard()
        {
            mutex.unlock();
        }
    private:
        Mutex& mutex;
    };
    class UnassignGuard{
    public:
        explicit UnassignGuard(Mutex& mutex_):mutex(mutex_)
        {
            mutex.unassignHolder();
        }
        ~UnassignGuard()
        {
            mutex.assignHolder();
        }
    private:
        Mutex& mutex;
    };
    class Condition{
    public:
        explicit Condition(Mutex& mutex_):
        cond(PTHREAD_COND_INITIALIZER),mutex(mutex_){}
        ~Condition()
        {
            ZEROCHECK(pthread_cond_destroy(&cond));
        }
        void wait()
        {
            UnassignGuard unassignGuard(mutex);
            ZEROCHECK(pthread_cond_wait(&cond,mutex.getMutexPtr()));
        }
        void signal()
        {
            ZEROCHECK(pthread_cond_signal(&cond));
        }
        void broadcast()
        {
            ZEROCHECK(pthread_cond_broadcast(&cond));
        }
    private:
        Mutex& mutex;
        pthread_cond_t cond;
    };
}

#endif //ETBASE_MUTEX_H
