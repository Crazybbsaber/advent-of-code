#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

const int STEPS = 64; // In the test example we are looking for 6 steps, but in the input, we're looking for 64 steps so steps are saved as a variable
const int MORE_STEPS = 10; // In Part 2 we're asked for 26 501 365 steps...
// Ye... Part 2 doesn't work we'll fix that some day, but that won't be right now...

std::queue<std::pair<std::pair<int, int>, int>> q;
std::unordered_set<int> visited;
int n;

int id(std::pair<int, int> xy) {
	return (xy.first*n)+xy.second;
}

int actualise_position(int x) {
	if (x >= 0) return x%n;
	return std::abs(n+x%n-1);
}

void simulate_steps(std::vector<std::string> &grid, std::pair<int, int> pos, int steps) {
	if (pos.first == -1 || pos.second == -1) return;
	if (pos.first == n || pos.second == n) return;
	if (grid[pos.first][pos.second] == '#') return;
	if (visited.find(id(pos)) != visited.end()) return;
	visited.insert(id(pos));

	steps++;
	q.push({{pos.first+1, pos.second}, steps});
	q.push({{pos.first-1, pos.second}, steps});
	q.push({{pos.first, pos.second+1}, steps});
	q.push({{pos.first, pos.second-1}, steps});
}

void simulate_infinite_steps(std::vector<std::string> &grid, std::pair<int, int> pos, int steps) {
	int actual_x = actualise_position(pos.first), actual_y = actualise_position(pos.second);
	// std::cout << actual_x << '\t' << actual_y << '\n';
	if (grid[actual_x][actual_y] == '#') return;
	if (visited.find(id(pos)) != visited.end()) return;
	visited.insert(id(pos));

	steps++;
	q.push({{pos.first+1, pos.second}, steps});
	q.push({{pos.first-1, pos.second}, steps});
	q.push({{pos.first, pos.second+1}, steps});
	q.push({{pos.first, pos.second-1}, steps});
}

int main() {
	std::fstream file("test.txt");
	std::string s;

	std::vector<std::string> grid;
	std::pair<int, int> start = {-1, -1};

	while (std::getline(file, s)) {
		if (start.first == -1 && s.find('S') != -1) start = {grid.size(), s.find('S')};
		grid.push_back(s);
	}

	n = grid.size(); // The grid is always square so we only need one size
	q.push({start, 0});

	int lastSteps = 0;
	while (!q.empty()) {
		std::pair<std::pair<int, int>, int> top = q.front();
		q.pop();

		if (top.second > STEPS) break;

		if (lastSteps != top.second) {
			visited.clear();
			lastSteps = top.second;
		}

		simulate_steps(grid, top.first, top.second);
	}

	std::cout << visited.size() << '\n';

	while(!q.empty()) q.pop();
	q.push({start, 0});

	visited.clear();

	lastSteps = 0;
	while(!q.empty()) {
		std::pair<std::pair<int, int>, int> top = q.front();
		q.pop();

		if (top.second > MORE_STEPS) break;

		if (lastSteps != top.second) {
			visited.clear();
			lastSteps = top.second;
		}

		simulate_infinite_steps(grid, top.first, top.second);
	}

	std::cout << visited.size() << '\n';
}