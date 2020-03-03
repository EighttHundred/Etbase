//
// Created by eight on 2/29/20.
//

#ifndef ETBASE_STRING_H
#define ETBASE_STRING_H

#include <iostream>
namespace Etbase{

    class String {
//        const long maxsize=4e3+5;
        char* head= nullptr;
        char* tail= nullptr;
        char* bottom= nullptr;
        void reallocate(long size);
        void init();
    public:
        String();
        String(const char* data);
        ~String();
        char* begin()const;
        char* end()const;
        long size()const;
        char operator[](int pos);
        void push_back(const char* data,long size);
        String&operator=(const String& data);
        String& operator=(const char*data);
        String& operator+=(const char* data);
        String& operator+=(const String& data);
        friend std::ostream&operator<<(std::ostream& out,const String& buff);
        friend std::istream&operator>>(std::istream& in,String& buff);
        void append(long len);
        void clear();
        long spare();
    };

}


#endif //ETBASE_STRING_H
