#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Point {
private:
    T x, y;
public:
    Point() : x(0), y(0) {}
    Point(T x_val, T y_val) : x(x_val), y(y_val) {}
    T getX() const { return x; }
    T getY() const { return y; }
    void setX(T x_val) { x = x_val; }
    void setY(T y_val) { y = y_val; }
    bool operator==(const Point& other) const { return x == other.x && y == other.y; }
    Point operator+(const Point& other) const { return Point(x + other.x, y + other.y); }
    Point operator/(T div) const { return Point(x / div, y / div); }
    friend ostream& operator<<(ostream& os, const Point& p) { os << "(" << p.getX() << ", " << p.getY() << ")"; return os; }
};
