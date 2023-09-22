#include <iostream>
#include <format>

using namespace std;

void stringCompare()
{
    string a {"Hello world!"};
    string b {"Hello world."};
    {
    auto res {a.compare(b)}; // 与C的strcmp()类似，不直观，易忘记类型，不推荐用
    if (res < 0) {
        cout << "a < b\n";
    } else if (res > 0) {
        cout << "a > b\n";
    } else {
        cout << "a == b\n";
    }
    }
    if (a > b) {    // 使用重载的操作符，非常直观和容易，推荐用
        cout << "a > b\n";
    } else if (a < b) {
        cout << "a < b\n";
    } else {
        cout << "a == b\n";
    }
    {
    auto res {a <=> b}; // 使用C++20引入的三向比较：<=>
    if (is_lt(res)) {
        cout << "a < b\n";
    } else if (is_gt(res)) {
        cout << "a > b\n";
    } else { // if (is_eq(res)) {
        cout << "a == b\n";
    }
    }
}

void stringConnect()
{
    string a {"123"};
    string b {"456"};
    cout << std::format("a+b = {}\n", a+b);
    a += a;
    cout << std::format("a = {}\n", a);
}

void stringFindAndReplace()
{
    string strHello {"Hello!!"};
    string strWorld {"The world..."};
    auto pos {strHello.find("!!")};
    if (pos != string::npos) {
        strHello.replace(pos, 2, strWorld.substr(3, 6));
    }
    cout << strHello << endl;
}

int main()
{
    const char* str {R"(Hello world)"};

    cout << str << endl;

    stringCompare();
    stringConnect();
    stringFindAndReplace();
    return 0;
}