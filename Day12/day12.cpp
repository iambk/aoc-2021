#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <cctype>
#include <boost/algorithm/string.hpp>

using namespace std;

bool isLower(string cave) {
	return islower(cave[0]);
}

int countPaths(map<string, vector<string> > graph, string source, string destination, set<string> lower_caves, bool twiceAllowed) {
	bool isStart = (source == "start");
	bool isEnd = (source == destination);
	bool isLowerCavesEmpty = lower_caves.size();
	bool isLowerCave = isLower(source);
	bool notAlreadyVisited = (lower_caves.find(source) != lower_caves.end());

	if (isEnd) return 1;
	if (isStart && isLowerCavesEmpty) return 0;
	if (isLowerCave && notAlreadyVisited && !twiceAllowed) return 0;
	if (isLowerCave && notAlreadyVisited && twiceAllowed) {
		if (twiceAllowed) twiceAllowed = false;
		else return 0;
	}

	if (isLower(source)) {
		lower_caves.insert(source);
	}

	int paths = 0;
	vector<string> caves = graph[source];
	for (int i = 0; i < caves.size(); i++) {
		paths += countPaths(graph, caves[i], destination, lower_caves, twiceAllowed);
	}

	return paths;
}



int part_one(map<string, vector<string> > graph) {
	set<string> lower_caves;
	return countPaths(graph, "start", "end", lower_caves, false);
}

int part_two(map<string, vector<string> > graph) {
	set<string> lower_caves;
	return countPaths(graph, "start", "end", lower_caves, true);
}

int main() {
	vector<string> input;
	map<string, vector<string> > graph;
	for (string data; getline(cin, data);) {
		boost::split(input, data, boost::is_any_of("-"));
		graph[input[0]].push_back(input[1]);
		graph[input[1]].push_back(input[0]);
	}

	cout << part_one(graph) << endl;
	cout << part_two(graph) << endl;

	return 0;
}
