#pragma once
#include "point.h"
#include <memory>
#include <vector>
using namespace std;

template <typename T>
class Figure {
protected:
    unique_ptr<Point<T>> center_point;
public:
    Figure() : center_point(make_unique<Point<T>>()) {}
    Figure(T x, T y) : center_point(make_unique<Point<T>>(x, y)) {}
    virtual ~Figure() {}
    virtual double area() const = 0;
    virtual void print(ostream& os) const = 0;
    virtual Point<T> getCenter() const = 0;
    virtual vector<Point<T>> getVertices() const = 0;
    explicit operator double() const { return area(); }
    bool operator==(const Figure& other) const { return area() == other.area(); }
    bool operator<(const Figure& other) const { return area() < other.area(); }
};
