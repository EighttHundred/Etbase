//
// Created by eighthundred on 2020/4/24.
//

#include "../include/Timer.h"
#include "../include/Event.h"
#include <ctime>

bool Etbase::Timer::check() {
    int curTime=::clock();
    if(times==0||lastTime>curTime){
        return false;
    }else{
        --times;
        lastTime=curTime+timeout;
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
    lastTime=(int)::clock()+delay;
}

void Etbase::Timer::setDelay(int delay_) {
    delay=delay_;
}

int Etbase::Timer::getTimes() {
    return times;
}

void Etbase::Timer::runTask() {
    task();
}

bool Etbase::Timer::isTriggered() {
    if(!triggered){
        triggered=true;
        return false;
    }
    return true;
}

bool Etbase::Timer::checkAlive() {
    return getTimes()!=0;
}

void Etbase::Timer::setTask(Etbase::Task task_) {
    task=std::move(task_);
}

