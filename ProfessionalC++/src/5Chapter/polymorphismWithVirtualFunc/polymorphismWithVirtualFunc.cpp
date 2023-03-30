#include <iostream>

// 展示通过虚函数实现多态性：同一界面，多种实现
class Base {
public:
        virtual void vf1() { std::cout << "Calling Base::vf1()\n"; }
        virtual void vf2() { std::cout << "Calling Base::vf2()\n"; }
        virtual void vf3() { std::cout << "Calling Base::vf2()\n"; }
        void f() { std::cout << "Calling Base::f()\n"; }
};

class Derived: public Base {
public:
        void vf1() { std::cout << "Calling Derived::vf1()\n"; }
        void vf2(int) { std::cout << "Calling Derived::vf2()\n"; }
        //char vf3() { std::cout << "Calling Derived::vf3()\n"; }    // 仅返回类型不同不能区分重载，编译错误
        void f() { std::cout << "Calling Derived::f()\n"; }
};

void g()
{
        Derived obj;
        Base* ptr = &obj;

        ptr->vf1(); // 虚函数，根据指针指向Derived对象，绑定为Derived::vf1()
        ptr->vf2(); // Binded to Base::vf2() when compiled
        ptr->f();   // Binded to Base::f() when compiled
}


// 展示如何初始化基类
class Figure {
protected:
        double m_x, m_y;
public:
        Figure(double x, double y) : m_x {x}, m_y {y} {}
        void set_pos(double x, double y)// : m_x { x }, m_y { y } {}，错误：不是构造函数，不能使用初始化列表
        {
                m_x = x;
                m_y = y;
        }
        virtual void show_area()
        {
                std::cout << "No area computation defined.\n";
        }
};

class Triangle: public Figure {
public:
        Triangle(double x, double y) : Figure(x, y) {} // 直接调用基类构造函数来初始化基类对象
        void show_area()
        {
                std::cout << "The area for a Triangle is: ";
                std::cout << "0.5 * x * y = ";
                std::cout << 0.5 * m_x * m_y << std::endl;
        }
};

class Rectangle: public Figure {
public:
        Rectangle(double x, double y) : Figure(x, y) {}
        void show_area()
        {
                std::cout << "The area for a Rectangle is: ";
                std::cout << "x * y = ";
                std::cout << m_x * m_y << std::endl;
        }
};

class Circle: public Figure {
public:
        Circle(double x, double y) : Figure(x, y) {}
        void show_area()
        {
                std::cout << "The area for a Circle is: ";
                std::cout << "3.14 * x * x = ";
                std::cout << 3.14 * m_x * m_x << std::endl;
        }
};

void area()
{
        Figure* p;
        Triangle t {10.0, 5.0};
        Rectangle r {10.0, 5.0};
        Circle c {10.0, 5.0};

        p = &t;
        // p->set_pos(10.0, 5.0);
        p->show_area();
        p = &r;
        // p->set_pos(10.0, 5.0);
        p->show_area();
        p = &c;
        // p->set_pos(10.0, 5.0);
        p->show_area();
}

int main()
{
        std::cout << "Testing Polymorphism feature with virtual function...\n";
        g();
        area();

        return 0;
}