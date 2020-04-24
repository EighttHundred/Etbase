//
// Created by eighthundred on 2020/4/24.
//

#include "../include/Timer.h"
#include "../include/Event.h"
#include <ctime>

bool Etbase::Timer::check() {
    int curTime=clock();
    if(times==0||lastTime+timeout>curTime){
        return false;
    }else{
        --times;
        lastTime=curTime;
        return true;
    }
}

void Etbase::Timer::setTimes(int times_) {
    times=times_;
}

void Etbase::Timer::setTimeout(int timeout_) {
    timeout=timeout_;
}

void Etbase::Timer::begin() {
    lastTime=clock();
    lastTime+=delay;
}

void Etbase::Timer::setDelay(int delay_) {
    delay=delay_;
}

int Etbase::Timer::getTimes() {
    return times;
}

void Etbase::Timer::assign(Task task_) {
    task=std::move(task_);
}

void Etbase::Timer::runTask() {
    task();
}

