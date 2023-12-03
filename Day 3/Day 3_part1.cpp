#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main() {
	std::fstream file("input.txt");
	std::string s;
	std::vector<std::string> engine;
	int res = 0;

	while (std::getline(file, s)) {
		engine.push_back(s);
	}

	int number = 0;
	bool isPart = false;
	for (int row = 0; row < engine.size(); row++) {
		for (int i = 0; i < engine[row].size(); i++) {
			if (!((engine[row][i] >= '0') && (engine[row][i] <= '9')) && !number) continue;
			if (!((engine[row][i] >= '0') && (engine[row][i] <= '9')) && number) {
				if (isPart) {
					res += number;
					isPart = false;
				}
				number = 0;
				continue;
			}
			
			number *= 10;
			number += (engine[row][i] - '0');

			// Detecting if the number is a part
			if (row && !isPart) {
				if ((engine[row-1][i] != 46 && !((engine[row-1][i] >= '0') && (engine[row-1][i] <= '9'))) ||
					((i + 1) != engine[row].size() && engine[row-1][i+1] != 46 && !((engine[row-1][i+1] >= '0') && (engine[row-1][i+1] <= '9'))) ||
					(i && engine[row-1][i-1] != 46 && !((engine[row-1][i-1] >= '0') && (engine[row-1][i-1] <= '9')))) {

					isPart = true;
					continue;
				}

			}
			if ((row + 1) != engine.size() && !isPart) {
				if ((engine[row+1][i] != 46 && !((engine[row+1][i] >= '0') && (engine[row+1][i] <= '9'))) ||
					((i + 1) != engine[row].size() && engine[row+1][i+1] != 46 && !((engine[row+1][i+1] >= '0') && (engine[row+1][i+1] <= '9'))) ||
					(i && engine[row+1][i-1] != 46 && !((engine[row+1][i-1] >= '0') && (engine[row+1][i-1] <= '9')))) {

					isPart = true;
					continue;
				}
			}
			if (((i + 1) != engine[row].size() && engine[row][i+1] != 46 && !((engine[row][i+1] >= '0') && (engine[row][i+1] <= '9'))) ||
				(i && engine[row][i-1] != 46 && !((engine[row][i-1] >= '0') && (engine[row][i-1] <= '9')))) {

				isPart = true;
				continue;
			}			
		}
		if (number) {
			if (isPart) {
					res += number;
					isPart = false;
				}
			number = 0;
		}
	}

	std::cout << res << std::endl;
}