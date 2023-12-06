#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

// I tried to run it, it took 25 minutes, 26 GB of RAM and it returned a blank line, I will do it one day...

int main() {
	std::fstream file("test.txt"); // I don't know why but this laptop decided that fstream will stop working...
	std::string s;

	{std::cout << "This code will fuck your computer! Proceed? [y/n] ";
	char x;
	std::cin >> x;
	if (x == 'N' || x == 'n' || x == 13) return 0;}

	std::vector<long long> seeds;
	std::unordered_set<int> changed;

	int c = 0;

	while (std::getline(file, s)) {
		std::cout << "A" << '\n';
		if (s == "") {
			changed.clear();
			continue;
		}
		if (s.back() == ':') continue;
		if (s.find(':') != -1) { // Adds ranges which are too big to just push_back into the vector as the start and the length of the range
			std::cout << "oi" << '\n';
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

		for (int i = 0; i < seeds.size(); i+=2) {
			if (changed.find(i) != changed.end()) continue;
			if (seeds[i] >= start) { // If the range starts inside the mutation
				if (seeds[i] < (start+range)) { // If the range is completely inside the mutation
					seeds[i] = dest + (seeds[i]-start); // Mutates the range to fit the new changed value
					changed.insert(i);
				} else { // If the range start is inside the permutation, but the range at some point exits the mutation
					int dif = (seeds[i]+seeds[i+1]) - (start+range); // Gets the leftovers
					seeds[i+1] -= dif; // Shortens the range
					seeds.push_back(seeds[i]+dif); // Adds a new range, starting from the new unmutated value
					seeds.push_back(dif); // Adds the leftovers range length
					seeds[i] = dest + (seeds[i]-start); // Mutates the changed range
					changed.insert(i);
				}
				seeds[i] = dest + (seeds[i] - start);
			} else if (seeds[i]+seeds[i+1] >= start ) { // If the range is in the mutation, but doesn't start in the mutation
				int seed_range_end = seeds[i]+seeds[i+1];
				if (seed_range_end <= start+range) { // If the range ends inside the mutation
					int dif = (seed_range_end - start); // Gets the mutated part of the range
					seeds[i+1] -= dif; // Removes the mutated part from the unmutated part
					seeds.push_back(dest); // Adds the mutated value
					seeds.push_back(dif); // Adds the range length of the mutated values
					changed.insert(seeds.size()-2); // Adds the mutated range into the set of already changed values
				} else {
					int dif_front = (start - seeds[i]); // Gets the size of the first unmutated range
					int dif_back = (seed_range_end - (start + range)); // Gets the size of the second unmutated range
					seeds[i+1] = dif_front; // Sets the size of the first unmutated range to the start of the mutation
					seeds.push_back(dest); // Adds the mutated range
					seeds.push_back(range); // Adds the length of the mutated range
					changed.insert(seeds.size() - 2);
					seeds.push_back(start+range); // Adds the second unmutated range
					seeds.push_back(dif_back); // Adds the size of the second unmutated range
				}
			}
		}

		std::cout << ++c << '\n';
	}

	long long res = LLONG_MAX;
	for (int n = 0; n < seeds.size(); n+=2) res = std::min(res, seeds[n]);
	for (int n = 0; n < seeds.size(); n+=2) std::cout << seeds[n] << '\n';

	std::cout << res;
}