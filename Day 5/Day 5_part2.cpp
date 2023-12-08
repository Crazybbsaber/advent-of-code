#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

// I tried to run it, it took 25 minutes, 26 GB of RAM and it returned a blank line, I will do it one day...

int main() {
	std::fstream file("input.txt"); // I don't know why but this laptop decided that fstream will stop working...
	std::string s;

	// {std::cout << "This code will fuck your computer! Proceed? [y/n] ";
	// char x;
	// std::cin >> x;
	// if (x == 'N' || x == 'n' || x == 13) return 0;}

	std::vector<long long> seeds;

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

	while (std::getline(file, s)) {
		if (s == "") continue;
		if (s.back() == ':') {
			// std::cout << "SIZE_" << seeds.size() << '\n';
			continue;
		}

		long long dest = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long start = std::stoll(s.substr(0, s.find(' ')));
		s = s.substr(s.find(' ')+1);
		long long range = (std::stoll(s) - 1);

		// std::cout << seeds.size() << std::endl;

		for (int i = 0; i < seeds.size(); i+=2) {
			// std::cout << seeds[i] << ' ' << seeds[i+1] << '\t';

			if (seeds[i] >= start && seeds[i] < (start+range)) {
				if ((seeds[i]+seeds[i+1]) < (start+range)) {
					seeds[i] = dest + (seeds[i] - start);
				} else if ((seeds[i]+seeds[i+1]) >= (start+range)) {
					long long dif = (seeds[i]+seeds[i+1])-(start+range);
					seeds[i+1] -= dif;
					seeds[i] = dest + (seeds[i] - start);
					seeds.push_back(start+range+1);
					seeds.push_back(dif);
				}
			} else if (seeds[i] < start) {
				if ((seeds[i]+seeds[i+1]) > (start+range)) {
					long long dif_front = start - seeds[i];
					long long dif_back = (seeds[i]+seeds[i+1]) - (start+range);
					seeds.push_back(seeds[i]);
					seeds.push_back(dif_front-1);
					seeds.push_back(seeds[i]+seeds[i+1]-dif_back);
					seeds.push_back(dif_back-1);
					seeds[i] += dif_front;
					seeds[i+1] -= dif_back;
					seeds[i] = dest;
				} else if ((seeds[i]+seeds[i+1]) <= (start+range) && (seeds[i]+seeds[i+1]) > start) {
					long long dif = start - seeds[i];
					seeds.push_back(start);
					seeds.push_back(dif-1);
					seeds[i] += dif;
					seeds[i-1] -= dif;
				}
			}
		}
	}

	long long min = LLONG_MAX;
	for (int i = 0; i < seeds.size(); i+=2) min = std::min(min, seeds[i]);

	std::cout << min << '\n';

	for (int i = 0; i < seeds.size(); i++) std::cout << seeds[i] << ' ' << i << '\t';
	std::cout << seeds.size() << '\n';
}