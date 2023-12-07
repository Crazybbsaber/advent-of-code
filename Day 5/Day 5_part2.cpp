#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

// I tried to run it, it took 25 minutes, 26 GB of RAM and it returned a blank line, I will do it one day...

int main() {
	std::fstream file("test.txt"); // I don't know why but this laptop decided that fstream will stop working...
	std::string s;

	// {std::cout << "This code will fuck your computer! Proceed? [y/n] ";
	// char x;
	// std::cin >> x;
	// if (x == 'N' || x == 'n' || x == 13) return 0;}

	std::vector<long long> seeds;
	std::unordered_set<int> changed;

	std::getline(file, s);
	s = s.substr(7);
	int split = 0;
	while (split != -1) {
		split = s.find(' ');
		if (split == -1) {
			seeds.push_back(std::stoll(s)-1);
			break;
		}
		if (seeds.size() % 2) seeds.push_back(std::stoll(s.substr(0, split)) - 1);
		else seeds.push_back(std::stoll(s.substr(0, split)));
		s = s.substr(split+1);
	}

	for (int i = 0; i < seeds.size(); i += 2) {
		std::cout << seeds[i] << '\t' << (seeds[i]+seeds[i+1]) << '\n';
	}

	while (std::getline(file, s)) {
		if (s == "") continue;
		if (s.back() == ':') {
			continue;
		}

		long long dest = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long start = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long range = (std::stoll(s) - 1);

		for (int i = 0; i < seeds.size(); i++) {
			if (changed.find(i) != changed.end()) continue;

			if (seeds[i] <= start) {
				if ((seeds[i]+seeds[i+1]) >= (start+range)) {
					seeds[i] = dest + (seeds[i] - start);
					changed.insert(i);
				} else if ((seeds[i]+seeds[i+1]) < (start+range)) {
					// Later that day...
				}
			}
		}
	}	
}