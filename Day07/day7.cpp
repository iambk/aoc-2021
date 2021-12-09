#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <numeric>

using namespace std;

int find_median(vector<int> list) {
	int size = list.size(), median;

	if (size % 2 != 0) {
		nth_element(list.begin(), list.begin() + size / 2, list.end());
		median = list[size / 2];
	}
	else {
		nth_element(list.begin(), list.begin() + size / 2, list.end());
		nth_element(list.begin(), list.begin() + (size - 1) / 2, list.end());
		median = (list[size / 2] + list[(size - 1) / 2]);
		median /= 2;
	}

	return median;
}

int find_average(vector<int> list) {
	int sum = accumulate(list.begin(), list.end(), 0);

	return sum / list.size();
}

int part_one(vector<int> list, int median) {
	int minfuel = 0;
	for (int i = 0; i < list.size(); i++) {
		int diff = abs(list[i] - median);
		minfuel += diff;
	}
	return minfuel;
}

int part_two(vector<int> list, int average) {
	int minfuel = INT_MAX;
	for (int possible = average - 1; possible <= average + 1; possible++) {
		int fuelcost = 0;
		for (int i = 0; i < list.size(); i++) {
			int diff = abs(list[i] - possible);
			int diffsquare = ((diff * (diff + 1)) / 2);
			fuelcost += diffsquare;
		}
		if (fuelcost < minfuel) minfuel = fuelcost;
	}

	return minfuel;
}

int main() {
	vector<string> input;

	for (string data; getline(cin, data); ) {
		boost::split(input, data, boost::is_any_of(","));
	}

	vector<int> crab_hp(input.size());
	for (int i = 0; i < input.size(); i++) {
		crab_hp[i] = stoi(input[i]);
	}
	
	int median = find_median(crab_hp);
	int avg = find_average(crab_hp);

	cout << part_one(crab_hp, median) << endl;
	cout << part_two(crab_hp, avg) << endl;

	return 0;
}
