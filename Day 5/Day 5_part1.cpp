#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
	std::fstream file("input.txt");
	std::string s;

	std::vector<long long> seeds;
	std::unordered_set<int> changed;

	while (std::getline(file, s)) {
		if (s == "") {
			changed.clear();
			continue;
		}
		if (s.back() == ':') continue;
		if (s.find(':') != -1) {
			s = s.substr(s.find(':')+2);
			int split = 0;
			while (split != -1) {
				split = s.find(' ');
				if (split == -1) {
					seeds.push_back(std::stoll(s));
					break;
				}
				seeds.push_back(std::stoll(s.substr(0, split)));
				s = s.substr(split+1);
			}
			continue;
		}
		
		long long dest = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long start = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long range = std::stoll(s);

		for (int i = 0; i < seeds.size(); i++) {
			if (changed.find(i) != changed.end()) continue;
			if (seeds[i] >= start && seeds[i] < (start+range)) {
				seeds[i] = dest + (seeds[i] - start);
				changed.insert(i);
			}
		}
	}

	long long res = LLONG_MAX;
	for (long long seed : seeds) res = std::min(res, seed);

	std::cout << res;
}