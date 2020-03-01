//
// Created by eight on 1/7/20.
//

#include "Util.h"

namespace Etbase{
    int strToInt(const char *str) {
        int res=0;
        if(str!= nullptr){
            for(int i=0;str[i];++i){
                res*=10;
                res+=str[i]-'0';
            }
        }
        return res;
    }

    char* intToStr(int x) {
        char* str= nullptr;
        if(x>=0){
            str=new char[10];
            for(int i=0;x;++i){
                str[i]=(char)(x%10+'0');
                x/=10;
            }
        }
        return str;
    }
}


