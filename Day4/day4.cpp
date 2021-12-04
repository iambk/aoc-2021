#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <boost/algorithm/string.hpp>

using namespace std;

bool isBingo(vector<vector<int> > board) {
	for (int i = 0; i < 5; i++) {
		int rowsum = 0;
		for (int j = 0; j < 5; j++) {
			rowsum += board[i][j];
		}
		if (rowsum == -5) return true;
	}

	for (int i = 0; i < 5; i++) {
		int colsum = 0;
		for (int j = 0; j < 5; j++) {
			colsum += board[j][i];
		}
		if (colsum == -5) return true;
	}

	return false;
}

int maxscore(vector<vector<int > > board, int num) {
	int score = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (board[i][j] != -1) score += board[i][j];
		}
	}
	return score * num;
}

int main() {
	string input;
	cin >> input;

	vector<string> numbers;
	boost::split(numbers, input, boost::is_any_of(","));

	fstream file("input", ios_base::in);

	vector<vector<vector<int> > > allboard;
	vector<int> row;
	vector<vector<int > > board;
	int num;
	while (file >> num) {
		row.push_back(num);

		if (row.size() == 5) {
			board.push_back(row);
			row.clear();
		}
		if (board.size() == 5) {
			allboard.push_back(board);
			board.clear();
		}
	}

	set<int> won;
	for (int it = 0; it < numbers.size(); it++) {
		int drawn = stoi(numbers[it]);
		for (int abi = 0; abi < allboard.size(); abi++) {
			for (int i = 0; i < 5; i++) {
				for (int j = 0; j < 5; j++) {
					if (drawn == allboard[abi][i][j]) {
						allboard[abi][i][j] = -1;
					}
				}
			}
			if (isBingo(allboard[abi])) {
				won.insert(abi);
				if (won.size() == allboard.size()) {
					cout << maxscore(allboard[abi], drawn) << endl;
					return 0;
				}
			}
		}
	}

	return 0;
}
