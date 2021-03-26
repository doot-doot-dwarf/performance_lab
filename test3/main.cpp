#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;
const static size_t cashier_desk_num = 5;
// а ведь можно сделать проще, простым двумерным массивом, без выкрутасов
struct Data {
	vector<float> v;
	void Add(float val) {
		v.push_back(val);
	}
};
struct Solver {
	vector<Data> holder;
	void Add(Data&& val) {
		holder.push_back(val);
	}
	string Answer() {
		size_t max_pos = 0;
		float max = 0;

		for (size_t segment = 0; segment < holder[0].v.size(); ++segment) {
			float curr_sum = 0;
			for (size_t cashier_desk = 0; cashier_desk < holder.size(); ++cashier_desk) {
				curr_sum += holder[cashier_desk].v[segment];
			}
			if (curr_sum > max) {
				max = curr_sum;
				max_pos = segment;
			}
		}
		return to_string(max_pos + 1);
	}
};

vector<string> GetFileNames(const string& base, char sep, size_t num) {
	vector<string> res;
		for (size_t i = 0; i < num; ++i) {
			ostringstream s;
			s << base << sep << "Cash" << to_string(i + 1) << ".txt";
			res.push_back(s.str());
		}
		return res;
}

Solver ReadFiles(const string& _dirname) {
	Solver res;
#ifdef __linux__
	char sep = '/';
#elif _WIN32
	char sep = '\\';
#endif
	string dirname = _dirname;
	if (dirname.back() == sep) {
		dirname.erase(prev(dirname.end()));
	}
	cerr << dirname << "\n";
	for (const auto& name : GetFileNames(dirname, sep, cashier_desk_num)) {
		ifstream file(name, std::ios::in);
		Data t;
		for (float num; file >> num;) {
			t.Add(num);
		}
		res.Add(move(t));
	}
	return res;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		exit(-1);
	}
	auto broker = ReadFiles(string(argv[1]));
	cout << broker.Answer() << endl;
	return 0;
}
