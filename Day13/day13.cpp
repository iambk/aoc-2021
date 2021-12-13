#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <cstdlib>

using namespace std;

set<pair<int, int> > fold(set<pair<int, int> > indices, char direction, int foldindex) {
	set<pair<int, int> > newindices;

	set<pair<int, int> >::iterator it = indices.begin();
	while(it != indices.end()) {
		int x = it->first, y = it->second;
		if (direction == 'y') {
			int diff = abs(foldindex - x);
			int overlapx = min(foldindex - diff, foldindex + diff);
			newindices.insert(make_pair(overlapx, y));
		}
		else {
			int diff = abs(foldindex - y);
			int overlapy = min(foldindex - diff, foldindex + diff);
			newindices.insert(make_pair(x, overlapy));
		}
		it++;
	}

	return newindices;
}

int part_one(set<pair<int, int> > &indices, vector<pair<char, int> > folds, int times) {
	for (int i = 0; i < times; i++) {
		char direction = folds[i].first;
		int foldindex = folds[i].second;

		indices = fold(indices, direction, foldindex);
	}

	return indices.size();
}

void part_two(set<pair<int, int> > indices, vector<pair<char, int> > folds, int times) {
	part_one(indices, folds, times);

	int xmax = 0, ymax = 0;
	set<pair<int, int> >::iterator it = indices.begin();
	for (; it != indices.end(); it++) {
		if (it->first > xmax) xmax = it->first;
		if (it->second > ymax) ymax = it->second;
	}
	
	for (int i = 0; i <= xmax; i++) {
		for (int j = 0; j <= ymax; j++) {
			if (indices.find(make_pair(i, j)) != indices.end()) {
				cout << "#";
			}
			else cout << " ";
		}
		cout << endl;
	}
}

int main() {
	vector<string> input;
	set<pair<int, int> >indices;
	vector<pair<char, int> > folds;
	int xmax = 0, ymax = 0;
	for (string data; getline(cin, data);) {
		boost::split(input, data, boost::is_any_of(","));

		if (input[0] == "x" || input[0] == "y") {
			folds.push_back(make_pair(input[0][0], stoi(input[1])));
		}
		else {
			int input1 = stoi(input[1]);
			int input0 = stoi(input[0]);
			indices.insert(make_pair(input1, input0));
			if (input1 > xmax) xmax = input1;
			if (input0 > ymax) ymax = input0;
		}
	}

	cout << part_one(indices, folds, 1) << endl;
	part_two(indices, folds, folds.size());

	return 0;
}
