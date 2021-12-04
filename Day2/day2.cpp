#include <iostream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>

using namespace std;
typedef long long int lli;

int main() {
	string forward = "forward", down = "down", up = "up";
	lli depth = 0, position = 0, aim = 0;
	freopen("input", "r", stdin);

	for (string data; getline(cin, data); ) {
		vector<string> command;
		boost::split(command, data, boost::is_any_of(" "));

		lli value = stoi(command[1]);

		if (command[0].compare(forward) == 0) {
			position += value;
			depth += aim * value;
		}
		else if (command[0].compare(up) == 0) aim -= value;
		else aim += value;
	}

	cout << depth * position << endl;

	return 0;
}
