#include "eventbase.h"

int Etbase::EventBase::addEvent(Event&& event)
{
    return evmap.addMap(std::move(event));
}

void Etbase::EventBase::beginLoop()
{
    int cnt;
    while((cnt=evmap.countActive())){
        for(int i=0;i<cnt;++i){
            auto ev=evmap.getFront();
            if(ev==nullptr){
                
                continue;
            }
            pool.loadTask();
        }
        epoller.dispatch(&evmap);
    }
}