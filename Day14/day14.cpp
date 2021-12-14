#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <cstdlib>
#include <boost/algorithm/string.hpp>

using namespace std;

void updatePairsAndCount(map<string, long int> &pairs, map<char, long int> &count, string rule, long int times, map<string, string> rules) {
	string appendValue = rules.find(rule)->second;
	count[appendValue[0]] += times;
	string left = rule.substr(0, 1) + appendValue;
	string right = appendValue + rule.substr(1, 1);
	pairs[rule] -= times;
	pairs[left] += times;
	pairs[right] += times;
}

long int part_one(string polymer, map<string, string> rules, int times) {
	map<string, long int> pairs;
	map<char, long int> count;

	for (int i = 0; i < polymer.size() - 1; i++) {
		pairs[polymer.substr(i, 2)]++;
		count[polymer[i]]++;
		if (i == polymer.size() - 2) count[polymer[i + 1]]++;
	}

	for (int i = 1; i <= times; i++) {
		map<string, long int>::iterator it = pairs.begin();
		vector<pair<string, long int> > rule;
		while (it != pairs.end()) {
			if (it->second) {
				rule.push_back(make_pair(it->first, it->second));
			}
			it++;
		}
		for (int i = 0; i < rule.size(); i++) {
			updatePairsAndCount(pairs, count, rule[i].first, rule[i].second, rules);
		}
	}

	long int max = LONG_MIN, min = LONG_MAX;
	map<char, long int>::iterator cit = count.begin();
	for (; cit != count.end(); cit++) {
		if (cit->second > max) max = cit->second;
		if (cit->second < min) min = cit->second;
	}
	return max - min;
}

int main() {
	string polymer;
	cin >> polymer;

	map<string, string> rules;
	vector<string> input;
	for (string data; getline(cin, data); ) {
		boost::split(input, data, boost::is_any_of(" "));
		rules.insert(make_pair(input[0], input[2]));
	}

	cout << part_one(polymer, rules, 10) << endl;
	cout << part_one(polymer, rules, 40) << endl;
	return 0;
}
