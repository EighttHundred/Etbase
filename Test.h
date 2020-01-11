//
// Created by eight on 1/11/20.
//

#ifndef ETBASE_TEST_H
#define ETBASE_TEST_H

class A{
    int val;
    int* ip;
public:
    A();
};
class Test {
    void test(int& a);
    void test2();
    int& test3(int b);
    int test4(int a);
    A& test5(int a);
    void test6(A& a);
};


#endif //ETBASE_TEST_H
