 
#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;


/*
 * Implement the same function as the copy() in the standard library
 */
template <typename InputIter, typename OutputIter>
void myCopy(InputIter begin, InputIter end, OutputIter oBegin)
{
    for (auto iter {begin}; iter != end; ++iter, ++oBegin) {    // Need to make sure oBegin is big enough
        *oBegin = *iter;
    }
}

void printIntVec()
{
    vector myVector {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int> vectorCopy(myVector.size());

    myCopy(cbegin(myVector), cend(myVector), begin(vectorCopy));
    // Use the same myCopy() to print the contents of both vectors.
    myCopy(cbegin(myVector), cend(myVector), ostream_iterator<int> { cout, " " });
    cout << endl;
    myCopy(cbegin(vectorCopy), cend(vectorCopy), ostream_iterator<int> { cout, " " });
    cout << endl;
}

template <typename InputIter>
auto sum(InputIter begin, InputIter end)
{
    auto sum { *begin };
    for (auto iter { ++begin }; iter != end; ++iter) {
        sum += *iter;
    }
    return sum;
}

void testSum()
{
    cout << "Enter numbers separated by whitespace.\n";
    cout << "Press Ctrl+D (Linux) followed by Enter to stop.\n";
    istream_iterator<int> cinInt { cin };
    istream_iterator<int> cinEof;  // Default constructor defines an end input stream iterator

    int result { sum(cinInt, cinEof) };

    cout << "Sum = " << result << "\n";

}

/*
* 看到这种写法，妙啊！
* 平时可能遇到将容器中的各元素以指定符号连接。比如字符串容器，想要将容器中的字符串相加，但中间以；分割。
* 结果ab;cd;ef。正常写法，遍历后相加。
* 能不能使用ostream_iterator来实现呢？ostream_iterator提供了一种可能，查了下ostream_iterator的构造函数，
* 参数只要是basic_ostream都可以，那就是ofstream以及ostringstream也可以。也就是写入文件和字符串流都可以
*/
void elementConcatenation()
{
	vector<int> iVec {54, 3, 89, 7};
	copy(cbegin(iVec), cend(iVec), ostream_iterator<int> { cout, "+"} );
    cout << "\n";
 
	ostringstream oss;
	vector<string> vec {"Alan", "Wang", "lunsheng.wang@gmail.com"};
	vector<string> vec2 { "ab", "cd", "ef" };
 
	ostream_iterator<string> outIter(oss, ":");
	copy(cbegin(vec), cend(vec), outIter);
	string spliceStr { oss.str() };
	cout << spliceStr << endl;
 
	oss.str("");	// 清空
	copy(cbegin(vec2), cend(vec2), outIter);
	string spliceStr2 { oss.str() };
	cout << spliceStr2 << endl;
}

int main(int argc, char *argv[])
{
    elementConcatenation();
    printIntVec();
    testSum();

    int a {5};
    int& ref_a = a;
    int&& rig_a = move(a);
    cout << "a = " << a << "\n";
    cout << "ref_a = " << ref_a << "\n";
    cout << "rig_a  = " << rig_a << "\n";
	getchar();
	return 0;
}