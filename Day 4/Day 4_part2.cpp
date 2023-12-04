#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

std::unordered_map<int, int> cards;
std::priority_queue<int, std::vector<int>, std::greater<int>> copies;

int main() {
	std::fstream file("input.txt");
	std::string s;
	int c = 0;

	while (std::getline(file, s)) {
		c++;
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

		int res = c;
		splitpos = 0;
		while (splitpos != -1) {
			splitpos = actual.find(' ');
			if (splitpos == -1) {
				if (std::find(win_nums.begin(), win_nums.end(), std::stoi(actual)) != win_nums.end()) {
					res++;
				}
				break;
			}
			std::string act_num = actual.substr(0, splitpos);
			actual = actual.substr(splitpos+1);
			if (act_num == "") continue;
			if (std::find(win_nums.begin(), win_nums.end(), std::stoi(act_num)) != win_nums.end()) {
				res++;
			}
		}
		cards[c] = res - c;
		copies.push(c);
	}

	int copiesc = 0; // copiesc as in copies_count
	// int fivec = 0;
	// int actfivec = 0;
	while (!copies.empty()) {
		int copy = copies.top();
		copies.pop();
		// std::cout << copy << '\t';
		// if (copy == 5) actfivec++;
		
		copiesc++;
		for (int i = 1; i <= cards[copy]; i++) {
			// if ((copy + i) == 5) fivec++;
			copies.push(copy+i);
		}
	}

	std::cout << copiesc << '\n';
}