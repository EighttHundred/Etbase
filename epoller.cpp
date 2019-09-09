#include "epoller.h"

Etbase::Epoller::Epoller()
{
    int fd = epoll_create1(0);
    if (fd == -1){
        //LogWriter::writeError("epoll create failed");
        return;
    }
    efd = fd;
    events = (epoll_event *)calloc(MAXEVENTS, sizeof(epoll_event));
}

Etbase::Epoller::~Epoller()
{
    close(efd);
}

int Etbase::Epoller::dispatch(EventMap* emap)
{
    int n = epoll_wait(efd, events, MAXEVENTS, -1);
    for (int i = 0; i < n; ++i){
        int fd = events[i].data.fd;
        if ((events[i].events & EPOLLERR) ||
            (events[i].events & EPOLLHUP) ||
            (!(events[i].events & EPOLLIN))){
            close(fd);
        }
        else{
            emap->addQueue(fd);
        }
    }
}

int Etbase::Epoller::addEvent(int fd)
{
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event) == -1){
        //LogWriter::writeError("add event failed");
        return -1;
    }
    return 1;
}