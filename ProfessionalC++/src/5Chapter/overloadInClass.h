#ifndef __OVERLOAD_IN_CLASS_H__
#define __OVERLOAD_IN_CLASS_H__

#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

// Get class name
static int demangle_status; // Must be static
#define __CLASS__ __class__
#define __class__ abi::__cxa_demangle(typeid(*this).name(), 0, 0, &demangle_status)


class Base {
public:
    virtual void who() const { std::cout << "This is class " << __CLASS__ << "\n"; }
};

class FirstD: public Base {
public:
    void who() const { std::cout << "This is class " << __CLASS__ << "\n"; }
};

class SecondD: public Base {
public:
    void who() const { std::cout << "This is class " << __CLASS__ << "\n"; }
};

#endif // __OVERLOAD_IN_CLASS_H__