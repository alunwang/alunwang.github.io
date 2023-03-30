/*
 *
 */
#include<iostream>
#include<array>
#include<vector>
#include<list>
#include<forward_list>
#include<deque>
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<iterator>
#include<typeinfo>

using std::cbegin;
using std::cend;



void _display_category(std::random_access_iterator_tag)
{
    std::cout << "randdom_access_iterator" << std::endl;
}
void _display_category(std::bidirectional_iterator_tag)
{
    std::cout << "bidirectional_iterator" << std::endl;
}
void _display_category(std::forward_iterator_tag)
{
    std::cout << "forward_iteraotr" << std::endl;
}
void _display_category(std::output_iterator_tag)
{
    std::cout << "output_iterator" << std::endl;
}
void _display_category(std::input_iterator_tag)
{
    std::cout << "input_iterator" << std::endl;
}

template <typename I>
void display_category(I iter)
{
    typename std::iterator_traits<I>::iterator_category cate;
    _display_category(cate);

    std::cout << "typeid(iter).name() = " << typeid(iter).name() << "\n\n";
}

void display()
{
    std::cout << "\ntest_iterator_category:\n";
    display_category(std::array<int, 10>::iterator());
    display_category(std::vector<int>::iterator());
    display_category(std::list<int>::iterator());
    display_category(std::forward_list<int>::iterator());
    display_category(std::deque<int>::iterator());

    display_category(std::set<int>::iterator());
    display_category(std::map<int, int>::iterator());
    display_category(std::multiset<int>::iterator());
    display_category(std::multimap<int, int>::iterator());
    display_category(std::unordered_set<int>::iterator());
    display_category(std::unordered_map<int, int>::iterator());
    display_category(std::unordered_multiset<int>::iterator());
    display_category(std::unordered_multimap<int, int>::iterator());

    display_category(std::istream_iterator<int>());
    display_category(std::ostream_iterator<int>(std::cout, ""));
}

template <typename Iter>
void myPrint(Iter begin, Iter end)
{
    for (auto iter {begin}; iter != end; ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << "\n";
}

template <typename Iter>
auto myFind(Iter begin, Iter end, const typename std::iterator_traits<Iter>::value_type& value)
{   // Use iterator_traits to ask for its value_type
    for (auto iter {begin}; iter != end; ++iter) {
        if (*iter == value) {   // Found, then return that iterator
            return iter;
        }
    }
    return end; // Not found, then return the end
}


int main(int argc, char* argv[])
{
    std::vector values {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // Always use != instead of <, because != supported by all iterators, while < not supported by bidirectional and forward iterators
    for (auto citer {cbegin(values)}; citer != cend(values); ++citer) {
        std::cout << *citer << " ";
    }
    std::cout << std::endl;

    display();

    auto result {myFind(cbegin(values), cend(values), 7)};
    if (result != cend(values)) {
        std::cout << "Found value at position " << distance(cbegin(values), result) << "\n";
    } else {
        std::cout << "Value not found\n";
    }
    return 0;
}

