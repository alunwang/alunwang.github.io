/*
 * iterator adapter
 * 作用是将一般迭代器的赋值（assign）操作转变为插入（insert）操作。
 * iterator adapter修饰之后的结果当成是一种迭代器，依然可以用*符号，但不同的是当你对它进行赋值的时候，
 * 它将自动进行insert操作，也就是说该iterator只是将assign操作变成了push_back, push_front, insert，
 * 而其他操作++, --, *全部返回原先的iterator。
 */
#include<iostream>
#include<vector>
#include<iterator>


using namespace std;


template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter target)
{
    for (auto iter { begin }; iter != end; ++iter) {
        *target = *iter;
    }
}


int main(int argc, char* argv[])
{
    vector vectorOne {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> vectorTwo;
    // Uses a back_insert_iterator with myCopy() to populate vectorTwo with copies of all elements from vectorOne
    back_insert_iterator<vector<int>> inserter { vectorTwo };
    myCopy(cbegin(vectorOne)+5, cend(vectorOne), inserter);
    // With class template argument deduction (CTAD), above two lines can also be replaced with:
    // myCopy(cbegin(vectorOne), cend(vectorOne), back_insert_iterator { vectorTwo });
    myCopy(cbegin(vectorTwo), cend(vectorTwo), ostream_iterator<int> {cout, " "});
    cout << "\n";

    // Can also use the std::back_inserter() utility function to create a back_insert_iterator
    myCopy(cbegin(vectorOne), cend(vectorOne), back_inserter(vectorTwo));
    myCopy(cbegin(vectorTwo), cend(vectorTwo), ostream_iterator<int> {cout, " "});
    cout << "\n";

    return 0;
}