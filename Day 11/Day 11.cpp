#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main() {
	std::fstream file("input.txt");
	std::string s;

	// Part 1 variables
	std::vector<std::string> space_unexpanded;
	std::vector<std::pair<int, int>> galaxies;

	// Part 2 variables
	std::vector<std::string> older_space;
	std::vector<int> row_breaks;
	std::vector<int> col_breaks;
	std::vector<std::pair<int, int>> older_galaxies;

	while (std::getline(file, s)) {
		if (s.find('#') == -1) {
			space_unexpanded.push_back(s);
			row_breaks.push_back(older_space.size());
		}
		space_unexpanded.push_back(s);
		older_space.push_back(s);
	}

	std::vector<std::string> space(space_unexpanded.size());

	for (int i = 0; i < space_unexpanded[0].size(); i++) {
		bool willAdd = true;
		for (int j = 0; j < space_unexpanded.size(); j++) {
			space[j].push_back(space_unexpanded[j][i]);
			if (space_unexpanded[j][i] == '#') willAdd = false;
		}
		if (willAdd) for (int j = 0; j < space.size(); j++) space[j].push_back('.');
		if (willAdd) col_breaks.push_back(i);
	}

	for (int i = 0, row = 0, col = 0; i < space.size(); i++) { // Getting the galaxies in Part 1
		for (int j = 0; j < space[0].size(); j++) {
			if (col_breaks[col] == j) col++;
			if (space[i][j] == '#') galaxies.push_back({i, j});
		}
	}

	for (int i = 0, row = 0, col = 0; i < older_space.size(); i++) { // Getting the galaxies in Part 2
		if (row_breaks[row] == i) row++;
		for (int j = 0; j < older_space[0].size(); j++) {
			if (col_breaks[col] == j) col++;
			if (older_space[i][j] == '#') older_galaxies.push_back({i+(row*999'999), j+(col*999'999)});
			// The numbers get multiplied by 999 999 because the expanded line already takes up one extra space
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