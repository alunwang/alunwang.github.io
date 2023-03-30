#ifndef __PUREVIRTUALFUNCTION_H__
#define __PUREVIRTUALFUNCTION_H__

class Point {
    //
};

class Shape {
    Point center;
public:
    Point where() const { return center; }
    void move(Point p) { center = p; draw(); }
    virtual void rotate(const& int) = 0;
    virtual void draw() = 0;
};

#endif // __PUREVIRTUALFUNCTION_H__