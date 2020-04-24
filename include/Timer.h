//
// Created by eighthundred on 2020/4/24.
//

#ifndef ETBASE_TIMER_H
#define ETBASE_TIMER_H

#include "Event.h"
namespace Etbase{

    class Timer {
    private:
        int delay=0;
        int lastTime=-1;
        int timeout=1000;
        int times;
        Task task;
    public:
        int getTimes();
        void setTimes(int times_);
        void setTimeout(int timeout_);
        void setDelay(int delay_);
        bool check();
        void begin();
        void runTask();
        void assign(Task task_);
    };

}


#endif //ETBASE_TIMER_H
