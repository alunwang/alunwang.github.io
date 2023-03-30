#include<iostream>
#include<vector>
#include<ranges>
#include<algorithm>
#include<string>
#include<iterator>
#include<algorithm>
#include "myPrint.h"

using namespace std;


template <typename InputIter>
auto sum(InputIter begin, InputIter end)
{
    auto sum { *begin };
    for (auto iter { ++begin }; iter != end; ++iter) { sum += *iter; }
    return sum;
}

class Person {
public:
    Person(string first, string last) : m_firstName {move(first)}, m_lastName {move(last)}
    {
    }
    const string& getFirstName() const
    {
        return m_firstName;
    }
    const string& getLastName() const
    {
        return m_lastName;
    }
private:
    string m_firstName;
    string m_lastName;

    friend ostream& operator<<(ostream& ostr, const Person& p);
};

ostream& operator<<(ostream& ostr, const Person& p)
{
    ostr << p.m_firstName << "." << p.m_lastName << "\n";
    return ostr;
}

void rangeProjection()
{
    vector persons {Person {"John", "White"}, Person {"Chris", "Blue"}, Person {"Donald", "Trump"}};
    
    ranges::sort(persons, {}, [](const Person& p) { return p.getFirstName(); });
    for (auto p: persons) cout << p;
}


// void printRange(string_view message, auto& range)
// {
//     cout << message;
//     for (const auto& value : range) {
//         cout << value << " ";
//     }
//     cout << endl;
// }

void rangeView()
{
    vector values {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printRange("Original sequence: ", values);

    auto result1 {values | views::filter([](const auto& value) { return value % 2 == 0;})};
    printRange("Only even values: ", result1);

    auto result2 {values | views::transform([](const auto& value) { return value * 2.0; })};
    printRange("Values doubled: ", result2);

    auto result3 {values | views::drop(2)};
    printRange("Dropped first two: ", result3);

    auto result4 {result3 | views::reverse};
    printRange("Sequence reverse: ", result4);

    auto result {values | views::filter([](const auto& value) { return value % 2 == 1; })
        | views::transform([](const auto& value) { return value * 2.0; })
        | views::drop(2)
        | views::reverse};
    printRange("Final sequence after chained view operations: ", result);
}

/*
 * Exercise 17-1: Write a program that lazily constructs the sequence of elements 10-100, squares each number, 
 * removes all numbers dividable by five, and transforms the remaining values to strings using std::to_string().
 */
void rangEx17_1()
{
    auto result { views::iota(10)
        | views::take(91)
        | views::transform([](auto const& value) { return value * value; })
        | views::filter([](auto const& value) { return value % 5 != 0; })};
    
    for (auto value : result) cout << to_string(value) << " ";
    cout << endl;
}

/*
 * Exercise 17-2: Write a program that creates a vector of pair s, where each pair contains an instance
 * of the Person class introduced earlier in this chapter, and their age. Next, use the ranges library to
 * construct a single pipeline that extracts all ages from all persons from the vector, and removes all
 * ages below 12 and above 65. Finally, calculate the average of the remaining ages using the sum()
 * algorithm from earlier in this chapter. As you'll pass a range to the sum() algorithm, you'll have to
 * work with a common range.
 */
void rangeEx17_2()
{
    vector peoples {
        pair{Person {"John", "White"}, 55},
        pair{Person {"Chris", "Blue"}, 66},
        pair{Person {"Donald", "Trump"}, 72},
        pair{Person {"Donald", "Junior"}, 38},
        pair{Person {"Eric", "Trump"}, 35},
        pair{Person {"Baron", "Trmp"}, 11}
    };

    auto result {views::common(peoples  // Convert the resulting range to a common range.
        | views::values
        // views::take_while([]auto const& age { return (age>=12 && age<=65)})};    // Why this doesn't work???
        | views::filter([](auto const& age) { return (age >= 12 && age <= 65); }))};
    auto num { distance(begin(result), end(result)) };
    if (!num) {
        cout << "No people found, divided by 0" << endl;
        return;
    }
    cout << "Average age " << sum(begin(result), end(result)) / static_cast<double>(num) << endl;
    for (auto const& value : result) cout << value <<" ";
    cout << endl;
}

int main(int argc, char* argv[])
{
    rangeProjection();
    rangeView();
    rangEx17_1();
    rangeEx17_2();
    return 0;
}