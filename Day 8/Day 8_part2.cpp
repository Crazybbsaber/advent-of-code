#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <numeric>

int main() {
	std::fstream file("input.txt");
	std::string s;

	std::unordered_map<std::string, std::pair<std::string, std::string>> adj;
	std::string instructions;

	std::getline(file, instructions); // Stores the instructions
	std::getline(file, s); // Removes the newline

	std::vector<std::string> start;

	while (std::getline(file, s)) {
		std::string node = s.substr(0,3);
		if (node.back() == 'A') start.push_back(node);
		adj[node] = {s.substr(7,3), s.substr(12, 3)};
	}

	long long steps = 1;
	int stepcount = 0;
	bool all_z = false;

	for (std::string &node : start) {
		while (node.back() != 'Z') {
			if (instructions[stepcount % instructions.size()] == 'R') node = adj[node].second;
			else node = adj[node].first;
			stepcount++;
		}
		steps = std::lcm(steps, stepcount);
		stepcount = 0;
	}

	std::cout << steps << '\n';	
}