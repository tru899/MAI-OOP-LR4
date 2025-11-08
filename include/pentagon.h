#pragma once
#include "figure.h"
#include <cmath>
using namespace std;

template <typename T>
class Pentagon : public Figure<T> {
private:
    T side;
public:
    Pentagon(T x, T y, T s) : side(s) { this->center_point = make_unique<Point<T>>(x, y); }
    double area() const override { return 1.72048 * side * side; }
    void print(ostream& os) const override { os << "Pentagon: side=" << side << ", area=" << area() << ", center=" << *this->center_point; }
    Point<T> getCenter() const override { return *this->center_point; }
    vector<Point<T>> getVertices() const override {
        vector<Point<T>> points;
        double cx = static_cast<double>(this->center_point->getX());
        double cy = static_cast<double>(this->center_point->getY());
        for (int i = 0; i < 5; ++i) points.emplace_back(cx + side*cos(2*M_PI*i/5), cy + side*sin(2*M_PI*i/5));
        return points;
    }
};
