/*
 *  栈的操作
 * 1. 弹栈，通常命名为pop
 * 2. 压栈，通常命名为push
 * 3. 求栈的大小
 * 4. 判断栈是否为空
 * 5. 获取栈顶元素的值
*/

#include<iostream>

using namespace std;

template <typename T>
class ArrayStack {
public:
    ArrayStack(int n=20): top {-1}, capacity {n}
    {
        data = new T(capacity);
    }
    ~ArrayStack()
    {
        delete [] data;
    }

    T& getTop();
    void push(const T& item);
    void pop();
    bool isEmpty() const { return top == -1; }
    int size() const { return top+1; }
private:
    int top = -1;
    int capacity = 10;
    T* data;
};

template <typename T>
T& ArrayStack<T>::getTop()
{
    if (top != -1) {
        return data[top];
    } else {
        cout << "Stack is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template <typename T>
void ArrayStack<T>::push(const T &item)
{
    if (top != capacity-1) {
        data[++top] = item;
    } else {
        cout << "Stack is full.\n";
        exit(EXIT_FAILURE);
    }
}

template <typename T>
void ArrayStack<T>::pop()
{
    if (top != -1) {
        --top;
    } else {
        cout << "Stack is empty.\n";
        exit(EXIT_FAILURE);
    }
}



int main(int argc, char* argv[])
{
    ArrayStack <int> p(5);
    for (int i = 0; i < 5; i++) {
        p.push(i);
    }
    cout << "栈的大小:" << p.size() << endl;
    cout << "栈是否为空:" << p.isEmpty() << endl;
    cout << "栈顶元素：" << p.getTop() << endl;
    cout << "依次出栈:"  << endl;
    while (!p.isEmpty()) {
        cout << p.getTop() << endl;
        p.pop();
    }
    getchar();
    return 0;
}
