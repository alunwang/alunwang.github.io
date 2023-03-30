#ifndef __STRING_H__
#define __STRING_H__

#include <iostream>
#include<string.h>

using namespace std;

class String {
public:
    String(const char* cstr = 0);
    String(const String&);      // class with pointer member must have both copy constructor
    String& operator=(const String&);   // and copy assignment operator
    ~String();

    char* get_string() const { return data; }
private:
    char* data;

    friend ostream& operator<<(ostream&, const String&);
};

// inline String::String(const char* cstr=0) // Error: default value can occur only in its declaration
inline String::String(const char* cstr) // shall be defined as inline
{
    if (cstr) {
        data = new char[strlen(cstr)+1];
        strcpy(data, cstr);
    } else {
        data = new char[1];
        *data = '\0';
    }
}

inline String::String(const String& str)
{
    // char* sstr = str.get_string();
    char* sstr = str.data;  // The objects from the same class are mutual friends
    data = new char[strlen(sstr)+1];
    strcpy(data, sstr);
}

inline String::~String()
{
    delete []data;
}

inline String& String::operator=(const String& str)
{
    if (this == &str) { // self assignment?
        return *this;
    }
    // char* sstr = str.get_string();
    char* sstr = str.data;

    delete [] data;
    data = new char[strlen(sstr)+1];
    strcpy(data, sstr);
    return *this;
}

inline ostream& operator<<(ostream& ostr, const String& str)
{
    ostr << str.data;
    return ostr;
}
#endif // __STRING_H__   