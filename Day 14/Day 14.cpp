#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Part 2 doesn't work yet

void cycle(std::vector<std::string> &mirror) {
	for (int i = 1; i < mirror.size(); i++) {
		for (int j = 0; j < mirror[0].size(); j++) {
			if (mirror[i][j] == 'O') {
				for (int k = i-1; k >= 0; k--) {
					if (!k && mirror[0][j] == '.') {
						mirror[i][j] = '.';
						mirror[0][j] = 'O';
						continue;
					}
					if (mirror[k][j] != '.') {
						mirror[i][j] = '.';
						mirror[k+1][j] = 'O';
						break;
					}
				}
			}
		}
	}
	for (int j = 1; j < mirror[0].size(); j++) {
		for (int i = 0; i < mirror.size(); i++) {
			if (mirror[i][j] == 'O') {
				for (int k = j-1; k >= 0; k--) {
					if (!k && mirror[i][0] == '.') {
						mirror[i][j] = '.';
						mirror[i][0] = 'O';
						continue;
					}
					if (mirror[i][k] != '.') {
						mirror[i][j] = '.';
						mirror[i][k+1] = 'O';
						break;
					}
				}
			}
		}
	}
	for (int i = mirror.size()-1; i >= 0; i--) {
		for (int j = mirror[0].size()-1; j >= 0; j--) {
			if (mirror[i][j] == 'O') {
				for (int k = i+1; k < mirror.size(); k++) {
					if (k+1 == mirror.size() && mirror[k][j] == '.') {
						mirror[i][j] = '.';
						mirror[k][j] = 'O';
						continue;
					}
					if (mirror[k][j] != '.') {
						mirror[i][j] = '.';
						mirror[k-1][j] = 'O';
						break;
					}
				}
			}
		}
	}
	for (int j = mirror[0].size()-1; j >= 0 ; j--) {
		for (int i = mirror.size()-1; i >= 0; i--) {
			if (mirror[i][j] == 'O') {
				for (int k = j+1; k < mirror[0].size(); k++) {
					if (k+1 == mirror[0].size() && mirror[i][k] == '.') {
						mirror[i][j] = '.';
						mirror[i][k] = 'O';
						continue;
					}
					if (mirror[i][k] != '.') {
						mirror[i][j] = '.';
						mirror[i][k-1] = 'O';
						break;
					}
				}
			}
		}
	}
}

int main() {
	std::fstream file("test.txt");
	std::string s;
	std::vector<std::string> rocks;

	while (std::getline(file, s)) {
		rocks.push_back(s);
	}

	std::vector<std::string> mirror = rocks;

	// Pushing the rocks north
	for (int i = 1; i < rocks.size(); i++) {
		for (int j = 0; j < rocks[0].size(); j++) {
			if (rocks[i][j] == 'O') {
				for (int k = i-1; k >= 0; k--) {
					if (!k && rocks[0][j] == '.') {
						rocks[i][j] = '.';
						rocks[0][j] = 'O';
						continue;
					}
					if (rocks[k][j] != '.') {
						rocks[i][j] = '.';
						rocks[k+1][j] = 'O';
						break;
					}
				}
			}
		}
	}

	// Getting the load

	int load = 0;
	for (int i = 0; i < rocks.size(); i++) {
		load += (std::count(rocks[i].begin(), rocks[i].end(), 'O') * (rocks.size()-i));
	}

	std::cout << load << '\n';

	// Part 2

	int last_load = 0, same_counter = 0;
	std::vector<int> rolls;

	for (int i = 0; i < 1'000'000'000; i++) {
	// for (int i = 0; i < 3; i++) {
		cycle(mirror);

		load = 0;
		for (int i = 0; i < mirror.size(); i++) {
			load += (std::count(mirror[i].begin(), mirror[i].end(), 'O') * (mirror.size()-i));
		}

		rolls.push_back(load);

		for (int i = 1; i * 2 < rolls.size(); i++) {
			std::vector<int> one(i), two(i);
			std::copy(rolls.end()-i, rolls.end()-1, one.begin());
			std::copy(rolls.end()-(i*2), rolls.end()-1-i, two.begin());
			for (int i : one) std::cout << i << ' ';
			std::cout << '\n';
			for (int i  : two) std::cout << i << ' ';
			std::cout << '\n';
			if (one == two) break;
		}
	}



	std::cout << load << '\n';
}