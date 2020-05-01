#ifndef TOOLS_H
#define TOOLS_H
#include <stdarg.h>
#define END -1
#define pass(...) return_test(__VA_ARGS__,END) 
bool return_test(int first,...){
    va_list ap;
    va_start(ap,first);
    int ans=first;
    int ret;
    while((ret=va_arg(ap,int))!=END){
        ans*=ret;
    }
    va_end(ap);
    return !ans;
}
template<typename T>
bool judgeEqual(T a,T b){
    return a==b;
}
#endif