//
// Created by eight on 2/29/20.
//

#ifndef ETBASE_Buffer_H
#define ETBASE_Buffer_H

#include "Mutex.h"
#include <map>
#include <iostream>
#include <memory>
namespace Etbase{

    class Buffer {
//        const long maxsize=4e3+5;
        int singleRead=0;
        int singleWrite=0;
        char* head= nullptr;
        char* tail= nullptr;
        char* bottom= nullptr;
        Mutex mutex;
        void init();
        void reallocate(long size);
    public:
        Buffer();
        Buffer(const char* data);
        ~Buffer();
        char* begin()const;
        char* end()const;
        long size()const;
        char operator[](int pos);
        void push_back(const char* data,long size);
        Buffer& operator=(const Buffer& data);
        Buffer& operator=(const char*data);
        Buffer& operator+=(const char* data);
        Buffer& operator+=(const Buffer& data);
        friend std::ostream&operator<<(std::ostream& out,const Buffer& buff);
        friend std::istream&operator>>(std::istream& in,Buffer& buff);
        void append(long len);
        void clear();
        long spare();
        void print();
        Mutex& getMutex();
    };
    typedef std::shared_ptr<Buffer> BufferPtr;
    typedef std::map<int,BufferPtr> BufferMap;
}


#endif //ETBASE_Buffer_H
