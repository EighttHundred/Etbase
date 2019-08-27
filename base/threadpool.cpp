#include "./threadpool.h"
#include  <functional>
void Etbase::ThreadPool::init(sizetype poolSize_=10) {
    LockGuard lockGuard(mutex);
    sizetype poolSize=std::min(maxPoolSize,poolSize_);
    pool.reserve(poolSize);
    for(auto i=0;i<poolSize;++i){
        pool.emplace_back(new Thread(std::bind(&ThreadPool::runInPool,this)));
        pool[i]->start();
    }
}

TaskWP Etbase::ThreadPool::takeTask() {
    LockGuard lockGuard(mutex);
    while(taskQueue.empty()){
        notEmpty.wait();
    }
    if(!taskQueue.empty()){
        TaskWP nowTask=taskQueue.front();
        taskQueue.pop();
        notFull.broadcast();
        return nowTask;
    }
    return TaskWP(nullptr,nullptr);
}

void Etbase::ThreadPool::runInPool() {
    while(running){
        TaskWP nowTask=takeTask();
        if(nowTask.first!=nullptr)
            nowTask.first(nowTask.second);
    }
}

void Etbase::ThreadPool::stop() {
    LockGuard lockGuard(mutex);
    if(running){
        running=false;
        notEmpty.broadcast();
        for(auto &thr:pool){
            thr->join();
        }
    }
}

void Etbase::ThreadPool::loadTask(TaskP &taskP, datatype data) {
    if(pool.empty()){
        taskP(data);
    }
    else{
        LockGuard lockGuard(mutex);
        if(taskQueue.size()>=maxQueueSize){
            notFull.wait();
        }
        taskQueue.push(TaskWP(taskP,data));
        if(taskQueue.size()==1){
            notEmpty.broadcast();
        }
    }
}

