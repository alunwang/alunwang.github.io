#include<vector>
#include<iterator>
#include "myPrint.h"
#include "printFuncName.h"


using namespace std;


void vectorInsertErase()
{
    vector vectorOne {1, 2, 3, 5};
    vector<int> vectorTwo;

    // Oops, we forgot to add '4' in vectorOne, insert it here
    vectorOne.insert(cbegin(vectorOne)+3, 4);
    printRange("vectorOne: ", vectorOne);

    // Add 6 through 10 to vectorTwo
    for (int i {6}; i<=10; i++) {
        vectorTwo.push_back(i);
    }
    printRange("vectorTwo: ", vectorTwo);

    // Add all elements from vectorTwo to the end of vectorOne
    vectorOne.insert(cend(vectorOne), cbegin(vectorTwo), cend(vectorTwo));
    printRange("vectorOne: ", vectorOne);

    // Erase the 2nd to 5th items in vectorOne
    vectorOne.erase(cbegin(vectorOne)+1, cbegin(vectorOne)+5);
    printRange("vectorOne: ", vectorOne);

    /*
     * Introduced in C++20, a more elegant solution to erase item:
     * std::erase() and std::erase_if()
     * two non-member functions defined for all Standard Library containers.
     */
    // Erase the one equal to 1
    erase(vectorOne, 1);
    printRange("vectorOne: ", vectorOne);
    erase_if(vectorOne, [](const auto& value) { return value % 2 == 0; });
    printRange("vectorOne: ", vectorOne);

    // Clear vectorTwo entirely
    vectorTwo.clear();

    // Add 10 copies of 100 to it
    vectorTwo.insert(cbegin(vectorTwo), 10, 100);
    printRange("vectorTwo: ", vectorTwo);

    // Pop out 1 item
    vectorTwo.pop_back();
    printRange("vectorTwo: ", vectorTwo);
    cout << __STR_FUNCTIONPC__ << endl;
}

int main()
{
    vectorInsertErase();

    return 0;
}