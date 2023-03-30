#include<iostream>
#include<memory>
#include "iterator.h"

using namespace std;

int sum(int* p, int n)
{
    ArrayIterator<int> aiter { ArrayIterator<int>(p, n) };
    return sum(&aiter);
}

int main(int argc, char** argv)
{
    int a[10];

    cout << "Please input 10 number:\n";
    for (auto i=0; i<10; i++) {
        cin >> a[i];
    }
    cout << "The sum of them: " << sum(a, 10) << endl;

    return 0;
}

