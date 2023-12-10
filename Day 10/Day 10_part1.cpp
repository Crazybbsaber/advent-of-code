#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

std::string top = "7F|S";
std::string left = "LF-S";
std::string down = "|LJS";
std::string right = "J7-S";

std::string topconnecting = "|LJS";
std::string leftconnecting = "J7-S";
std::string downconnecting = "F7|S";
std::string rightconnecting = "LF-S";

int id(std::pair<int, int> pair, int n) {
	return (pair.first*n)+pair.second;
}

int bfs(int x, int y, int dist, std::vector<std::string> &grid, std::queue<std::pair<std::pair<int, int>, int>> &q, std::unordered_set<int> &visited) {
	std::pair<int, int> connections;

	if (x == -1 || x == grid.size()) return -1;
	if (y == -1 || y == grid[0].size()) return -1;

	int position_id = id({x, y}, grid[0].size());
	if (visited.find(position_id) != visited.end()) return -1;
	visited.insert(position_id);

	if (grid[x][y] == '.') return -1;

	if (x && topconnecting.find(grid[x][y]) != -1 && top.find(grid[x-1][y]) != -1) {
		connections.first = 1;
	}
	if (y && leftconnecting.find(grid[x][y]) != -1 && left.find(grid[x][y-1]) != -1) {
		if (connections.first) connections.second = 2;
		else connections.first = 2;
	} 
	if (x != grid[0].size() && downconnecting.find(grid[x][y]) != -1 && down.find(grid[x+1][y]) != -1) {
		if (connections.first && connections.second) return -1;
		else if (connections.first) connections.second = 3;
		else connections.first = 3;
	}
	if (y != grid.size() && rightconnecting.find(grid[x][y]) != -1 && right.find(grid[x][y+1]) != -1) {
		if (connections.first && connections.second) return -1;
		else if (connections.first) connections.second = 4;
		else return -1;
	}
	if (!connections.first || !connections.second) return -1;
	dist++;
	if (connections.first == 1) q.push({{x-1, y}, dist});
	if (connections.first == 2 || connections.second == 2) q.push({{x, y-1}, dist});
	if (connections.first == 3 || connections.second == 3) q.push({{x+1, y}, dist});
	if (connections.second == 4) q.push({{x, y+1}, dist});

	return --dist;
}

int main() {
	std::fstream file("input.txt");
	std::string s;

	std::queue<std::pair<std::pair<int, int>, int>> q;
	std::vector<std::string> grid;
	std::unordered_set<int> visited;

	std::pair<int, int> beast;

	while (std::getline(file, s)) {
		if (s.find('S') != -1) beast = {grid.size(), s.find('S')};
		grid.push_back(s);
	}

	q.push({beast, 0});
	int farthest_part = -1;

	while (!q.empty()) {
		std::pair<std::pair<int, int>, int> top = q.front();
		q.pop();
		int far = bfs(top.first.first, top.first.second, top.second, grid, q, visited);
		farthest_part = std::max(farthest_part, far);
	}

	std::cout << farthest_part << '\n';
}