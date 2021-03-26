#include <iostream>
#include "gtest/gtest.h"
#include "misc.h"
#include <sstream>

using namespace std;

TEST(TestTime, Input1) {
	istringstream in("8:20 9:31");
	TimeSegment t;
	in >> t;
	EXPECT_EQ(t.start, 20);
	EXPECT_EQ(t.end, 91);
}
TEST(TestTime, Input2) {
	istringstream in("8:02 09:01");
	TimeSegment t;
	in >> t;
	EXPECT_EQ(t.start, 2);
	EXPECT_EQ(t.end, 61);
}

TEST(TestTime, Output) {
	TimeSegment t = { .start = 123, .end = 587 };
	{
		ostringstream out;
		out << t;
		EXPECT_EQ(out.str(), "10:03 17:47");
	}
	t.start = 60;
	t.end = 600;
	{
		ostringstream out;
		out << t;
		EXPECT_EQ(out.str(), "9:00 18:00");
	}
	t.start = 0;
	t.end = 720;
	{
		ostringstream out;
		out << t;
		EXPECT_EQ(out.str(), "8:00 20:00");
	}
}
TEST(TestCounter, _1) {
	istringstream inp("8:10 8:30");
	TimeSegment ts;
	inp >> ts;
	Counter cnt;
	cnt.AddVisitor(ts);
	ostringstream out;
	for (auto r: cnt.FindMostBusyTimes()) {
		out << r << "\n";
	}
	EXPECT_EQ(out.str(), "8:10 8:30\n");
}
TEST(TestCounter, _2) {
	istringstream inp("8:10 8:30\n8:30 8:45\n");
	Counter cnt;
	TimeSegment ts;
	while (inp >> ts) {
		cnt.AddVisitor(ts);
	}
	ostringstream out;
	for (auto r: cnt.FindMostBusyTimes()) {
		out << r << "\n";
	}
	EXPECT_EQ(out.str(), "8:10 8:45\n");
}

TEST(TestCounter, _3) {
	istringstream inp("8:10 8:30\n8:30 8:45\n8:01 8:12");
	Counter cnt;
	TimeSegment ts;
	while (inp >> ts) {
		cnt.AddVisitor(ts);
	}
	ostringstream out;
	for (auto r: cnt.FindMostBusyTimes()) {
		out << r << "\n";
	}
	EXPECT_EQ(out.str(), "8:10 8:12\n");
}
TEST(TestCounter, _4) {
	istringstream inp("8:10 8:30\n8:20 8:45\n8:01 8:15");
	Counter cnt;
	TimeSegment ts;
	while (inp >> ts) {
		cnt.AddVisitor(ts);
	}
	ostringstream out;
	for (auto r: cnt.FindMostBusyTimes()) {
		out << r << "\n";
	}
	EXPECT_EQ(out.str(), "8:10 8:15\n8:20 8:30\n");
}
TEST(TestCounter, _5) {
	istringstream inp("8:00 8:30\n8:15 8:45\n8:45 9:00\n8:30 9:00\n9:00 9:30\n9:10 9:20\n");
	Counter cnt;
	TimeSegment ts;
	while (inp >> ts) {
		cnt.AddVisitor(ts);
	}
	ostringstream out;
	for (auto r: cnt.FindMostBusyTimes()) {
		out << r << "\n";
	}
	EXPECT_EQ(out.str(), "8:15 9:00\n9:10 9:20\n");
}

int main(int argc, char *argv[]) {

	testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();;
}
