#include <bit>
#include <bitset>
#include <cstdint>
#include <iostream>


int main()
{
    for (const std::uint8_t i : {0, 0b11111111, 0b00011101}) {
        // popcount: 多少个比特位1
        std::cout << "popcount(" << std::bitset<8>(i) << ") = " << std::popcount(i) << '\n';
        // has_single_bit: 是否只有一个比特位为1，换句话说，是否为2的次幂。
        std::cout << "has_single_bit(" << std::bitset<8>(i) << ") = " << std::has_single_bit(i) << '\n';
        // countl_zero: 左端点开始连续0个数。
        std::cout << "countl_zero(" << std::bitset<8>(i) << ") = " << std::countl_zero(i) << '\n';
        // countl_one: 左端点开始连续1个数。
        std:: cout << "countl_one(" << std::bitset<8>(i) << ") = " << std::countl_one(i) << '\n';
        std::cout << "countr_zero(" << std::bitset<8>(i) << ") = " << std::countr_zero(i) << '\n';
        std::cout << "countr_one(" << std::bitset<8>(i) << ") = " << std::countr_one(i) << '\n';
        std::cout << std::endl;
    }
    
    return 0;
}