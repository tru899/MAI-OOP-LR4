#include <gtest/gtest.h>
#include <memory>
#include <cmath>

#include "../include/point.h"
#include "../include/figure.h"
#include "../include/pentagon.h"
#include "../include/hexagon.h"
#include "../include/rhombus.h"
#include "../include/array.h"

TEST(PointTest, ConstructionAndAccess) {
    Point<int> p1(10, 20);
    EXPECT_EQ(p1.getX(), 10);
    EXPECT_EQ(p1.getY(), 20);
}

TEST(FigureTest, PentagonArea) {
    Pentagon<int> p(0, 0, 4);
    double expected = 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * 4 * 4;
    EXPECT_NEAR(p.area(), expected, 0.001);
}

TEST(FigureTest, HexagonArea) {
    Hexagon<int> h(0, 0, 3);
    double expected = (3 * sqrt(3) / 2.0) * 3 * 3;
    EXPECT_NEAR(h.area(), expected, 0.001);
}

TEST(FigureTest, RhombusArea) {
    Rhombus<int> r(0, 0, 6, 4);
    double expected = 0.5 * 6 * 4;
    EXPECT_DOUBLE_EQ(r.area(), expected);
}

TEST(FigureTest, DoubleConversion) {
    Pentagon<int> p(0, 0, 3);
    double area = static_cast<double>(p);
    double expected = 0.25 * sqrt(5 * (5 + 2 * sqrt(5))) * 3 * 3;
    EXPECT_NEAR(area, expected, 0.001);
}

TEST(FigureTest, VerticesCount) {
    Pentagon<int> p(0,0,3);
    EXPECT_EQ(p.getVertices().size(), 5);
    Hexagon<int> h(0,0,2);
    EXPECT_EQ(h.getVertices().size(), 6);
    Rhombus<int> r(0,0,4,2);
    EXPECT_EQ(r.getVertices().size(), 4);
}

TEST(ArrayTest, BasicOperationsFigures) {
    Array<std::shared_ptr<Figure<int>>> arr;
    arr.add(std::make_shared<Pentagon<int>>(0,0,3));
    arr.add(std::make_shared<Hexagon<int>>(0,0,2));
    arr.add(std::make_shared<Rhombus<int>>(0,0,4,2));

    EXPECT_EQ(arr.size(), 3);
    for (size_t i=0;i<arr.size();++i)
        EXPECT_GT(arr[i]->area(), 0);
}

TEST(ArrayTest, RemoveOperation) {
    Array<int> arr{1,2,3,4,5};
    arr.remove(2);
    EXPECT_EQ(arr.size(), 4);
    EXPECT_EQ(arr[2], 4);
}

TEST(ArrayTest, MoveSemantics) {
    Array<int> original{1,2,3};
    Array<int> moved = std::move(original);

    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(original.size(), 0);
}

TEST(FigureTest, PrintAndCenter) {
    Pentagon<int> p(1,2,3);
    Hexagon<int> h(0,0,2);
    Rhombus<int> r(-1,1,4,5);

    std::ostringstream oss;
    p.print(oss);
    EXPECT_NE(oss.str().find("Pentagon"), std::string::npos);

    Point<int> pc = p.getCenter();
    EXPECT_EQ(pc.getX(), 1);
    EXPECT_EQ(pc.getY(), 2);
}

TEST(ArrayTest, SharedPointerArrayAccess) {
    Array<std::shared_ptr<Figure<int>>> arr;
    auto pent = std::make_shared<Pentagon<int>>(0,0,3);
    arr.add(pent);
    EXPECT_EQ(arr[0]->getVertices().size(), 5);
    arr.remove(0);
    EXPECT_EQ(arr.size(), 0);
}
