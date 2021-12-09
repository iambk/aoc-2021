#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
typedef long long int lli;
const lli P1SIZE = 80;
const lli P2SIZE = 256;

lli find_fish(vector<lli> pond, lli size) {
	for (lli i = 1; i <= size; i++) {
		rotate(pond.begin(), pond.begin() + 1, pond.end());

		pond[6] += pond[8];
	}

	lli fishes = 0;
	for (lli i = 0; i < 9; i++) fishes += pond[i];

	return fishes;
}

int main() {

	for (string data; getline(cin, data); ) {
		vector<string> line;
		boost::split(line, data, boost::is_any_of(","));

		vector<lli> pond(9, 0);
		for (lli i = 0; i < line.size(); i++) {
			pond[stoi(line[i])]++;
		}

		cout << find_fish(pond, P1SIZE) << endl;
		cout << find_fish(pond, P2SIZE) << endl;

	}

	return 0;
}
