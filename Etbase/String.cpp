//
// Created by eight on 2/29/20.
//

#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../include/String.h"
#include "../include/Util.h"
using namespace Etbase;

char *String::begin()const {
    return head;
}

char *String::end()const {
    return tail;
}

long String::size() const{
    return tail-head;
}

String::String() {
    init();
}

char String::operator[](int pos) {
    return head[pos];
}

String &String::operator+=(const char *data) {
    long size=strlen(data);
    push_back(data,size);
    return *this;
}

void String::push_back(const char *data, long size) {
    if(bottom-tail<size) reallocate(tail-head+size);
    memcpy(tail,data,size);
    tail+=size;
}

template <typename T>
T max(T A,T B){
    return A>B?A:B;
}

void String::reallocate(long size) {
    auto oldhead=head;
    long newsize=max(size,(bottom-head)*2)+10;
    head=new char[newsize]();
    memcpy(head,oldhead,tail-oldhead);
    tail=head+(tail-oldhead);
    bottom=head+newsize;
    delete [] oldhead;
}

String::~String() {
    delete []head;
}

String &String::operator+=(const String &data) {
    push_back(data.begin(),data.size());
    return *this;
}

void String::clear() {
    tail=head;
    whead=head;
}

void String::append(long len) {
    tail+=len;
    if(bottom<tail+10) reallocate(0);
}

long String::spare() {
    return bottom-tail;
}

String::String(const char *data) {
    init();
    push_back(data,strlen(data));
}

namespace Etbase{

    std::ostream &operator<<(std::ostream &out, const String &buff) {

        for(auto ip=buff.head;ip!=buff.tail;++ip)
            out<<*ip;
        return out;
    }

    std::istream &operator>>(std::istream &in, String &buff) {
        //not yet implement
        in>>buff.head;
        buff.tail=buff.head+strlen(buff.head);
        return in;
    }

    String& String::operator=(const char *data) {
        init();
        whead=tail=head;
        push_back(data,strlen(data));
        return *this;
    }

    String &String::operator=(const String &data) {
        init();
        whead=tail=head;
        if(&data!=this)
            push_back(data.begin(),data.size());
        return *this;
    }

    void String::init() {
        if(head== nullptr){
            head=new char[100]();
            whead=tail=head;
            bottom=head+100;
        }
    }

    char *String::writeBegin() const {
        return whead;
    }

    long String::restToWrite() const {
        return tail-whead;
    }

    int String::read(int fd) {
        int ret;
        singleRead=0;
        while((ret=::read(fd,tail,spare()))>0){
            append(ret);
            singleRead+=ret;
        }
        return ret;
    }

    int String::write(int fd) {
        int ret;
        singleWrite=0;
        while((ret=::write(fd,whead,restToWrite()))>0){
            writeAppend(ret);
            singleWrite+=ret;
        }
        return ret;
    }

    void String::writeAppend(long len) {
        whead+=len;
        if(whead==tail){
            whead=tail=head;
        }
    }

    int String::getReadSize() {
        return singleRead;
    }

    int String::getWriteSize() {
        return singleWrite;
    }

}


