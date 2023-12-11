#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main() {
	std::fstream file("input.txt");
	std::string s;
	
	std::vector<std::string> space;
	std::vector<int> row_breaks;
	std::vector<int> col_breaks;

	// Part 1 variable
	std::vector<std::pair<int, int>> galaxies;

	// Part 2 variable
	std::vector<std::pair<int, int>> older_galaxies;
	
	while (std::getline(file, s)) {
		if (s.find('#') == -1) {
			row_breaks.push_back(space.size());
		}
		space.push_back(s);
	}


	for (int i = 0; i < space[0].size(); i++) {
		bool _break = true;
		for (int j = 0; j < space.size(); j++) {
			if (space[j][i] == '#') {
				_break = false;
				break;
			}
		}
		if (_break) col_breaks.push_back(i);
	}

	for (int i = 0, row = 0, col = 0; i < space.size(); i++) { // Getting the galaxies
		if (row_breaks[row] == i) row++;
		for (int j = 0; j < space[0].size(); j++) {
			if (col_breaks[col] == j) col++;
			if (space[i][j] == '#') {
				galaxies.push_back({i+row, j+col}); // Part 1
				older_galaxies.push_back({i+(row*999'999), j+(col*999'999)}); // Part 2
				// The numbers get multiplied by 999 999 because the expanded line already takes up one extra space
			}
		}
		col = 0;
	}

	int overall_distances = 0; // Part 1 distance
	long long older_distances = 0; // Part 2 distance

	for (int i = 0; i < galaxies.size(); i++) {
		std::pair<int, int> src = galaxies[i], older_src = older_galaxies[i];
		for (int j = i+1; j < galaxies.size(); j++) {
			std::pair<int, int> dest = galaxies[j], older_dest = older_galaxies[j];

			// Part 1 distance
			overall_distances += std::abs(src.first - dest.first);
			overall_distances += std::abs(src.second - dest.second);

			// Part 2 distance
			older_distances += std::abs(older_src.first - older_dest.first);
			older_distances += std::abs(older_src.second - older_dest.second);
		}
	}

	std::cout << overall_distances << '\n' << older_distances << '\n';
}