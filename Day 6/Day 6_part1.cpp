#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::fstream file("input.txt");
	std::string s;
	int res = 1;

	std::vector<int> durations;
	std::vector<int> records;

	std::getline(file, s);
	s = s.substr(s.find(':')+1);
	int splitpos = 0;
	while (splitpos != -1) {
		if (s[0] == ' ') {
			s = s.substr(1);
			continue;
		}
		splitpos = s.find(' ');
		if (splitpos == -1) {
			durations.push_back(std::stoi(s));
			break;
		}
		durations.push_back(std::stoi(s.substr(0, splitpos)));
		s = s.substr(splitpos+1);		
	}

	std::getline(file, s);
	s = s.substr(s.find(':')+1);
	splitpos = 0;
	while (splitpos != -1) {
		if (s[0] == ' ') {
			s = s.substr(1);
			continue;
		}
		splitpos = s.find(' ');
		if (splitpos == -1) {
			records.push_back(std::stoi(s));
			break;
		}
		records.push_back(std::stoi(s.substr(0, splitpos)));
		s = s.substr(splitpos+1);
	}

	for (int i = 0; i < durations.size(); i++) {
		int c = 0;
		for (int j = 1; j*2 < durations[i]; j++) {
			if ((j*(durations[i]-j)) > records[i]) c += 2;
		}
		if (!(durations[i] % 2)) c++; // If it's an even number there's a middle number which will get skipped, but is guaranteed to be a record-breaking number
		res *= c;
	}

	std::cout << res;
}