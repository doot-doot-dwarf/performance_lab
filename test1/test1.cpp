#include <iostream>
#include <iomanip>
#include <cstdint>
#include <fstream>
#include "test1.h"

using namespace std;


int main(int argc, char **argv) {
    if (argc != 2) {
        exit(-1);
    }
    ifstream file = ifstream(argv[1], std::ios::in);
    DataHolder data;
    // одно число влезает в 12 бит, значит 1000 влезут в 22
	data.ReadData(file);
    cout << setprecision(2) << fixed << data.Process() << "\n";
    return 0;
}
