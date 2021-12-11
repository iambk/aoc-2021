#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

int part_one(string data, map<char, char> character_matcher) {
	stack<char> syntax_checker;
	map<char, int> scores = {
		{')', 3},
		{']', 57},
		{'}', 1197},
		{'>', 25137}
	};
	
	for (int i = 0; i < data.size(); i++) {
		map<char, char>::iterator it = character_matcher.find(data[i]);
		if (it == character_matcher.end()) {
			syntax_checker.push(data[i]);
		}
		else if (!syntax_checker.empty() && (it->second == syntax_checker.top())) {
			syntax_checker.pop();
		}
		else return scores[data[i]];
	}

	return 0;
}

long int part_two(string data, map<char, char> character_matcher) {
	stack<char> syntax_checker;
	map<char, int> scores = {
		{'(', 1},
		{'[', 2},
		{'{', 3},
		{'<', 4}
	};

	for (int i = 0; i < data.size(); i++) {
		map<char, char>::iterator it = character_matcher.find(data[i]);
		if (it == character_matcher.end()) {
			syntax_checker.push(data[i]);
		}
		else if (!syntax_checker.empty() && (it->second == syntax_checker.top())) {
			syntax_checker.pop();
		}
		else return 0;
	}

	long int total = 0;
	while (!syntax_checker.empty()) {
		char top = syntax_checker.top();
		total = static_cast<long int>(total) * 5 + scores[top];
		syntax_checker.pop();
	}
	return total;
}

int main() {
	map<char, char> character_matcher = {
		{')', '('},
		{']', '['},
		{'}', '{'},
		{'>', '<'}
	};

	int part_one_total = 0;
	long int part_two_score;
	vector<long int> part_two_scores;
	for (string data; getline(cin, data);) {
		part_one_total += part_one(data, character_matcher);
		part_two_score = part_two(data, character_matcher);
		if (part_two_score) {
			part_two_scores.push_back(part_two_score);
		}
	}
	sort(part_two_scores.begin(), part_two_scores.end());

	cout << part_one_total << endl;
	cout << part_two_scores[part_two_scores.size() / 2] << endl;

	return 0;
}
