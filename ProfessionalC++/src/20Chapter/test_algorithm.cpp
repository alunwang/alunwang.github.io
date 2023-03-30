#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>  // accumulate()


using namespace std;


void test_find(const auto& v)
{
    while (true) {
        cout << "Enter a number to lookup (0 to stop): ";
        int number;
        cin >> number;
        if (number == 0) {
            break;
        }
        auto endIter {cend(v)};
        // auto iter {find(cbegin(v), endIter number)};
        // if (iter == endIter) {
        if (auto iter {find(cbegin(v), endIter, number)}; iter == endIter) {
            cout << "Cannot find " << number << endl;
        } else {
            cout << "Found " << *iter << endl;
        }
    }
}
bool perfectScore(int num)
{
    return (num >= 100);
}

void test_find_if(const auto& v)
{
    auto endIter {cend(v)};
    // if (auto iter {find_if(cbegin(v), endIter, perfectScore)}; iter == endIter) {
    if (auto iter {find_if(cbegin(v), endIter, [](int i){return i>=100;})}; iter == endIter) { // Lambda function
        cout << "No perfect score found." << endl;
    } else {
        cout << "Found perfect score " << *iter << endl;
    }
}

void test_accumulate(span<const int> values)
{
    double sum {accumulate(cbegin(values), cend(values), 0.0)};
    cout << "Sum(values) = " << sum << endl;
    cout << "Average(values) = " << (sum / values.size()) << endl;
}

int main()
{
    vector<int> myVec;
    while (true) {
        cout << "Enter a number to store (0 to stop): ";
        int number;
        cin >> number;
        if (number == 0) {
            break;
        }
        myVec.push_back(number);
    }

    test_find(myVec);

    return 0;
}