#include "./thread.h"

void Etbase::Thread::start() {
    assert(!started);
    assert(runTask!=nullptr);
    started=true;
    if(pthread_create(&tid,nullptr,callRun,this)){

    }
}

void Etbase::Thread::shutdown() {
    if(started){
        ZEROCHECK(pthread_detach(tid));
        started=false;
    }
}

void Etbase::Thread::join() {
    if(started){
        ZEROCHECK(pthread_join(tid,nullptr));
        started=false;
    }
}
