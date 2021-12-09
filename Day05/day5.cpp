#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <boost/algorithm/string.hpp>

using namespace std;

void count_hv_points(map<pair<int, int>, int> &points, int x1, int x2, int y1, int y2) {
	if (x1 == x2) {
		int beg = min(y1, y2), end = max(y1, y2);
		for (int i = beg; i <= end; i++) {
			points[make_pair(x1, i)]++;
		}
	}
	else if (y1 == y2) {
		int beg = min(x1, x2), end = max(x1, x2);
		for (int i = beg; i <= end; i++) {
			points[make_pair(i, y1)]++;
		}
	}
}

void count_diag_points(map<pair<int, int>, int> &points, int x1, int x2, int y1, int y2) {
	if (abs(y2 - y1) == abs(x2 - x1)) {
		int xiterator = x1, yiterator = y1;
		int xstep, ystep;

		if (x1 < x2) xstep = 1;
		else xstep = -1;

		if (y1 < y2) ystep = 1;
		else ystep = -1;

		int diff = abs(y2 - y1) + 1;
		while (diff--) {
			points[make_pair(xiterator, yiterator)]++;
			xiterator += xstep;
			yiterator += ystep;
		}
	}
}

int find_overlap(map<pair<int, int>, int> &points) {
	int overlap = 0;
	map<pair<int, int>, int>::iterator it = points.begin();
	for (; it != points.end(); it++) {
		if (it->second >= 2) overlap++;
	}
	return overlap;
}


int main() {
	map<pair<int, int>, int> points;
	for (string data; getline(cin, data); ) {
		vector<string> line;
		boost::split(line, data, boost::is_any_of(" "));

		boost::trim(line[0]);
		boost::trim(line[2]);

		vector<string> from, to;
		boost::split(from, line[0], boost::is_any_of(","));
		boost::split(to, line[2], boost::is_any_of(","));

		int x1 = stoi(from[0]), y1 = stoi(from[1]);
		int x2 = stoi(to[0]), y2 = stoi(to[1]);

		count_hv_points(points, x1, x2, y1, y2);
		count_diag_points(points, x1, x2, y1, y2);
	}

	cout << find_overlap(points) << endl;
	
	return 0;
}
