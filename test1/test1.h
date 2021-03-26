#ifndef _TEST1_H_
#define _TEST1_H_

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <fstream>

struct Result {
	float precentile_50 = 0.0;
	float precentile_90 = 0.0;
	float max = 0.0;
	float min = 0.0;
	float average = 0.0;

	friend std::ostream& operator << (std::ostream& out, const Result& v) {
		out << v.precentile_90 << "\n" << v.precentile_50 << "\n" <<
			v.max << "\n" << v.min << "\n" << v.average;
		return out;
	}
};

class DataHolder {
private:
	std::vector<int16_t>  data;
	float ComputePercentile(int percentile) const {
		float rank = ((float)percentile / 100.0) * ((float)data.size() - 1.0);
		size_t ind = std::floor(rank);
		return data[ind] + (rank - (float)ind) * (data[ind + 1] - data[ind]);
	}
	int32_t Accumulate() {
		int32_t res = 0;
		for (auto val : data) {
			res += (int32_t) val;
		}
		return res;
	}
    void Add(int16_t val) {
        data.push_back(val);
    }
public:
    DataHolder() {
        data.reserve(500);
    }
    Result Process()  {
        Result res;
        if (data.size() != 0) {
			std::sort(data.begin(), data.end());
			res.min = (float) data.at(0);
			res.max = (float) data.back();
			res.average = (float) Accumulate() / (float) data.size();
			res.precentile_90 = ComputePercentile(90);
			res.precentile_50 = ComputePercentile(50);
        }
        return res;
    }
	void ReadData(std::ifstream& file) {
		int16_t val;
		while (file >> val) {
			Add(val);
		}
	}
};
#endif // _TEST1_H_

