#include <array>     // std::array
#include <vector>    // std::vector
#include <string>
#include <utility>   // std::pair
#include <optional>  // std::optional
#include <iostream>
#define FMT_HEADER_ONLY
#include <fmt/format.h> // fmt::v9::format


/*
 * A number of advantages to using std::arrays instead of C-style arrays:
 * 1. They always know their own size,
 * 2. are not automatically cast to a pointer to avoid certain types of bugs,
 * 3. and have iterators to easily loop over the elements.
 */
void arrayUsage(void)
{
    std::cout << "testing arrayUsage()...\n";
    std::array arr {9, 8, 7}; // std::array<int, 3> arr {9, 8, 7}; // Type and size can be automatically deduced.

    std::cout << "array[" << arr.size() << "] =\n";
    for (auto iter = arr.begin(); iter != arr.end(); ++iter) {
        std::cout << *iter << "\n";
    }
}

/*
 * Non-fixed size container
 * 1. a generic container, can hold almost any type of objects, use type to determine what type of object it holds,
 * 2. automatically allocates enough memory to hold its elements
 * 3. push_back() to add an element
 * 4. accessed with a similar syntax for array[]
 */
void vectorUsage(void)
{
    std::cout << "testing vectorUsage()...\n";
    std::vector vec {0.0};

    vec.push_back(10.0);
    vec.push_back(100.0);
    std::cout << "vector[" << vec.size() << "] = \n";
    for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
        std::cout << *iter << "\n";
    }
}

/*
 * 1. groups together two values of possibly different types
 * 2. data mebers accessed with pair.first/second
 */
void pairUsage(void)
{
    std::cout << "testing pairUsage()...\n";
    std::pair myPair {3.14, 5}; // std::pair<double, int> myPair {3.14, 5}
    
    std::cout << fmt::v9::format("(first, second) = ({}, {})\n", myPair.first, myPair.second);
}

/*
 * std::optional holds a value of specific type, or nothing.
 */
std::optional<int> getData(bool giveIt) // Used as return type so that function can return a value or none
{
    if (giveIt) {
        return 42;
    }
    return std::nullopt; // return {};
}

void optionalUsage(void)
{
    std::cout << "testing optionalUsage()...\n";
    std::optional opt1 {getData(true)};  // std::optional<int> opt {getData(true)};
    std::optional opt2 {getData(false)};

    // Use has_value() to determine if an optional has a value
    std::cout << "opt1.has_value = " << opt1.has_value() << "\n";
    if (opt2) { // Or can check an optional directly to see it if it has a value
        std::cout << "opt2.value = " << opt2.value() << "\n";   // If yes, use value() to retrieve its value
    } else {
        std::cout << "opt2.has_value = None\n";
    }
    try {
        auto value = opt2.value();  // If not check and it is empty, value() cause an exception
    } catch (const std::bad_optional_access& e) {
        std::cout << e.what() << "\n";
    }

    std::cout << "opt2.value = " << opt2.value_or(0) << "\n";    // Return opt2's value or 0
}

struct CircleStruct {
    int x, y;
    double radius;
};

class CircleClass {
    public:
        CircleClass(int x, int y, double radius) : m_x {x}, m_y {y}, m_radius {radius} {}
    private:
        int m_x, m_y;
        double m_radius;
};

void func(int i)
{
    std::cout << fmt::v9::format("i = {}\n", i);
}

// Uniform initialization
void uniformInitialization()
{
    std::cout << "testing uniformInitialization()...\n";
    // Prior to C++11
    // CircleStruct circle1 = {10, 10, 2.5}; // 没有构造函数，直接赋值
    // CircleClass circle2(10, 20, 2.5); // 用函数表示法调用构造函数
    // Since C++11
    CircleStruct circle1 {10, 10, 2.5};
    CircleClass circle2 {10, 20, 2.5}; // 用大括号也会自动调用构造函数

    int x = 3.14; // Truncated to 3 automatically
    func(3.14); // Truncated to 3 without message
    // int x {3.14}; // C++11, report error to prevent narrowing
    // func({3.14}); // C++11, report error

    // Can be used to initialize dynamically allocated arrays
    int* myArray = new int[] {0, 1, 2, 3, 4}; // 初始化动态分配的数组
}

void tryChangingConstParameter(const std::string* name)
{
    // *name = "Other name"; // Not compile because it is const.
    std::cout << *name << std::endl;
}

class People {
    public:
        People(std::string first, std::string last, int age)
        : m_firstName {std::move(first)}, m_lastName {std::move(last)}, m_age {age} {}
        std::string getName() const
        {
            return m_firstName + '.' + m_lastName;
        }
        int getAge() const // const修饰类成员函数：不能修改成员变量
        {
            return m_age;
        }
    private:
        std::string m_firstName, m_lastName;
        int m_age;
};

void constUsage()
{
    std::cout << "testing constUsage()...\n";
    const int versionNumberMajor {2};
    const int versionNumberMinor {1};
    // versionNumberMajor = 1; // It's a constant, cannot be changed

    int i {10}, a;
    {
    const int* pi {new int[i]}; // 修饰（int* pi），即pi指向的内容为constant。
    // int const* pi {new int[i]}; // 本质与上面一样
    // pi[4] = 5; // 指向内容为constant，不可改变
    pi = &a;
    }
    {
    int* const pi {new int[i]}; // 修饰（pi），即pi为constant
    pi[4] = 5;
    // pi = &a; // pi是constant，不能改变
    }
    std::string name {"Alan Wang"};
    tryChangingConstParameter(&name);

    People person {"Alan", "Wang", 25};
    std::cout << "Name: " << person.getName() << std::endl;
}

std::string getString()
{
    return "Hello, world!";
}

void tryChangingConstParam(const int& value)
{
    // value = 100; // 不能修改
    std::cout << "value = " << value << std::endl;
}

void swap(int& x, int& y)
{
    int temp {x};
    x = y;
    y = temp;
}

void referenceUsage()
{
    std::cout << "testing referenceUsage()...\n";
    {
    int x {3}, y {5};
    int& xRef {x}; // 类型之后加&，表明定义一个引用
    std::cout << "x = " << x << std::endl;
    std::cout << "xRef = " << xRef << std::endl;
    // int& ref; // Not compile，引用声明同时必须初始化为某一个已经存在的变量
    // xRef = &y; // Not compile，不能改变为另一个变量，而且&y是指针（地址）
    xRef = y; // 改变的是应用的地址中的内容，也即x的内容，不是让xRef成为y的应用
    std::cout << "x = " << x << std::endl;
    std::cout << "xRef = " << xRef << std::endl;
    }
    // Reference-to-const
    {
    // int& ref {5}; // Not compile，不能为未命名的值声明引用，必须是已经存在的变量
    const int& ref {5}; // 但可以为未命名的const值声明应用
    std::cout << "ref = " << ref << std::endl;
    // std::string& str {getString()}; // Not compile，不能为零时对象声明应用
    const std::string& str {getString()}; // 但可以为const临时对象声明应用
    std::cout << "str = " << str << std::endl;
    int x {3};
    const int& xRef {x}; // int const& xRef {x}; // 两者一样，修饰的都是引用地址的内容为constant（引用自己本身就是constant）
    std::cout << "xRef = " << xRef << std::endl;
    // xRef = 5; // Not compile，因有const限制，其内容不能改变
    // int& const xRef {x}; // Not compile， 不存在，引用本身就是constant
    tryChangingConstParam(x);
    }
    {
    int x {3};
    int& xRef {x};
    int* xPtr {&xRef}; // int* xPtr {&x}; // 取xRef的地址和取x的地址完全一样
    *xPtr = 10;
    std::cout << "x = " << x << std::endl;
    }
    {
    int x {30}, y {50};
    std::cout << fmt::v9::format("(x, y) = ({}, {})\n", x, y);
    swap(x, y);
    std::cout << fmt::v9::format("(x, y) = ({}, {})\n", x, y);
    int* xPtr {&x};
    int* yPtr {&y};
    swap(*xPtr, *yPtr); // 当实参是指针时，可以传值给以应用为形参的函数
    std::cout << fmt::v9::format("(x, y) = ({}, {})\n", x, y);
    }
}

/*
 */
void structuredBindings(void)
{
    std::cout << "testing structuredBindings()...\n";
    std::array arr {11, 22, 33};
    auto [a1, a2, a3] {arr};    // Shall use auto, cannot use int
    std::cout << fmt::v9::format("[a1, a2, a3] = [{}, {}, {}]\n", a1, a2, a3);

    struct Point {double dx, dy, dz;};
    Point px;
    px.dx = 1.0; px.dy = 2.0; px.dz = 3.0;
    auto& [x, y, z] {px};    // The number of variables shall be equal to the members in struct
    std::cout << fmt::v9::format("[x, y, z] = [{}, {}, {}]\n", x, y, z);

    std::pair myPair {"Alan", 25};
    const auto& [myName, myAge] {myPair};  // const and reference can be used with StructureBindings
    std::cout << fmt::v9::format("[Name, Age] = [{}, {}]\n", myName, myAge);
}

int main(int argc, char* argv[])
{
    arrayUsage();
    vectorUsage();
    pairUsage();
    optionalUsage();
    uniformInitialization();
    constUsage();
    referenceUsage();
    structuredBindings();
    return 0;
}