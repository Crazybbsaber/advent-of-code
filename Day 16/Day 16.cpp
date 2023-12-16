#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

std::unordered_set<int> visited;
std::unordered_set<int> dir_visited;

int hash(std::pair<int, int> pair, int n) {
	return (pair.first*n+pair.second);
}

int dir_hash(int x, int y, int n, int dir) {
	return ((x*(n*4))+(y+dir*n));
}

void beam(std::vector<std::string> &grid, int x, int y, int dir) {
	while (true) {
		if (x < 0 || y < 0) break;
		if (x == grid.size() || y == grid[0].size()) break;
		if (dir_visited.find(dir_hash(x, y, grid.size(), dir)) != dir_visited.end()) break;
		
		dir_visited.insert(dir_hash(x, y, grid.size(), dir));
		visited.insert(hash({x, y}, grid.size()));

		if (grid[x][y] == '|') {
			if (!(dir % 2)) {
				dir = 3;
				beam(grid, x+1, y, 1);
			}
		} else if (grid[x][y] == '-') {
			if (dir % 2) {
				dir = 2;
				beam(grid, x, y+1, 0);
			}
		} else if (grid[x][y] == '/') dir = 3 - dir;
		else if (grid[x][y] == '\\') {
			if (dir == 0) dir = 1;
			else if (dir == 1) dir = 0;
			else if (dir == 2) dir = 3;
			else if (dir == 3) dir = 2;
		}

		switch (dir) {
			case 0:
				y++;
				break;
			case 1:
				x++;
				break;
			case 2:
				y--;
				break;
			case 3:
				x--;
				break;
		}
	}
}

int main() {
	std::fstream file("input.txt");
	std::string s;
	std::vector<std::string> grid;

	while(std::getline(file, s)) {
		grid.push_back(s);
	}

	beam(grid, 0, 0, 0);
	std::cout << visited.size() << '\n'; // Part 1

	int best = visited.size();
	int lastrow = grid.size()-1, lastcol = grid[0].size();

	visited.clear();
	dir_visited.clear();

	// Part 2

	// The solution works, it's just a tad slow (like 2 minutes) because it goes through all the iterations of which there are 440
	// To compensate, there's a display of on which part the beam is right now so you know that the code isn't broken because it's running for 2 minutes

	for (int i = 1; i < grid.size(); i++) {
		std::cout << i << ' ' << 0 << '\n';
		beam(grid, i, 0, 0);
		best = std::max(best, (int)visited.size());
		visited.clear();
		dir_visited.clear();
	}
	for (int i = 0; i < grid[0].size(); i++) {
		std::cout << 0 << ' ' << i << '\n';
		beam(grid, 0, i, 1);
		best = std::max(best, (int)visited.size());
		visited.clear();
		dir_visited.clear();
	}
	for (int i = 0; i < grid.size(); i++) {
		std::cout << i << ' ' << lastcol << '\n';
		beam(grid, i, lastcol, 2);
		best = std::max(best, (int)visited.size());
		visited.clear();
		dir_visited.clear();
	}
	for (int i = 0; i < grid[0].size(); i++) {
		std::cout << lastrow << ' ' << i << '\n';
		beam(grid, lastrow, i, 3);
		best = std::max(best, (int)visited.size());
		visited.clear();
		dir_visited.clear();
	}

	std::cout << best << '\n';
}