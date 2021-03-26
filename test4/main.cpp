#include <iostream>
#include <fstream>
#include "misc.h"

using namespace std;

int main(int argc, char **argv) {
	if (argc != 2) {
		exit(-1);
	}
	ifstream inp(argv[1], ios::in);
	Counter cnt;
	cnt.ReadData(inp);
	for (const auto interval : cnt.FindMostBusyTimes()) {
		cout << interval << '\n';
	}
	return 0;
}
