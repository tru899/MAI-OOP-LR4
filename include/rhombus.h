#pragma once
#include "figure.h"
using namespace std;

template <typename T>
class Rhombus : public Figure<T> {
private:
    T d1, d2;
public:
    Rhombus(T x, T y, T diag1, T diag2) : d1(diag1), d2(diag2) { this->center_point = make_unique<Point<T>>(x, y); }
    double area() const override { return 0.5 * d1 * d2; }
    void print(ostream& os) const override { os << "Rhombus: d1=" << d1 << ", d2=" << d2 << ", area=" << area() << ", center=" << *this->center_point; }
    Point<T> getCenter() const override { return *this->center_point; }
    vector<Point<T>> getVertices() const override {
        T cx = this->center_point->getX(), cy = this->center_point->getY();
        return { {cx - d1/2, cy}, {cx, cy + d2/2}, {cx + d1/2, cy}, {cx, cy - d2/2} };
    }
};
