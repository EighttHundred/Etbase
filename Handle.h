//
// Created by eight on 1/15/20.
//

#ifndef ETBASE_HANDLE_H
#define ETBASE_HANDLE_H

namespace Etbase{
    class Handle {
    public:
        Handle(int fd_,int type_,int priority_);
    public:
        const int fd;
        int type;
        int priority;
    };
}



#endif //ETBASE_HANDLE_H
