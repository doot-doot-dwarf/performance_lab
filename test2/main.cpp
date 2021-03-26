#include <ios>
#include <iostream>
#include <fstream>
#include "test2.h"

using namespace std;

int main(int argc, char *argv[]) {
	if (argc != 3) {
		exit(-1);
	}
	ifstream polygon = ifstream(argv[1], std::ios::in);
	Solver s(polygon);
	ifstream points = ifstream(argv[2], std::ios::in);
	for (Point query; points >> query;) {
		cout << s.Probe(query) << "\n";
	}
	return 0;
}
