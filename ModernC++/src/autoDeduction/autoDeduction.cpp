/*
 * auto在实际开发中到底有什么应用?
 */

#include<iostream>
#include<vector>


using namespace std;


/*
 * 1. auto 的一个典型应用场景是用来定义STL的迭代器。
 * 我们在使用STL容器的时候，需要使用迭代器来遍历容器里面的元素；不同容器有不同类型的迭代器，
 * 而迭代器的类型有时候比较复杂。
 */
void autoInIterator(void)
{
    vector<pair<int, int>> pairs {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

    // for (vector<pair<int, int>>::const_iterator it {pairs.cbegin()}; it != pairs.cend(); ++it) {
    for (auto it {pairs.cbegin()}; it != pairs.cend(); ++it) {  // 使用auto让compiler推导其类型，可读性更好
        cout << it->first << ", " << it->second << "\n";
    }
}


/*
 * 2. auto的另一个应用就是当我们不知道变量是什么类型，或者不希望指明具体类型的时候，比如泛型编程中。
 */
template <typename T>
auto maxVal(const T& x, const T& y)
{
    if (x > y) {
        return x;
    } else {
        return y;
    }
}

class A {
public:
    static int get(void)
    {
        return 100;
    }
};

class B {
public:
    static const char* get(void)
    {
        return "http://c.biancheng.net/cplus/";
    }
};

template <typename T>
void func(void)
{
    auto val = T::get();    // 这里调用不同的类的get()函数，它的返回值不同，不能设定死，需要auto，才能自动转换，统一处理。
    cout << val << endl;
}

int main(int argc, char** argv)
{
    autoInIterator();

    int ia {10}, ib {20};
    cout << "maxVal(" << ia << ", " << ib << ") = " << maxVal(ia, ib) << "\n";
    long la {1000000}, lb {2000000};
    cout << "maxVal(" << la << ", " << lb << ") = " << maxVal(la, lb) << "\n";
    double da {0.0001}, db {0.0002};
    cout << "maxVal(" << da << ", " << db << ") = " << maxVal(da, db) << "\n";

    func<A>();
    func<B>();
    return 0;
}