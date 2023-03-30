/*
 * It allows for easy iteration over elements of a container. This type of loop works for
 * 1. C-style arrays, 
 * 2. initializer lists, 
 * 3. and any type that has begin() and end() methods returning iterators, such as std::array, vector, 
 *    and all other Standard Library containers
 */
#include<iostream>
#include<array>
#include<initializer_list>  // std::initializer_list


int makeSum(std::initializer_list<int> values)
{
    int sum {0};
    for (int v : values) {
        sum += v;
    }
    return sum;
}


int main(int argc, char* argv[])
{
    // C-stype array
    int arr1[] = {9, 8, 7, 6};
    std::cout << "arr1: ";
    for (int v : arr1) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // std::array
    std::array arr2 {1.0, 2.0, 3.0, 4.0};
    std::cout << "arr2: ";
    for (int v : arr2) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Initializer, introduced in C++20
    // for (<initializer>; <for-range-declaration> : <for-range-initializer>) { <body> }
    std::cout << "Initializer: ";
    for (std::array arr3 {1, 2, 3, 4}; int v : arr1) {
        std::cout << v << " ";
    }
    std::cout << "\n";

    // Initializer Lists
    int a {makeSum({1,2,3,4,5,6,7,8,9})};
    std::cout << "a = " << a << "\n";
    int b {makeSum({10, 20, 30, 40, 50})};
    std::cout << "b = " << b << "\n";

    return 0;
}