#ifndef _TEST2_H_
#define _TEST2_H_

#include <array>
#include <cmath>
//#include <fstream>
#include <iostream>
#include <algorithm>

static const float eps = 0.000001;

enum class Result {
	VERTEX = 0,
	EDGE = 1,
	INSIDE = 2,
	OUTSIDE = 3,
};
std::ostream& operator << (std::ostream& out, Result r);

struct Point {
	float x, y;
};

std::istream& operator >> (std::istream& input, Point& p);
std::ostream& operator << (std::ostream& out, Point& p);

class Solver {
	public:
		Solver(std::istream& in);
		Result Probe(Point p);
	private:
		struct Polygon {
			std::array<Point, 4> vertexes;
			constexpr size_t Size() const {
				return vertexes.size();
			}
			bool isInside(Point p) const;
			bool onVertex(Point p) const;
			bool onEdge(Point p) const;
		};
		Polygon polygon;
};
bool isBetween(Point v1, Point v2, Point x);
bool isOnLine(Point v1, Point v2, Point x);
#endif // _TEST2_H_

