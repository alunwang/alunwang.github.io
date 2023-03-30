#include<iostream>
#include "mstring.h"
#include<memory>

using namespace std;

int main(int argc, char** argv)
{
    String s1;
    String s2 { "Hello S2" };
    const char str[] { "Hello S3" };
    String s3 { str };
    s1 = s3;
    cout << s1 << "\n";
    cout << s2 << "\n";
    cout << s3 << "\n";

    String *pstr = new String[5];
    for (int i=0; i<5; i++) {

    }
    cout << "s1 address: " << &s1 << "\n";
    cout << "pstr address: " << pstr << "\n";
    delete [] pstr;

    auto variableArray { make_unique<int[]>(10) };
    variableArray[0] = 123;
    cout << variableArray[0] << "\n";
    return 0;
}