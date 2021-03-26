#include "test2.h"

using namespace std;


std::ostream& operator << (std::ostream& out, Result r) {
	out << static_cast<int>(r);
	return out;
}

std::istream& operator >> (std::istream& input, Point& p) {
	input >> p.x >> p.y;
	return input;
}
std::ostream& operator << (std::ostream& out, Point& p) {
	out << "(" << p.x << "," << p.y << ")";
	return out;
}

// пока мы сравниваем введенные числа, можно этого не делать, но при расчетах -- обязательно!
bool Eq(float a, float b) {
	if (std::fabs(a - b) <= eps) {
		return true;
	} else {
		return false;
	}
}

bool isBetween(Point v1, Point v2, Point q) {
	return (q.x >= std::min(v1.x, v2.x)) && (q.x <= std::max(v1.x, v2.x)) && 
		(q.y >= std::min(v1.y, v2.y)) && (q.y <= std::max(v1.y, v2.y)) ;
}

bool isOnLine(Point v1, Point v2, Point q) {
	// учесть случай вертикальной линии, там k == inf
	if ((v1.x == v2.x) && (q.x == v1.x) && (q.x == v2.x)) {
		return true;
	} else {
		// v1.x <= q.x <= v2.x
		// v1.y <= q.y <= v2.y
		float k = (v2.y - v1.y) / (v2.x - v1.x);
		float k_prime = (q.y - v1.y) / (q.x - v1.x);
		return Eq(k, k_prime);
	}
	return false;
}

Solver::Solver(std::istream& input) {
	for (size_t i = 0; i < polygon.Size(); ++i) {
		input >> polygon.vertexes[i];
	}
}

Result Solver::Probe(Point p) {
	if (polygon.onVertex(p)) {
		return Result::VERTEX;
	} else if (polygon.onEdge(p)) {
		return Result::EDGE;
	} else if (polygon.isInside(p)) {
		return Result::INSIDE;
	} else {
		return Result::OUTSIDE;
	}
}
bool Solver::Polygon::onVertex(Point p) const {
	for (const auto& v: vertexes) {
		if ((v.x == p.x) && (v.y == p.y)) {
			return true;
		}
	}
	return false;
}
bool Solver::Polygon::onEdge(Point p) const {
	auto check_pair = [&](size_t from, size_t to) {
		if (isBetween(vertexes.at(from), vertexes.at(to), p)) {
			return isOnLine(vertexes.at(from), vertexes.at(to), p);
		} else {
			return false;
		}
	};
	for (size_t i = 0; i < vertexes.size() - 1; i++) {
		if (check_pair(i, i+1)) {
			return true;
		}
	}
	return check_pair(0, vertexes.size() - 1);
}
bool Solver::Polygon::isInside(Point p) const {
	auto on_right_side = [&](size_t _from, size_t _to) {
		Point from = vertexes.at(_from);
		Point to = vertexes.at(_to);
		float a = from.y - to.y;
		float b = to.x - from.x;
		float c = -1.0 * (a * from.x + b * from.y);
		return a * p.x + b * p.y + c < 0;
	};
	for (size_t i = 0; i < vertexes.size() - 1; i++) {
		if (!on_right_side(i, i + 1)) {
			return false;
		}
	}
	if (!on_right_side(vertexes.size() - 1 , 0)) {
		return false;
	}
	return true;
}
