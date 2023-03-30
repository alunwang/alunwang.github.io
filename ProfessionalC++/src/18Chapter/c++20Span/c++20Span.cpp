#include <span>
#include <iostream>

using namespace std;

void spanUse(void)
{
    constexpr char str[] = "ABCDEF\n";
    const span sp {str};
    for (auto n {sp.size()}; n != 2; --n) {
        cout << sp.last(n).data();
    }
    for (auto n {2}; n <= sp.size(); ++n) {
        cout << sp.last(n).data();
    }
}

int main()
{
    spanUse();
    return 0;
}