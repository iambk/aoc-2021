#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;

void returnCount(vector<string> input, int index, int minMax[]) {
	int zeroCount = 0, oneCount = 0;
	for (int i = 0; i < input.size(); i++) {
		if (input[i][index] == '0') {
			zeroCount++;
		}
		else {
			oneCount++;
		}
	}

	minMax[0] = zeroCount;
	minMax[1] = oneCount;
}

int main() {
	freopen("input", "r", stdin);

	vector<string> input;
	for (string data; getline(cin, data); ) {
		input.push_back(data);
	}

	int size = input[0].size(), minMax[2] = {0};
	string o2, co2;
	vector<string> o2input(input);
	vector<string> co2input(input);

	//O2
	int index = 0;
	while (index < size) {
		if (o2input.size() == 1) {
			o2.append(o2input[0].substr(index));
			break;
		}
		char max;
		returnCount(o2input, index, minMax);
		if (minMax[0] > minMax[1]) {
			max = '0';
			o2.push_back('0');
		}
		else {
			max = '1';
			o2.push_back('1');
		}
		vector<string>::iterator it = o2input.begin();
		while (it != o2input.end()) {
			string val = *it;
			if (val[index] != max) {
				it = o2input.erase(it);
			}
			else ++it;
		}
		index++;
	}

	//CO2
	index = 0;
	while (index < size) {
		if (co2input.size() == 1) {
			co2.append(co2input[0].substr(index));
			break;
		}
		char min;
		returnCount(co2input, index, minMax);
		if (minMax[0] <= minMax[1]) {
			min = '0';
			co2.push_back('0');
		}
		else if (minMax[1] < minMax[0]){
			min = '1';
			co2.push_back('1');
		}
		vector<string>::iterator it = co2input.begin();
		while (it != co2input.end()) {
			string val = *it;
			if (val[index] != min) {
				it = co2input.erase(it);
			}
			else ++it;
		}
		index++;
	}

	int o2rating = stoi(o2, nullptr, 2);
	int co2rating = stoi(co2, nullptr, 2);

	cout << o2rating * co2rating << endl;

	return 0;
}
