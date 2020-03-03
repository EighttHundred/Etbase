//
// Created by eight on 2/29/20.
//

#ifndef ETBASE_STRING_H
#define ETBASE_STRING_H

#include <iostream>
namespace Etbase{

    class String {
//        const long maxsize=4e3+5;
        int singleRead=0;
        int singleWrite=0;
        char* head= nullptr;
        char* tail= nullptr;
        char* bottom= nullptr;
        char* whead=nullptr;
        void reallocate(long size);
        void init();
    public:
        String();
        String(const char* data);
        ~String();
        char* begin()const;
        char* writeBegin() const;
        char* end()const;
        long size()const;
        long writeSize() const;
        char operator[](int pos);
        void push_back(const char* data,long size);
        String&operator=(const String& data);
        String& operator=(const char*data);
        String& operator+=(const char* data);
        String& operator+=(const String& data);
        friend std::ostream&operator<<(std::ostream& out,const String& buff);
        friend std::istream&operator>>(std::istream& in,String& buff);
        void append(long len);
        void writeAppend(long len);
        void clear();
        long spare();
        int read(int fd);
        int write(int fd);
        int getReadSize();
        int getWriteSize();
    };

}


#endif //ETBASE_STRING_H
