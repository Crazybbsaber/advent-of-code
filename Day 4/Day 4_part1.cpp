#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
	std::fstream file("input.txt");
	std::string s;
	int points = 0;

	while (std::getline(file, s)) {
		std::string numbers = s.substr(s.find(':')+2);
		std::string winning = numbers.substr(0, numbers.find('|') - 1);
		std::string actual = numbers.substr(numbers.find('|') + 2);

		std::vector<int> win_nums;
		int splitpos = 0;
		while (splitpos != -1) {
			splitpos = winning.find(' ');
			if (splitpos == -1) {
				win_nums.push_back(std::stoi(winning));
				break;
			}
			std::string win_num = winning.substr(0, splitpos);
			winning = winning.substr(splitpos+1);
			if (win_num == "") continue;
			win_nums.push_back(std::stoi(win_num));
		}

		int res = 0;
		splitpos = 0;
		while (splitpos != -1) {
			splitpos = actual.find(' ');
			if (splitpos == -1) {
				if (std::find(win_nums.begin(), win_nums.end(), std::stoi(actual)) != win_nums.end()) {
					if (res) res *= 2;
					else res = 1;
				}
				break;
			}
			std::string act_num = actual.substr(0, splitpos);
			actual = actual.substr(splitpos+1);
			if (act_num == "") continue;
			if (std::find(win_nums.begin(), win_nums.end(), std::stoi(act_num)) != win_nums.end()) {
				if (res) res *= 2;
				else res = 1;
			}
		}
		points += res;
	}
	std::cout << points << '\n';
}