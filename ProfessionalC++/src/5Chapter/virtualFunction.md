# Contents


## 5 Derived Class

### 5.3 Virtual Function and Polymorphism
#### 5.3.2 Virtual Function
##### 5.3.2.1 Introduction
First, let's examine the following example:
```
#include<typeinfo>
#include<cxxabi.h>

// Get class name
static int demangle_status; // Must be static
#define __CLASS__ __class__
#define __class__ abi::__cxa_demangle(typeid(*this).name(), 0, 0, &demangle_status)

using namespace std;

class Base {
public:
    void who() const { cout << __CLASS__ << "\n"; }
};

class FirstD: public Base {
public:
    void who() const { cout << __CLASS__ << "\n"; }
};

class SecondD: public Base {
public:
    void who() const { cout << __CLASS__ << "\n"; }
};

#endif // __OVERLOAD_IN_CLASS_H__
```
```
#include<iostream>
#include "overloadInClass.h"

using namespace std;

int main(int argc, char** argv)
{
    Base bobj;
    Base* p;
    FirstD fobj;
    SecondD sobj;

    p = &bobj;  // 1
    p->who();   // 2
    p = &fobj;  // 3
    p->who();   // 4
    p = &sobj;  // 5
    p->who();   // 6
    
    fobj.who(); // 7
    sobj.who(); // 8

    return 0;
}
```
The output of the program is:
```
Base
Base
Base
FirstD
SecondD
```
Here above a Base class is created. Two derived classes FirstD and SecondD are derived from this Base class. There is a who() function in the each class, so it is obvious that the who() functions in FirstD and SecondD classes overwrite the one from the Base class.

According to the program and its output, we can see:
- A Base class type pointer can point to its derived class object directly without conversion.
- For general member function, either p points to bobj, fobj, or sobj, p->who() always calls the version of the who() defined in the Base class. This means the function call invoked by a pointer (or reference) is related only with the type of the pointer (or reference), not related to the object it is now pointing to. The root cause for it is that this binding is determined during compilation.

So we need explictly call:
```
fobj.who();
```
or
```
sobj.who();
```
in order to call the version of who() from classes FirstD and SecondD.

But lines from 1 to 6 in the above main() are just what we are interested in. That is, when p points to different object, p->who() will call corresponding version of who(). In that case, a single interface p->who() can be used to call multiple implementations of who(), that is, when p points to different object, different version of who() will be binded to it. What is more, this binding is not determined statically during compilation, however, it is binded during execution. It is binded dynamically during execution, depending on what object it is pointing to. General function cannot support this binding, the introduction of virtual function solves this problem.

Virtual function is a function declared with the keyword "virtual" in a base class. It defines an interface the "virtual" keyword in the base class, whose body can then be overwritten in one or more derived classes.

在派生类中，重写(override)继承自基类成员函数的实现(implementation)时，要满足如下条件：

  一虚：基类中，成员函数声明为虚拟的(virtual)

  二容：基类和派生类中，成员函数的返回类型和异常规格(exception specification)必须兼容

  四同：基类和派生类中，成员函数名、形参类型、常量属性(constness)和引用限定符(reference qualifier)必须完全相同

With the above criterions met, only one change is required: add the "virtual" keyword to the who() in the Base class, as below:
```
...
class Base {
public:
    virtual void who() const { cout << __CLASS__ << "\n"; }
};
...
```
Now the output of the program will be:
```
Base
FirstD
SecondD
FirstD
SecondD
```
The virtual function who() in the Base class defines a unified interface, while in the derived class, different versions of body are implemented. This interpretation of virtual function makes the idea of "single interface, multipile implementations" possible.

##### 5.3.2.2 Multiple Inheritences and Virtual Funtion

#### 5.3.3 Pure Virtual Function and Abstract Class
In general, base class expresses some abstract concepts, e.g. Shape is a base class and it describes a kind of objects with shape. From the Shape class, we can derive two derived classes: one for closed shapes and one for  unclosed shapes. And from the closed shape class, oval class, polygon class, circle class and so on can be derived. As the basis of this class hierachy, Shape class expresses an abstract concept, and apparently it is meaningless to declare an area function in the Shape class. It would be very meaningful, however, if we can define such a unified interface (function) in the Shape class - it doesn't include any implementation within it, instead, it leaves specific implemention to its derived class. Pure virtual function introduced for this purpose.

Here is the general form to declare a pure virtual function:
```
virtual type func_name(paramter_list) = 0;
```
Here are the features for pure virtual function:
- is a member function declared in a base class.
- doesnot include implementation within it.
- requires that derived class shall include its implemention.

##### 5.3.3.2 Abstract Class
If there is at least one pure virtual function in a base class, this base class is called abstract class. As abstract class includes pure virtual function, which doesn't contain its function body implementation, it is used to express abstract concept and to declare abstract interfaces.And here are some features for abstract class:
- can't be used to define object.
- can't be used as the parameter of function.
- can't be used as the return type of function.
- can't be used as conversion type.
- can be used to define pointer.
- can be used as reference.

Here is an example of abstract class:
```
class Point;

class Shape {
    Point center;
public:
    Point where() const { return center; }
    void move(Point p) { center = p; draw(); }
    virtual void rotate(const& int) = 0;
    virtual void draw() = 0;
};
```