#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>

using namespace std;

int part_one(string data) {
	stack<char> ss;
	map<char, int> mm = {
		{')', 3},
		{']', 57},
		{'}', 1197},
		{'>', 25137}
	};
	
	int total = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '(' || data[i] == '[' || data[i] == '{' || data[i] == '<') ss.push(data[i]);
		else {
			char top = ss.top();
			if (data[i] == ')') {
				if(!ss.empty() && top == '(') ss.pop();
				else return mm[data[i]];
			}
			else if (data[i] == ']') {
				if(!ss.empty() && top == '[') ss.pop();
				else return mm[data[i]];
			}
			else if (data[i] == '}') {
				if(!ss.empty() && top == '{') ss.pop();
				else return mm[data[i]];
			}
			else {
				if(!ss.empty() && top == '<') ss.pop();
				else return mm[data[i]];
			}
		}
	}

	return total;
}

long int part_two(string data) {
	stack<char> ss;
	map<char, int> mm = {
		{'(', 1},
		{'[', 2},
		{'{', 3},
		{'<', 4}
	};
	
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '(' || data[i] == '[' || data[i] == '{' || data[i] == '<') ss.push(data[i]);
		else {
			char top = ss.top();
			if (data[i] == ')') {
				if(!ss.empty() && top == '(') ss.pop();
				else return 0;
			}
			else if (data[i] == ']') {
				if(!ss.empty() && top == '[') ss.pop();
				else return 0;
			}
			else if (data[i] == '}') {
				if(!ss.empty() && top == '{') ss.pop();
				else return 0;
			}
			else {
				if(!ss.empty() && top == '<') ss.pop();
				else return 0;
			}
		}
	}

	long int total = 0;
	while (!ss.empty()) {
		char top = ss.top();
		total = static_cast<long int>(total) * 5 + mm[top];
		ss.pop();
	}
	return total;
}

int main() {
	int part_one_total = 0;
	long int part_two_score;
	vector<long int> part_two_scores;
	for (string data; getline(cin, data);) {
		part_one_total += part_one(data);
		part_two_score = part_two(data);
		if (part_two_score) {
			part_two_scores.push_back(part_two_score);
		}
	}
	sort(part_two_scores.begin(), part_two_scores.end());

	cout << part_one_total << endl;
	cout << part_two_scores[part_two_scores.size()/2] << endl;

	return 0;
}
