#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

static int size = 0;

bool islow(vector<vector<int> > input, int x, int y) {
	int up = INT_MAX, down = INT_MAX, left = INT_MAX, right = INT_MAX;
	if ((x - 1) >= 0) up = input[x - 1][y];
	if ((x + 1) < input.size()) down = input[x + 1][y];
	if ((y - 1) >= 0) left = input[x][y - 1];
	if ((y + 1) < input[x].size()) right = input[x][y + 1];

	int value = input[x][y];
	if ((value < up) && (value < down) && (value < right) && (value < left)) return true;
	return false;
}

void fill_dp_memo(vector<vector<int> > input, vector<vector<int> > &dp_memo) {
	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input[i].size(); j++) {
			dp_memo[i][j] = islow(input, i, j);
		}
	}
}


void traverse(vector<vector<int> > input, int x, int y) {
	static vector<vector<bool> > covered(input.size(), vector<bool>(input.size(), false));
	if (x < 0 || x == input.size() || y < 0 || y == input[x].size()) return;
	else if (input[x][y] == 9) return;
	else if (!covered[x][y]) {
		size++;
		covered[x][y] = true;
		traverse(input, x - 1, y);
		traverse(input, x + 1, y);
		traverse(input, x, y - 1);
		traverse(input, x, y + 1);
	}
}

int part_one(vector<vector<int> > input, vector<vector<int> > dp_memo, vector<pair<int, int> > &lows) {
	int riskcount = 0;

	for (int i = 0; i < dp_memo.size(); i++) {
		for (int j = 0; j < dp_memo[i].size(); j++) {
			if (dp_memo[i][j]) {
				lows.push_back(make_pair(i, j));
				riskcount += input[i][j] + 1;
			}
		}
	}

	return riskcount;
}

int part_two(vector<vector<int> > input, vector<vector<int> > dp_memo, vector<pair<int, int> > lows) {
	int total = 1;
	vector<int> sizes;

	vector<pair<int, int> >::iterator lit = lows.begin();
	for (; lit != lows.end(); lit++) {
		traverse(input, lit->first, lit->second);
		sizes.push_back(size);
		size = 0;
	}

	sort(sizes.begin(), sizes.end(), greater<int>());
	total *= sizes[0] * sizes[1] * sizes[2];

	return total;
}

int main() {
	vector<vector<int> > list;
	for (string data; getline(cin, data); ) {
		vector<int> v;
		for (int i = 0; i < data.size(); i++) {
			v.push_back(data[i] - '0');
		}
		list.push_back(v);
	}

	vector<vector<int> > dp_memo(list.size(), vector<int>(list[0].size()));
	fill_dp_memo(list, dp_memo);

	vector<pair<int, int> > lows;
	cout << part_one(list, dp_memo, lows) << endl;
	cout << part_two(list, dp_memo, lows) << endl;
}
