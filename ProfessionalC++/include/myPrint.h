#ifndef __MYPRINT_H__
#define __MYPRINT_H__

#include<iostream>
#include<string>

void printRange(std::string_view message, auto& range)
{
    std::cout << message;
    for (const auto& value : range) {
        std::cout << value << " ";
    }
    std::cout << std::endl;
}

#endif  //__MYPRINT_H__