#include "../include/Buffer.h"
#include "tools.h"
using namespace Etbase;
int main(){
    Buffer buffer="hello";
    buffer+=" world";
    std::cout<<buffer<<std::endl;
}