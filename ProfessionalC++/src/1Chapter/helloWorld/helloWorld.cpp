// helloWorld.cpp
#include <iostream>
#include <compare>
// import <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Hello world!" << std::endl;

    int a {11};
    std::strong_ordering res { a <=> 0};
    if (res == std::strong_ordering::less) {
        std::cout << "less\n";
    }
    if (res == std::strong_ordering::greater) {
        std::cout << "greater\n";
    }
    if (res == std::strong_ordering::equal) {
        std::cout << "equal\n";
    }
    return 0;
}