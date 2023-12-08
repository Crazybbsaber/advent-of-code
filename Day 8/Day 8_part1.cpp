#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main() {
	std::fstream file("input.txt");
	std::string s;

	std::unordered_map<std::string, std::pair<std::string, std::string>> adj;
	std::string instructions;

	std::getline(file, instructions); // Stores the instructions
	std::getline(file, s); // Removes the newline

	while (std::getline(file, s)) {
		std::string node = s.substr(0,3);
		adj[node] = {s.substr(7,3), s.substr(12, 3)};
	}

	std::string current_node = "AAA";
	int stepcount;

	while (current_node != "ZZZ") {
		if (instructions[stepcount % instructions.size()] == 'R') current_node = adj[current_node].second;
		else current_node = adj[current_node].first;
		stepcount++;
	}

	std::cout << stepcount << '\n';	
}