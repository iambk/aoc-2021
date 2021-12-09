#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <numeric>

using namespace std;

int part_one(vector<string> input) {
	int count = 0, n = input.size();
	for (int i = n - 4; i < n; i++) {
		int size = input[i].size();
		if (size == 2 || size == 3 || size == 4 || size == 7) count++;
	}

	return count;
}

void decode_and_map_signal(vector<string> input, map<char, char> &char_mapping) {
	map<char, int> frequency;
	string len2input, len3input, len4input, len7input;
	for (int i = 0; i < 10; i++) {
		int size = input[i].size();
		for (int j = 0; j < size; j++) {
			frequency[input[i][j]]++;
		}
		if (size == 2) len2input = input[i];
		else if (size == 3) len3input = input[i];
		else if (size == 4) len4input = input[i];
		else if (size == 7) len7input = input[i];
	}

	map<char, int>::iterator it = frequency.begin();
	for (; it != frequency.end(); it++) {
		if (it->second == 4) {
			char_mapping.insert(make_pair(it->first, 'e'));
		}
		else if (it->second == 6) {
			char_mapping.insert(make_pair(it->first, 'b'));
		}
		else if (it->second == 9) {
			char_mapping.insert(make_pair(it->first, 'f'));
		}
	}

	for (int i = 0; i < 2; i++) {
		if (char_mapping.find(len2input[i]) == char_mapping.end()) {
			char_mapping.insert(make_pair(len2input[i], 'c'));
			break;
		}
	}

	for (int i = 0; i < 3; i++) {
		if (char_mapping.find(len3input[i]) == char_mapping.end()) {
			char_mapping.insert(make_pair(len3input[i], 'a'));
			break;
		}
	}

	for (int j = 0; j < 4; j++) {
		if (char_mapping.find(len4input[j]) == char_mapping.end()) {
			char_mapping.insert(make_pair(len4input[j], 'd'));
			break;
		}
	}

	for (int j = 0; j < 7; j++) {
		if (char_mapping.find(len7input[j]) == char_mapping.end()) {
			char_mapping.insert(make_pair(len7input[j], 'g'));
			break;
		}
	}
}

int part_two(vector<string> input, map<string, char> digit_mapping) {
	map<char, char> char_mapping;
	decode_and_map_signal(input, char_mapping);

	string output;
	int size = input.size();
	for (int i = size - 4; i < size; i++) {
		string num;
		for (int j = 0; j < input[i].size(); j++) {
			num.push_back(char_mapping[input[i][j]]);
		}
		sort(num.begin(), num.end());
		output.push_back(digit_mapping[num]);
	}

	return stoi(output);
}

int main() {
	map<string, char> digit_mapping = {
		{"abcefg", '0'},
		{"cf", '1'},
		{"acdeg", '2'},
		{"acdfg", '3'},
		{"bcdf", '4'},
		{"abdfg", '5'},
		{"abdefg", '6'},
		{"acf", '7'},
		{"abcdefg", '8'},
		{"abcdfg", '9'}
	};

	vector<string> input;

	int part_one_total = 0, part_two_total = 0;
	for (string data; getline(cin, data); ) {
		boost::split(input, data, boost::is_any_of(" "));

		part_one_total += part_one(input);
		part_two_total += part_two(input, digit_mapping);
	}

	cout << part_one_total << endl;
	cout << part_two_total << endl;

	return 0;
}
