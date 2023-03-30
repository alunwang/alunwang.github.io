/*
 * 传统C++会把NULL、0视为同一种东西，这取决于编译器如何定义NULL，有些编译器会将NULL定义为
 * #define NULL ((void*)0)
 * 有些则会直接将其定义为
 * #define NULL 0
 * 后一种定义就会让调用foo(NULL)在选择下面的两C++重载函数产生混乱：
 * void foo(int);
 * void foo(char*);
 * 
 * C++11引入了nullptr关键字，专门用来区分空指针、0。而nullptr的类型为nullptr_t，
 * 能够隐式的转换为任何指针或成员指针的类型，也能和他们进行相等或者不等的比较。
 */
#include<iostream>
#include<type_traits>


void foo(int i)
{
    std::cout << "foo(int) is called" << "\n";
}

void foo(char* str)
{
    std::cout << "foo(char*) is called" << "\n";
}

int main(void)
{
    if (std::is_same<decltype(NULL), decltype(0)>::value)   // NULL != 0
        std::cout << "NULL == 0" << "\n";
    if (std::is_same<decltype(NULL), decltype((void*)0)>::value)    // NULL != (void*)0
        std::cout << "NULL == (void*)0" << "\n";
    if (std::is_same<decltype(NULL), std::nullptr_t>::value)    // NULL != nullptr
        std::cout << "NULL == nullptr" << "\n";
    
    int a = 0;
    foo(a);     // Call foo(int)
    // char *s = NULL;  // Don't use NULL again
    // foo(NULL);       // Compiling error
    char *s = nullptr;  // Always use this in C++
    foo(s);       // Call foo(char*)
    
    return 0;
}