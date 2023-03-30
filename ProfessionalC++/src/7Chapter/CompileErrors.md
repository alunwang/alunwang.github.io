# Virtual function
## V1
* Error:
In file included from iterator.cpp:3:
iterator.h: In instantiation of ‘class Iterator<int>’:
iterator.h:13:7:   required from ‘class ArrayIterator<int>’
iterator.cpp:9:24:   required from here
iterator.h:9:7: error: initializer specified for non-virtual method ‘T Iterator<T>::next() [with T = int]’
    9 |     T next() = 0;
* Solution:
忘记给虚函数next()加上“virtual”






# Parameter with default value
## P1
* Error:
mstring.h:18:8: error: default argument given for parameter 1 of ‘String::String(const char*)’ [-fpermissive]
   18 | inline String::String(const char* cstr=0)
      |        ^~~~~~
mstring.h:8:5: note: previous specification in ‘String::String(const char*)’ here
    8 |     String(const char* cstr = 0);
* Solution:
仅在函数声明中指定参数默认值，在函数实现中不能再有。