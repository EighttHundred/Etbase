//
// Created by eight on 1/11/20.
//

#include "Test.h"

void Test::test(int &a) {
    int b=5;
    a=b;
}

void Test::test2() {
    auto ip=new int(5);
    test(*ip);
}

int &Test::test3(int b) {
    auto a = new int();
    if (b) return *a;
}

int Test::test4(int a) {
    if(a) return 0;
}

A &Test::test5(int a) {

}

void Test::test6(A &a) {
    A b=A();
    a=b;
}

A::A() {

}
