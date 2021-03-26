#include <iomanip>
#include <string>
#include <cassert>
#include "misc.h"

using namespace std;

ostream& operator << (ostream& out, const TimeSegment& ts) {
	char default_filler = out.fill();
	out.fill('0');
	size_t start = ts.start + 8 * 60;
	size_t end = ts.end + 8 * 60;
	out << start / 60 << ":" << setw(2) <<  start % 60 << " "
			<< end / 60 << ":" << setw(2) << end % 60;
	out.fill(default_filler);
	return out;
}
std::istream& operator >> (std::istream& in, TimeSegment& ts) {
	int hour, minute;
	in >> hour;
	in.ignore(1);
	in >> minute;
	{
		assert(hour < 21 && hour > 7);
		assert(minute >= 0 && minute < 61);
	}
	ts.start = (hour - 8) * 60 + minute;
	in >> hour;
	in.ignore(1);
	in >> minute;
	{
		assert(hour < 21 && hour > 7);
		assert(minute >= 0 && minute < 61);
	}
	ts.end = (hour - 8) * 60 + minute;
	return in;
}
bool operator == (const TimeSegment& lhs, const TimeSegment& rhs) {
	return lhs.start == rhs.start && rhs.end == lhs.end;
}
bool operator < (const TimeSegment& lhs, const TimeSegment& rhs) {
	return lhs.start < rhs.start;
}
void Counter::AddVisitor(TimeSegment ts) {
	for (size_t pos = ts.start; pos < ts.end; ++pos) {
		++count[pos];
	}
}
void Counter::ReadData(ifstream& in) {
	for (TimeSegment t; in >> t;) {
		AddVisitor(t);
	}
}
vector<TimeSegment> Counter::FindMostBusyTimes() const {
	vector<TimeSegment> res;
	// первый проход
	size_t max = 0;
	for (size_t pos = 0; pos < count.size(); ++pos) {
		if (count[pos] > max) {
			max = count[pos]; 
		}
	}
	// второй проход
	for (size_t pos = 0; pos < count.size(); ++pos) {
		if (count[pos] == max) {
			size_t start = pos;
			// то, что мы проглотим один элемент не страшно
			// группы разделены по крайней мере одним элементом
			while (count[pos] == max) {
				++pos;
			}
			res.push_back({.start = start, .end = pos});
		}
	}
	return res;
}
