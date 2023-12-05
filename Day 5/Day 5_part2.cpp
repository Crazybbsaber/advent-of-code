#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

// I tried to run it, it took 25 minutes, 26 GB of RAM and it returned a blank line, I will do it one day...

int main() {
	std::fstream file("input.txt");
	std::string s;

	{std::cout << "This code will fuck your computer! Proceed? [y/n] ";
	char x;
	std::cin >> x;
	if (x == 'N' || x == 'n' || x == 13) return 0;}

	std::vector<long long> seeds;
	std::unordered_set<int> changed;

	int c = 0;

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
				long long num1 = std::stoll(s.substr(0, split));
				s = s.substr(split+1);
				split = s.find(' ');
				long long num2;
				if (split == -1) {
					num2 = std::stoll(s);
				} else {
					num2 = std::stoll(s.substr(0, split));
					s = s.substr(split+1);
				}
				for (long long i = 0; i < num2; i++) {
					seeds.push_back(num1++);
				}				
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

		std::cout << ++c << '\n';
	}

	long long res = LLONG_MAX;
	for (long long seed : seeds) res = std::min(res, seed);

	std::cout << res;
}