#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <stack>
#include <boost/algorithm/string.hpp>
#include <numeric>

using namespace std;
typedef long long int lli;

lli part_one(string data) {
	stack<char> ss;
	map<char, lli> mm = {
		{')', 3},
		{']', 57},
		{'}', 1197},
		{'>', 25137}
	};
	
	lli total = 0;
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == '(' || data[i] == '[' || data[i] == '{' || data[i] == '<') ss.push(data[i]);
		else {
			char top = ss.top();
			if (data[i] == ')') {
				if(!ss.empty() && top == '(') ss.pop();
				else {
					total += mm[data[i]];
					break;
				}
			}
			else if (data[i] == ']') {
				if(!ss.empty() && top == '[') ss.pop();
				else {total += mm[data[i]];
					break;
				}
			}
			else if (data[i] == '}') {
				if(!ss.empty() && top == '{') ss.pop();
				else {total += mm[data[i]];
					break;
				}
			}
			else {
				if(!ss.empty() && top == '<') ss.pop();
				else {
					total += mm[data[i]];
					break;
				}
			}

		}

	}
	return total;
}

lli part_two(string data) {
	stack<char> ss;
	map<char, lli> mm = {
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
				else {
					return 0;
				}
			}
			else if (data[i] == ']') {
				if(!ss.empty() && top == '[') ss.pop();
				else {
					return 0;
				}
			}
			else if (data[i] == '}') {
				if(!ss.empty() && top == '{') ss.pop();
				else {
					return 0;
				}
			}
			else {
				if(!ss.empty() && top == '<') ss.pop();
				else {
					return 0;
				}
			}

		}
	}

	lli total = 0;
	while (!ss.empty()) {
		char top = ss.top();
		total = total * 5 + mm[top];
		ss.pop();
	}
	return total;
}

int main() {
	lli partonetotal = 0;
	vector<lli> parttwo;
	for (string data; getline(cin, data);) {
		partonetotal += part_one(data);
		lli total = part_two(data);
		if (total) {
			parttwo.push_back(total);
		}
	}
	sort(parttwo.begin(), parttwo.end());

	cout << partonetotal << endl;
	cout << parttwo[parttwo.size()/2] << endl;

	return 0;
}
