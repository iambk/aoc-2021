#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <boost/algorithm/string.hpp>

using namespace std;

bool isValid(int size, int x, int y) {
	if (x < 0 || x == size || y < 0 || y == size) return false;
	return true;
}

void flash(vector<vector<int> > &input, int x, int y) {
	int size = input.size();
	if (isValid(size, x - 1, y)) input[x - 1][y]++;
	if (isValid(size, x + 1, y)) input[x + 1][y]++;
	if (isValid(size, x, y - 1)) input[x][y - 1]++;
	if (isValid(size, x, y + 1)) input[x][y + 1]++;
	if (isValid(size, x - 1, y - 1)) input[x - 1][y - 1]++;
	if (isValid(size, x - 1, y + 1)) input[x - 1][y + 1]++;
	if (isValid(size, x + 1, y + 1)) input[x + 1][y + 1]++;
	if (isValid(size, x + 1, y - 1)) input[x + 1][y - 1]++;
}

int step(vector<vector<int> > &input) {
	int size = input.size(), flashes = 0;
	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			input[x][y]++;
		}
	}

	vector<vector<bool> > alreadyFlashed(size, vector<bool>(size, false));
	bool flashable = true;
	while (flashable) {
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				if (input[x][y] > 9 && !alreadyFlashed[x][y]) {
					alreadyFlashed[x][y] = true;
					flash(input, x, y);
					flashes++;
				}
			}
		}
		flashable = false;
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				if (input[x][y] > 9 && !alreadyFlashed[x][y]) {
					flashable = true;
					break;
				}
			}
			if (flashable) break;
		}
	}

	for (int x = 0; x < size; x++) {
		for (int y = 0; y < size; y++) {
			if (alreadyFlashed[x][y]) input[x][y] = 0;
		}
	}

	return flashes;
}

int part_one(vector<vector<int> > input, int steps) {
	int flashes = 0, size = input.size();
	for (int i = 1; i <= steps; i++) {
		flashes += step(input);
	}

	return flashes;
}

int part_two(vector<vector<int> > input) {
	int size = input.size();
	for (int i = 1; ; i++) {
		step(input);

		bool allZero = true;
		for (int x = 0; x < size; x++) {
			for (int y = 0; y < size; y++) {
				if (input[x][y]) {
					allZero = false;
					break;
				}
			}
			if (!allZero) break;
		}
		if (allZero) return i;
	}

	return -1;
}

int main() {
	vector<vector<int> > input;
	for (string data; getline(cin, data); ) {
		vector<int> row;
		for (int i = 0; i < data.size(); i++) {
			row.push_back(data[i] - '0');
		}
		input.push_back(row);
	}
	
	cout << part_one(input, 100) << endl;
	cout << part_two(input) << endl;

	return 0;
}
