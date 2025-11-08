#include <iostream>
#include <memory>
#include <iomanip>
#include "point.h"
#include "figure.h"
#include "pentagon.h"
#include "hexagon.h"
#include "rhombus.h"
#include "array.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const Figure<T>& fig) {
    fig.print(os);
    return os;
}

int main() {
    auto pentagon = make_shared<Pentagon<int>>(0, 0, 5);
    auto hexagon = make_shared<Hexagon<int>>(1, 1, 4);
    auto rhombus = make_shared<Rhombus<int>>(2, 2, 6, 3);

    cout << "Created figures:\n";
    cout << *pentagon << endl;
    cout << *hexagon << endl;
    cout << *rhombus << endl;

    Array<shared_ptr<Figure<int>>> figures;
    figures.add(pentagon);
    figures.add(hexagon);
    figures.add(rhombus);

    cout << "\nAll figures in array:\n";
    for (size_t i = 0; i < figures.size(); ++i) {
        cout << "Figure " << i << ": " << *figures[i] << endl;
        cout << "  Center: " << figures[i]->getCenter() << endl;
        cout << "  Area: " << fixed << setprecision(2) << figures[i]->area() << endl;
        auto verts = figures[i]->getVertices();
        cout << "  Vertices: ";
        for (size_t j = 0; j < verts.size(); ++j) {
            cout << verts[j];
            if (j < verts.size() - 1) cout << ", ";
        }
        cout << "\n";
    }

    double total_area = 0;
    for (size_t i = 0; i < figures.size(); ++i) total_area += static_cast<double>(*figures[i]);
    cout << "\nTotal area of all figures: " << total_area << endl;

    figures.remove(1);
    cout << "\nAfter removing figure at index 1, array size: " << figures.size() << endl;

    Array<shared_ptr<Pentagon<double>>> pent_arr;
    pent_arr.add(make_shared<Pentagon<double>>(0, 0, 2.5));
    pent_arr.add(make_shared<Pentagon<double>>(1, 1, 3.0));

    cout << "\nPentagons array:\n";
    for (size_t i = 0; i < pent_arr.size(); ++i) {
        cout << "[" << i << "] " << *pent_arr[i] << endl;
    }

    cout << "\nDemonstrating move semantics:\n";
    Array<shared_ptr<Figure<int>>> moved_figures = move(figures);
    cout << "Original array size after move: " << figures.size() << endl;
    cout << "Moved array size: " << moved_figures.size() << endl;

    return 0;
}
