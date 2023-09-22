#include <string>
#include <string_view>
#include <chrono>
#include <iostream>
#include <format>


std::string_view extractExtension(std::string_view fname) // string_view通常按值传递，因为它们的复制成本非常低。
{
    return fname.substr(fname.rfind('.'));
}

void stringView()
{
    std::string fname {R"(./stringView.cpp)"};
    std::cout << std::format("C++ string: {}\n", extractExtension(fname));

    const char* cStr {R"(./stringView.cpp)"};
    std::cout << std::format("C string: {}\n", extractExtension(cStr));

    std::cout << std::format("String literal: {}\n", extractExtension(R"(./stringView.cpp)"));
}

class Timer {
    private:
        std::string m_title;
        std::chrono::high_resolution_clock::time_point m_start, m_stop;
    public:
        Timer(const std::string& title) : m_title{title}
        { // 构造时记录开始时间
            m_start = std::chrono::high_resolution_clock::now();
        }
        ~Timer()
        {
            stop();
        }
        void stop()
        { // 析构时再记录结束时间，计算并打印耗时
            m_stop = std::chrono::high_resolution_clock::now();
            std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(m_stop - m_start);
            std::cout << std::format("{} {}s\n", m_title, (ms.count()) * 0.001);
        }
};

// const string&传递在下面三者情况：
// 字符串字面值、字符数组、字符串指针的传递依然要数据拷贝
// 这三类低级数据类型与string类型不同，传入时编译器要做隐式转换，即需要拷贝这些数据生成string临时对象。const string&指向的实际上是这个临时对象。
// 通常字符串字面值较小，性能损失可忽略不计；但字符串指针和字符数组某些情况下可能会比较大（比如读取文件的内容），此时会引起频繁的内存分配和数据拷贝，影响程序性能。
void functionWithString(const std::string& str)
{
}

void functionWithString(const std::string_view strView)
{
}

int main()
{
    {
    Timer timer {"std::string"};
    for (int i {0}; i<10000000; ++i) {
        std::string name {"Lunsheng Wang"};
        std::string fname {name.substr(1, 8)};
        std::string lname {name.substr(9, 4)};
        functionWithString(fname);
        functionWithString(lname);
    }
    }
    {
    Timer timer {"std::string_view"};
    for (int i {0}; i<10000000; ++i) {
        const char* name {"Lunsheng Wang"};
        std::string_view fname {std::string_view(name, 8)};
        std::string_view lname {std::string_view(name+8, 4)};
        functionWithString(fname);
        functionWithString(lname);
    }
    }
}