//
// Created by eight on 2/29/20.
//

#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/in.h>
#include "../include/Buffer.h"
#include "../include/Util.h"
using namespace Etbase;

char *Buffer::begin()const {
    return head;
}

char *Buffer::end()const {
    return tail;
}

long Buffer::size() const{
    return tail-head;
}

Buffer::Buffer() {
    init();
}

char Buffer::operator[](int pos) {
    return head[pos];
}

Buffer &Buffer::operator+=(const char *data) {
    long size=strlen(data);
    push_back(data,size);
    return *this;
}

void Buffer::push_back(const char *data, long size) {
    if(bottom-tail<size) reallocate(tail-head+size);
    memcpy(tail,data,size);
    tail+=size;
}

template <typename T>
T max(T A,T B){
    return A>B?A:B;
}

void Buffer::reallocate(long size) {
    auto oldhead=head;
    long newsize=max(size,(bottom-head)*2)+10;
    head=new char[newsize]();
    memcpy(head,oldhead,tail-oldhead);
    tail=head+(tail-oldhead);
    bottom=head+newsize;
    delete [] oldhead;
}

Buffer::~Buffer() {
    delete []head;
}

Buffer &Buffer::operator+=(const Buffer &data) {
    push_back(data.begin(),data.size());
    return *this;
}

void Buffer::clear() {
    tail=head;
}

void Buffer::append(long len) {
    tail+=len;
    if(bottom<tail+10) reallocate(0);
}

long Buffer::spare() {
    return bottom-tail;
}

Buffer::Buffer(const char *data) {
    init();
    push_back(data,strlen(data));
}

namespace Etbase{

    std::ostream &operator<<(std::ostream &out, const Buffer &buff) {
        for(auto ip=buff.head;ip!=buff.tail;++ip)
            out<<*ip;
        return out;
    }

    std::istream &operator>>(std::istream &in, Buffer &buff) {
        //not yet implement
        in>>buff.head;
        buff.tail=buff.head+strlen(buff.head);
        return in;
    }

    Buffer& Buffer::operator=(const char *data) {
        init();
        tail=head;
        push_back(data,strlen(data));
        return *this;
    }

    Buffer &Buffer::operator=(const Buffer &data) {
        init();
        tail=head;
        if(&data!=this)
            push_back(data.begin(),data.size());
        return *this;
    }

    void Buffer::init() {
        if(head== nullptr){
            head=new char[100]();
            bottom=head+100;
        }
    }

}


