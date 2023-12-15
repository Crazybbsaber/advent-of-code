#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

int hash(std::string s) {
	int hash = 0;
	for (char x : s) {
		hash += x;
		hash *= 17;
		hash %=  256;
	}

	return hash;
}

int main() {
	std::fstream file("input.txt");
	std::string s;

	std::getline(file, s); // There's one line of input
	std::stringstream ss(s);

	int hash_sum = 0;
	std::vector<std::pair<std::string, int>> hashmap[256] = {};

	while (std::getline(ss, s, ',')) {
		int hashed = hash(s);
		hash_sum += hashed;

		if (s.back() == '-') {
			int hash_id = hash(s.substr(0, s.find('-')));
			for (int i = 0; i < hashmap[hash_id].size(); i++) {
				if (s.find(hashmap[hash_id][i].first) != -1) {
					hashmap[hash_id].erase(hashmap[hash_id].begin()+i);
					break;
				}
			}
		} else {
			std::string id = s.substr(0, s.find('='));
			int hash_id = hash(id);
			int power = std::stoi(s.substr(s.find('=')+1));
			bool inHashmap = false;
			for (int i = 0; i < hashmap[hash_id].size(); i++) {
				if (s.find(hashmap[hash_id][i].first) != -1) {
					hashmap[hash_id][i].second = power;
					inHashmap = true;
				}
			}

			if (!inHashmap) hashmap[hash_id].push_back({id, power});
		}
	}

	int focusing_power = 0;
	for (int i = 0; i < 256; i++) {
		int box_id = i+1;
		for (int j = 0; j < hashmap[i].size(); j++) {
			focusing_power += (box_id * (j+1) * hashmap[i][j].second);
		}
	}

	std::cout << hash_sum << '\n'; // Part 1 solution
	std::cout << focusing_power << '\n'; // Part 2 solution
}