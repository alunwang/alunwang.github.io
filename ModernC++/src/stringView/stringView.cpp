#include<iostream>
#include<string>
#include<string_view>
#include<chrono>

using namespace std;

class TimerWrapper {
public:
    TimerWrapper(const string& str_type): str_type_(str_type)
    {
        start_time_ = chrono::high_resolution_clock::now();
    }
    ~TimerWrapper()
    {
        timeCost();
    }
    void timeCost()
    {
        auto ms = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - start_time_);
        // cout << str_type_ << ", costtime: " << ms << endl; // With compilation error
    }
private:
    string str_type_;
    chrono::high_resolution_clock::time_point start_time_;
};

void testString(const string& str)
{
    cout << "string: " << str << "\n";
    for (auto i=0; i<1000000; i++) {
        string sub_str = str.substr(5, 10);
    }
}

void testStringView(const string_view& str)
{
    cout << "string_view: " << str << "\n";
    for (auto i=0; i<1000000; i++) {
        string_view sub_str = str.substr(5, 10);
    }
}

string_view printStringView()
{
    string s {"How are you ..."};
    string_view sv { s };
    return sv;
}

int main(int argc, char* argv[])
{
    string str {"abcdefghijklmnopqrtstuvwxyz"};

    {
        TimerWrapper timer_wrapper("string");
        testString(str);
    }

    {
        TimerWrapper timer_wrapper("stringview");
        string_view str_view {str};
        testStringView(str_view);
    }

    string_view str_view_str = "testing string_view related..";
    string_view str_view_sub_str = str_view_str.substr(5, 10);
    cout << "str_view_sub_str: " << str_view_sub_str << "size: " << str_view_sub_str.size() << endl;
    cout << "str_view_str: " << str_view_str.data() << "size: " << str_view_str.size() << endl;

    // string strview2strerr = str_view_str;  //报错，不能直接转换

    string strview2str = static_cast<string>(str_view_str);
    cout << "strview2str: " << strview2str << endl;

    cout << "PrintLocalStringView: " << printStringView() << endl;
    return 0;
}