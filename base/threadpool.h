#ifndef ETBASE_THREADPOOL_H
#define ETBASE_THREADPOOL_H

#include <queue>
#include <vector>
#include <memory>
#include "./thread.h"
#include "./mutex.h"
typedef size_t sizetype;
namespace Etbase
{
    class ThreadPool {
    public:
        explicit ThreadPool(int poolSize_=10):notFull(mutex),notEmpty(mutex)
        {
            init(poolSize_);
        }
        ~ThreadPool()
        {
            stop();
        }
        void init(sizetype poolSize_);
        void stop();
        void loadTask(TaskP& taskP,datatype data=nullptr);
    private:
        TaskWP takeTask();
        Condition notFull;
        Condition notEmpty;
        void runInPool();
        mutable Mutex mutex;
        std::vector<std::unique_ptr<Thread>> pool;
        std::queue<TaskWP> taskQueue;
        const sizetype maxQueueSize=70;
        const sizetype maxPoolSize=50;
        bool running=false;
    };
}



#endif //ETBASE_THREADPOOL_H
