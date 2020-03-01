//
// Created by eight on 2/29/20.
//

#include <string.h>
#include "String.h"
#include "Util.h"
char *Etbase::String::begin()const {
    return head;
}

char *Etbase::String::end()const {
    return tail;
}

long Etbase::String::size() const{
    return tail-head;
}

Etbase::String::String() {
    init();
}

char Etbase::String::operator[](int pos) {
    return head[pos];
}

Etbase::String &Etbase::String::operator+=(const char *data) {
    long size=strlen(data);
    push_back(data,size);
    return *this;
}

void Etbase::String::push_back(const char *data, long size) {
    if(bottom-tail<size) reallocate(tail-head+size);
    memcpy(tail,data,size);
    tail+=size;
}

template <typename T>
T max(T A,T B){
    return A>B?A:B;
}

void Etbase::String::reallocate(long size) {
    auto oldhead=head;
    long newsize=max(size,(bottom-head)*2)+10;
    head=new char[newsize]();
    memcpy(head,oldhead,tail-oldhead);
    tail=head+(tail-oldhead);
    bottom=head+newsize;
    delete [] oldhead;
}

Etbase::String::~String() {
    delete []head;
}

Etbase::String &Etbase::String::operator+=(const Etbase::String &data) {
    push_back(data.begin(),data.size());
    return *this;
}

void Etbase::String::clear() {
    tail=head;
}

void Etbase::String::append(long len) {
    tail+=len;
    if(bottom<tail+10) reallocate(0);
}

long Etbase::String::spare() {
    return bottom-tail;
}

Etbase::String::String(const char *data) {
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
        tail=head;
        push_back(data,strlen(data));
        return *this;
    }

    String &String::operator=(const String &data) {
        init();
        tail=head;
        if(&data!=this)
            push_back(data.begin(),data.size());
        return *this;
    }

    void String::init() {
        if(head== nullptr){
            head=new char[100]();
            tail=head;
            bottom=head+100;
        }
    }

}


