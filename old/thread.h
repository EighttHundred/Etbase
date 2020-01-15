#ifndef ETBASE_THREAD_H
#define ETBASE_THREAD_H

#include "types.h"
#include "mutex.h"
#include <functional>
#include <utility>
#ifndef THREADOP
#define THREADOP
#define ZEROCHECK(num) assert(num==0)
#endif

#ifndef TASKANDDATATYPE
#define TASKANDDATATYPE
typedef void* datatype;
typedef void*(*FuncP)(void*);
typedef std::function<void()> Task;
typedef std::function<void(void*)> TaskP;
typedef std::pair<TaskP,datatype> TaskWP;
#endif
namespace Etbase
{
    class Thread {
    public:
        explicit Thread(Task task_r=nullptr):
        runTask(std::move(task_r)){}
        ~Thread()
        {
            if(!started){
                ZEROCHECK(pthread_join(tid,nullptr));
            }
        }
        void setRunTask(Task task_)
        {
            runTask=std::move(task_);
        }
        void setLeaveTask(Task task_)
        {
            leaveTask=std::move(task_);
        }
        void start();
        void shutdown();
        void join();
        bool isStart()
        {
            return started;
        }
    private:
        void* run()
        {
            runTask();
            return nullptr;
        }
        static void* callRun(void* arg)
        {
            return ((Thread*)arg)->run();
        }
                pthread_t tid=0;
        bool started=false;
        Task runTask;
        Task leaveTask;
    };
}



#endif //ETBASE_THREAD_H
