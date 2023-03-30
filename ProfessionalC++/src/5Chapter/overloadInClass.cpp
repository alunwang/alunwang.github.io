#include <iostream>
#include "overloadInClass.h"


int main(int argc, char** argv)
{
    Base bobj;
    Base* p;
    FirstD fobj;
    SecondD sobj;

    // 虚函数，随着指针指向不同的对象，匹配到不同的版本
    p = &bobj;  // 1
    p->who();   // 2
    p = &fobj;  // 3
    p->who();   // 4
    p = &sobj;  // 5
    p->who();   // 6
    
    fobj.who(); // 7
    sobj.who(); // 8

    return 0;
}