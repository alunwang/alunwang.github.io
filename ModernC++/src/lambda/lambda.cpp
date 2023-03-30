#include<iostream>
#include<memory>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
    vector<int> nums {1, 2, 4, 8, 9, 11, 23, 26, 32};

    auto it = find_if(nums.begin(), nums.end(), [](int x) { return x%2 == 0;} );
    cout << "First odd number is: " << *it << "\n";

    return 0;
}