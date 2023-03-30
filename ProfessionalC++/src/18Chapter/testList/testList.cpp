#include <array>
#include <list>
#include <forward_list>
#include <vector>
#include <deque>
#include <stack>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>
#include <exception>
#include <limits>   // numeric_limits
#include <cassert>   // assert()
#include <cstdlib>  // abort(), qsort()
#include <cstdio>   // snprintf()
#include <ctime>

using namespace std;

#define ASIZE   500000

namespace containerTest {
long get_a_target_long()
{
    long target {0};

    cout << "Target (0~" << RAND_MAX << "): ";
    cin >> target;
    return target;
}

string get_a_target_string()
{
    long target {0};
    char buf[10];

    cout << "target (0~" << RAND_MAX << "): ";
    cin >> target;
    snprintf(buf, 10, "%ld", target);
    return string(buf);
}

int compareLongs(const void* a, const void* b)
{
    return (*(long*)a - *(long*)b); // long*: convert void* to long*, *(long*): get its value
}

int compareStrings(const void* a, const void* b)
{
    if (*(char*)a < *(char*)b) return -1;
    else if (*(char*)a == *(char*)b) return 0;
    else return 1; //(*(char*)b > *(char*)b) return 1;
}

void test_array()
{
    cout << "\ntest_array().......... \n";

    array<long, ASIZE> c;
    clock_t timeStart = clock();
    for (long i {0}; i<ASIZE; ++i) {
        c[i] = rand();
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "array.size() = " << c.size() << endl;
    cout << "array.front() = " << c.front() << endl;
    cout << "array.back() = " << c.back() << endl;
    cout << "array.data() = " << c.data() << endl;

    timeStart = clock();
    qsort(c.data(), ASIZE, sizeof(long), compareLongs);
    cout << "qsort(), milli-seconds: " << (clock() - timeStart) << endl;

    long target {get_a_target_long()};
    // bsearch()?
}

void test_vector(const long& value)
{
    cout << "\ntest_vector().......... \n";

    vector<string> c;
    char buf[10];

    clock_t timeStart = clock();
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "vector.size() = " << c.size() << endl;
    cout << "vector.front() = " << c.front() << endl;
    cout << "vector.back() = " << c.back() << endl; // Calling front() or back() on an empty container causes undefined behavior.
    cout << "vector.data() = " << c.data() << endl;
    cout << "vector.capacity() = " << c.capacity() << endl;

    string target {get_a_target_string()};
    {
    timeStart = clock();
    auto pItem {::find(c.begin(), c.end(), target)}; // find() return an iterator
    cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != c.end()) {
        cout << "Found: " << *pItem << endl;
    } else {
        cout << "Not found!" << endl;
    }
    }
    {
    timeStart = clock();
    sort(c.begin(), c.end());
    string* pItem {(string*)bsearch(&target, c.data(), c.size(), sizeof(string), compareStrings)};
    cout << "sort()+bsearch(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != NULL) {
        cout << "Found: " << *pItem << endl;
    } else {
        cout << "Not found!";
    }
    }
}

void test_vector1()
{
    vector<double> doubleVector;
    double max {-numeric_limits<double>::infinity()};

    for (size_t i {1}; true; i++) {
        double temp;
        // cout << format("Enter score {}:", i+1);
        cout << "Enter score " << i << " (-1 to stop):";
        cin >> temp;
        if (temp == -1) {
            break;
        }
        try {
            doubleVector.push_back(temp); // It takes care of allocating space for the new element. 
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
        if (temp > max) {
            max = temp;
        }
    }

    max /= 100.0;
    for (auto& elem : doubleVector) { // Use "auto&"" instead of "auto" so that the actual elements can be modified
        elem /= max;
        cout << elem << " ";
    }
    cout << "\n";
}

void test_vector_constructor()
{
    {
    vector<int> intVector;  // Default constructor creates a vector with 0 element (empty).
    assert(intVector.size() == 0);
    }
    {
    vector<int> intVector(10, 100); // Create vector of 10 ints with value 100
    for (size_t i {0}; i<intVector.size(); i++) {
        assert(intVector[i] == 100);
    }
    }
    {
    vector intVector {1, 2, 3, 4, 5, 6}; // Create vector of 6 ints with value 1~6
    size_t i {1};
    for (auto iter {cbegin(intVector)}; iter != cend(intVector); ++iter, ++i) {
        assert(*iter == i);
    }
    }
    {
    vector<string> stringVector(10, "hello");
    for (auto elem : stringVector) {
        assert(elem == "hello");
    }
    }
    {

    }

}

/*
 * list:
 *    ----    ----    ----
 * <-|    |<-|    |<-|    |<-
 * ->|    |->|    |->|    |->
 *    ----    ----    ----
 */
void test_list(const long& value)
{
    cout << "\ntest_list().......... \n";

    list<string> c;
    char buf[10];

    clock_t timeStart {clock()};
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "list.size() = " << c.size() << endl;
    cout << "list.max_size() = " << c.max_size() << endl;
    cout << "list.front() = " << c.front() << endl;
    cout << "list.back() = " << c.back() << endl;

    string target {get_a_target_string()};
    timeStart = clock();
    auto pItem = ::find(c.begin(), c.end(), target);
    cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != c.end()) {
        cout << "Found, " << *pItem << endl;
    } else {
        cout << "Not found!" << endl;
    }

    timeStart = clock();
    c.sort();
    cout << "c.sort(), milli-seconds: " << (clock() - timeStart) << endl;
}

/*
 * forward_list:
 * |   --    --    --    --
 * |->|  |->|  |->|  |->|  |->
 * |   --    --    --    --
 */
void test_forward_list(long& value)
{
    cout << "\ntest_forward_list().......... \n";
    forward_list<string> c;
    char buf[10];

    clock_t timeStart {clock()};
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_front(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "forward_list.max_size() = " << c.max_size() << endl;
    cout << "forward_list.front() = " << c.front() << endl;

    string target {get_a_target_string()};
    timeStart = clock();
    auto pItem {::find(c.begin(), c.end(), target)};
    cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != c.end()) {
        cout << "Found, " << *pItem << endl;
    } else {
        cout << "Not found!" << endl;
    }

    timeStart = clock();
    c.sort();
    cout << "forward_list.sort(), milli-seconds: " << (clock() - timeStart) << endl;
}

/*
 * Deque
 */
void test_deque(long& value)
{
    cout << "\ntest_deque().......... \n";
    deque<string> c;
    char buf[10];

    clock_t timeStart {clock()};
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push_back(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "deque.size() = " << c.size() << endl;
    cout << "deque.max_size() = " << c.max_size() << endl;
    cout << "deque.front() = " << c.front() << endl;
    cout << "deque.back() = " << c.back() << endl;

    string target {get_a_target_string()};
    timeStart = clock();
    auto pItem = ::find(c.begin(), c.end(), target);
    cout << "::find(), milli-seconds: " << (clock() - timeStart) << endl;
    if (pItem != c.end()) {
        cout << "Found, " << *pItem << endl;
    } else {
        cout << "Not found!" << endl;
    }

    timeStart = clock();
    sort(c.begin(), c.end());
    cout << "::sort(), milli-seconds: " << (clock() - timeStart) << endl;
}

/*
 * stack - it is actually a deque, but only allows push/pop from one end.
 */
void test_stack(long& value)
{
    cout << "\ntest_stack().......... \n";
    stack<string> c;
    char buf[10];

    clock_t timeStart {clock()};
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "stack.size() = " << c.size() << endl;
    cout << "stack.top() = " << c.top() << endl;
    c.pop();
    cout << "stack.size() = " << c.size() << endl;
    cout << "stack.top() = " << c.top() << endl;
}

/*
 * queue - it is actually a deque, but only allows push to one end, and pop from the other end
 */
void test_queue(long& value)
{
    cout << "\ntest_queue().......... \n";
    queue<string> c;
    char buf[10];

    clock_t timeStart {clock()};
    for (long i {0}; i<value; ++i) {
        try {
            snprintf(buf, 10, "%d", rand());
            c.push(string(buf));
        } catch (const exception& e) {
            cout << "i = " << i << ": " << e.what() << endl;
            abort();
        }
    }
    cout << "milli-seconds: " << (clock() - timeStart) << endl;
    cout << "queue.size() = " << c.size() << endl;
    cout << "queue.front() = " << c.front() << endl;
    cout << "queue.back() = " << c.back() << endl;
    c.pop();
    cout << "queue.front() = " << c.front() << endl;
    cout << "queue.back() = " << c.back() << endl;
}


/*
 * string
 * C++的string和C语言的char *区别：
 * string是一个类，char *是指向字符的指针
 * string封装了char *,管理这个字符串，是一个char *类型的容器
 * string不用考虑内存释放和数组越界
 * string提供了一些列的字符串操作函数
 */


/*
 * 字符串的遍历
 */
void test_string_traverse(const string& s)
{
     // 1. 数组方式遍历，通过[]操作符 （不会抛出异常）
    cout << "Traverse the string with []: ";
    for (int i {0}; i<s.length(); ++i) {
        cout << s[i];
    }
    cout << "\n";

    // 2. at()方法遍历，根据index取值 (会抛出异常)
    cout << "Traverse the string with at(): ";
    for (int i {0}; i<s.length(); ++i) {
        try {
            cout << s.at(i);
        } catch (const exception& e) {
            cout << "At i = " << i << ", cause:  " << e.what() << endl;
            abort();
        }
    }
    cout << "\n";

    // 3. 通过迭代器遍历
    cout << "Traverse string with iterator: ";
    for (auto iter {cbegin(s)}; iter != cend(s); ++iter) {
        cout << *iter;
    }
    cout << '\n';
}

void test_string_cancatenation()
{
    string s1 {"0123456789"};
    string s2 {"abcdefghij"};

    string s3 = s1 + s2;    // 1. Use overloading of "+"
    cout << "s3 = " << s3 << '\n';

    string s4 = s1.append(s2); // 2. Use member function append()
    cout << "s4 = " << s4 << '\n';

}

bool test_string_find(const string& s, const string& sub)
{

    return false;
}
void test_string()
{
    cout << "test_string().......... \n";

    string str {"abcdererdfdf.kjdkfdofuidfkj3434-9-edfdfhjljljdfdzjkn dfdueroeu"};
    test_string_traverse(str);
    test_string_cancatenation();
}

}


int main()
{
    int choice;
    cout << "Test case list: \n";
    cout << "0. test_string()\n";
    cout << "1. test_vector()\n";
    cout << "2. test_list()\n";
    cout << "Input your choice to do: ";
    cin >> choice;
    switch (choice) {
    case 0:
        containerTest::test_string();
        break;
    case 1:
        containerTest::test_vector(1000000);
        containerTest::test_vector1();
        containerTest::test_vector_constructor();
        break;
    case 2:
        containerTest::test_list(1000000);
        break;
    default:
        break;
    }

    return 0;
}