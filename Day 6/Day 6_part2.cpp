#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main() {
	std::fstream file("input.txt");
	std::string s;
	long long res;

	long long duration;
	long long record;

	{std::getline(file, s);
	s = s.substr(s.find(':')+1);
	std::string temp;
	int splitpos = 0;
	while (splitpos != -1) {
		if (s[0] == ' ') {
			s = s.substr(1);
			continue;
		}
		splitpos = s.find(' ');
		if (splitpos == -1) {
			temp += s;
			break;
		}
		temp += s.substr(0, splitpos);
		s = s.substr(splitpos+1);		
	}
	duration = std::stoll(temp);
	temp = "";

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
			temp += s;
			break;
		}
		temp += s.substr(0, splitpos);
		s = s.substr(splitpos+1);
	}
	record = std::stoll(temp);}

	res = duration;

	std::cout << duration << ' ' << record << '\n';

	for (long long j = 1; j*2 <= duration; j++) {
		if ((j*(duration-j)) > record) {
			std::cout << j << ' ' << (j*(duration-j)) << '\n';
			res -= j*2;
			break;
		}
	}
	res++; // One number gets skipped every time, I can't explain why, I don't know, it just works like this so let's leave it like this
	std::cout << res << '\n';
}