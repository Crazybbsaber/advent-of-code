#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

// I basically rewrote everything for part 2

std::vector<std::string> engine;

int isNumber(char number) {
	return (number >= '0' && number <= '9');
}

int findNumber(std::pair<int, int> pos) {
	int number = 0;

	while (pos.second != -1 && isNumber(engine[pos.first][pos.second])) {
		pos.second--;
	}

	pos.second++;

	while (pos.second != engine[0].size() && isNumber(engine[pos.first][pos.second])) {
		number *= 10;
		number += (engine[pos.first][pos.second] - '0');
		pos.second++;
	}
	return number;
}

int main() {
	std::fstream file("input.txt");
	std::string s;
	std::vector<std::pair<int, int>> gears;

	int res = 0;

	while (std::getline(file, s)) {
		engine.push_back(s);
	}

	for (int row = 0; row < engine.size(); row++) {
		for (int i = 0; i < engine[row].size(); i++) {
			if (engine[row][i] == '*') {
				gears.push_back({row, i});
			}	
		}
	}

	for (std::pair<int, int> gear : gears) {
		int layer = 0;

		gear.first--;

		if (gear.first == -1) {
			gear.first++;
			layer++;
		}

		gear.second--;

		std::pair<int, int> gearnums;
		for (int i = layer; i < 3; i++) {
			for (int i = 0; i < 3; i++) {
				if ((gear.second != -1 || gear.second != engine[0].size()) && isNumber(engine[gear.first][gear.second])) {
					int number = findNumber(gear);
					if (gearnums.first == 0) gearnums.first = number;
					if (gearnums.second == 0 && (gearnums.first != number)) gearnums.second = number;
				}
				gear.second++;
			}
			gear.second -= 3;			
			gear.first++;
		}
		if (gearnums.second) {
			res += (gearnums.first * gearnums.second);
		}
	}

	std::cout << res << std::endl;
}