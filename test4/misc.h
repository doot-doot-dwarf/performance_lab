#ifndef _MY_MISC_H_
#define _MY_MISC_H_

#include <iostream>
#include <vector>
#include <fstream>
struct TimeSegment {
	size_t start, end;
};

std::ostream& operator << (std::ostream& out, const TimeSegment& ts);
std::istream& operator >> (std::istream& out, TimeSegment& ts);
bool operator == (const TimeSegment& lhs, const TimeSegment& rhs);
bool operator < (const TimeSegment& lhs, const TimeSegment& rhs);
class Counter {
	private:
		// время дискретно, можно не строить перекрывающиеся интервалы
		std::vector<size_t> count;
	public:
		void AddVisitor(TimeSegment time);
		Counter() : count((20 - 8) * 60 + 1, 0) {}
		void ReadData(std::ifstream& in);
		std::vector<TimeSegment>  FindMostBusyTimes () const;
};

#endif //_MY_MISC_H_
