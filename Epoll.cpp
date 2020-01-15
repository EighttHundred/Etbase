//
// Created by eight on 1/15/20.
//

#include <unistd.h>
#include <cstdlib>
#include "Epoll.h"

void Etbase::Epoll::accpet() {

}

Etbase::Epoll::Epoll():fd(epoll_create(0)) {
}

Etbase::Epoll::~Epoll() {
    close(fd);
}


int Etbase::Epoll::wait(EventMap *emap) {
    int n = epoll_wait(fd, events, 64, -1);
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

int Etbase::Epoll::add(int fd) {
    epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;
    if (epoll_ctl(efd, EPOLL_CTL_ADD, fd, &event) == -1){
        //LogWriter::writeError("add event failed");
        return -1;
    }
    return 1;
}
