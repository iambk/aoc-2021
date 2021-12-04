#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	freopen("input", "r", stdin);

	vector<int> input;

	for (string data; getline(cin, data); ) {
		input.push_back(stoi(data));
	}

	int count = 0, left = 0, right = 3, leftsum = 0, rightsum = 0;
	while (right < input.size()) {
		leftsum = input[left] + input[left + 1] + input[right - 1];
		rightsum = leftsum - input[left] + input[right];
		if (rightsum > leftsum) count++;
		left++;
		right++;
	}

	cout << count << endl;

	return 0;
}
