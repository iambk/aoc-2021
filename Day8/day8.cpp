#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <numeric>

using namespace std;

int part_one(vector<string> input) {
	int one = 2, four = 4, seven = 3, eight = 7;
	int onecount = 0, fourcount = 0, sevencount = 0, eightcount = 0;

	for (int i = input.size() - 1; i >= input.size() - 4; i--) {
		if (input[i].size() == one) onecount++;
		else if (input[i].size() == four) fourcount++;
		else if (input[i].size() == seven) sevencount++;
		else if (input[i].size() == eight) eightcount++;
	}

	return onecount + fourcount + sevencount + eightcount;
}

int part_two(vector<string> input) {
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

	map<char, int> frequency;
	string len2input, len3input, len4input, len7input;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < input[i].size(); j++) {
			frequency[input[i][j]]++;
		}
		if (input[i].size() == 2) len2input = input[i];
		else if (input[i].size() == 3) len3input = input[i];
		else if (input[i].size() == 4) len4input = input[i];
		else if (input[i].size() == 7) len7input = input[i];
	}

	map<char, char> char_mapping;
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

	if (char_mapping.find(len2input[0]) == char_mapping.end()) {
		char_mapping.insert(make_pair(len2input[0], 'c'));
	}
	else {
		char_mapping.insert(make_pair(len2input[1], 'c'));
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

	string output;
	for (int i = input.size() - 4; i < input.size(); i++) {
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
	vector<string> input;

	int part_one_total = 0;
	int part_two_total = 0;
	for (string data; getline(cin, data); ) {
		boost::split(input, data, boost::is_any_of(" "));

		part_one_total += part_one(input);
		part_two_total += part_two(input);
	}

	cout << part_one_total << endl;
	cout << part_two_total << endl;

	return 0;
}
