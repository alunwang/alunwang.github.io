#include <iostream>
#include <cstring>
#include <cassert>
#define FMT_HEADER_ONLY
#include <fmt/format.h>


void stringLiterals()
{
    std::cout << "String literal: This is a string literal, stored in read-only memory sector." << std::endl;

    {
    char* res {"abcdefg"}; // string literals实际放置在read-only内存区，在此定指针指向该处，让后面能修改打开可后门
    res[1] = '1'; // 未定义，根据编译器实现
    }
    {
    const char* res {"abcdefg"}; // 用const修饰指针指向的为constant，保护其免致以外修改
    res[1] = '1'; // 因是const char*，所有编译器都会报错
    }
    {
    char res[] {"abcdefg"}; // 以string literals作初值初始化一个字符array，实质是拷贝string literals到其中，不再是同一份
    res[1] = '1'; // 这样就可以改变
    }
}

void stringUsage()
{
    {
    const char* a {"12"};
    char b[] {"12"};
    // assert(a!=b);
    if (a == b) { // False，因为比较的是指针，非其中的内容
        //
    }
    // assert(strcmp(a, b) == 0);
    if (strcmp(a, b) == 0) { // True，比较的是其中的内容
        //
    }
    }
    {
    const char* str1 {"1234"};
    const char* str2 {"5678"};
    const char* str3 {"910"};
    std::cout << fmt::v9::format("str1 = {}, str2 = {}, str3 = {}\n", str1, str2, str3);
    const char* str {new char[strlen(str1) + strlen(str2) + strlen(str3) + 1]}; // stren()返回不包括“\0”，必须加1，以容纳“\0”
    strcpy(str, str1);
    strcat(str, str2);
    strcat(str, str3);
    std::cout << fmt::v9::format("str = {} + {} + {} = {}\n", str1, str2, str3, str);
    }
}