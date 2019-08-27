#ifndef ETBASE_EPOLLER_H
#define ETBASE_EPOLLER_H

#include <sys/epoll.h>
#include "../base/threadpool.h"
#include "./socket.h"
#include "../base/log.h"

#define MAXEVENTS 64

namespace Etbase
{
    class Epoller {
    public:
        Epoller()
        {
            epollCreate();
        }
        ~Epoller()
        {
            Close(efd);
        }
        void epollCreate()
        {
            int tfd=epoll_create1(0);
            if(tfd==-1){
                LogWriter::writeError("epoll create failed");
                return;
            }
            efd=tfd;
            events=(epoll_event*)calloc(MAXEVENTS,sizeof(epoll_event));
        }
        int epollWait()
        {
            return epoll_wait(efd,events,MAXEVENTS,-1);
        }
        void addEvent(int fd)
        {
            epoll_event event;
            event.data.fd=fd;
            event.events=EPOLLIN|EPOLLET;
            if(epoll_ctl(efd,EPOLL_CTL_ADD,fd,&event)==-1){
                LogWriter::writeError("add event failed");
                return;
            }
        }
        void loop()
        {
            while(1)
            {
                int n=epollWait();
                for(int i=0;i<n;++i){
                    int fd=events[i].data.fd;
                    if ((events[i].events & EPOLLERR) ||
                    (events[i].events & EPOLLHUP) ||
                    (!(events[i].events & EPOLLIN))){
                        Close(fd);
                    }
                    else if(sfd==fd){
                        Socket socket;
                    }
                }
            }
        }
        void Close(int fd)
        {
            close(fd);
        }
    private:
        int efd;
        int sfd;
        epoll_event* events;
        ThreadPool threadPool;
    };
}
#endif //ETBASE_EPOLLER_H
