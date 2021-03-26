#include <iostream>
#include "gtest/gtest.h"
#include "test2.h"
#include <sstream>

using namespace std;
TEST(IsOnLine, vertical) {
	Point a = {.x = 6.0, .y = 6.0};
	Point b = {.x = 6.0, .y = -6.0};
	Point x = {.x = 6.0, .y = 5.9};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = 5};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = 4};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = 3};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = -1};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = -5};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), true);
	x = {.x = 6.0, .y = -7};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), false);
	x = {.x = 6.1, .y = 0};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), false);
	x = {.x = 7, .y = -1};
	EXPECT_EQ(isBetween(a, b, x) && isOnLine(a, b, x), false);
}
TEST(Basic, _inside) {
	istringstream polygon("0 0\n2 5\n6 6\n6 -6\n");
	Solver s(polygon);
	istringstream points("5 3\n5.9 0\n 5 0\n 1 0\n 2 2\n 2 -1.9\n");
	ostringstream out;
	for (Point q; points >> q; ) {
		out << q << ": " << s.Probe(q) << "\n";
	}
	EXPECT_EQ(out.str(), "(5,3): 2\n(5.9,0): 2\n(5,0): 2\n(1,0): 2\n(2,2): 2\n(2,-1.9): 2\n");
}
TEST(Basic, _vertex) {
	istringstream polygon("0 0\n2 5\n6 6\n6 -6\n");
	Solver s(polygon);
	istringstream points("0 0\n 2 5\n 6 6\n 6 -6\n");
	ostringstream out;
	for (Point q; points >> q; ) {
		out << q << ": " << s.Probe(q) << "\n";
	}
	EXPECT_EQ(out.str(), "(0,0): 0\n(2,5): 0\n(6,6): 0\n(6,-6): 0\n");
}
TEST(Basic, _edge) {
	istringstream polygon("0 0\n2 5\n6 6\n6 -6\n");
	Solver s(polygon);
	istringstream points("6 3\n 2 -2\n1 2.5\n5.9 -5.9\n4 5.5\n6 0\n 6 -5.9\n6 5.9\n");
	ostringstream out;
	for (Point q; points >> q; ) {
		out << q << ": " << s.Probe(q) << "\n";
	}
	EXPECT_EQ(out.str(), "(6,3): 1\n(2,-2): 1\n(1,2.5): 1\n(5.9,-5.9): 1\n"
		"(4,5.5): 1\n(6,0): 1\n(6,-5.9): 1\n(6,5.9): 1\n");
}
TEST(Basic, _outside) {
	istringstream polygon("0 0\n2 5\n6 6\n6 -6\n");
	Solver s(polygon);
	istringstream points("7 0\n 7 6\n-1 0\n0 1\n0 -1\n3 7\n1 -2\n6.1 3\n");
	ostringstream out;
	for (Point q; points >> q; ) {
		out << q << ": " << s.Probe(q) << "\n";
	}
	EXPECT_EQ(out.str(), "(7,0): 3\n(7,6): 3\n(-1,0): 3\n(0,1): 3\n(0,-1): 3\n(3,7): 3\n(1,-2): 3\n(6.1,3): 3\n");
}
int main(int argc, char *argv[]) {
	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();;
}
