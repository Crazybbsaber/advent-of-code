#include <fstream>
#include <string>
#include <iostream>
#include <vector>

// I didn't merge the two parts, so you get two parts yea...

int main() {
	std::fstream file("input.txt");
	std::string s;
	int res;
	
	std::vector<std::string> nums = {"0", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	while (std::getline(file, s)) {
		int f = 0, l = 0;
		std::string number;

		for (int x = 0; x < s.size(); x++) {
			if (s[x] > '0' && s[x] <= '9') {
				f = (s[x] - '0');
				break;
			}

			number += s[x];
			for (int i = 1; i < nums.size(); i++) {
				if (number.find(nums[i]) != std::string::npos) {
					f = i;
					break;
				}
			}

			if (f) break;
		}

		number = "";

		for (int x = (s.size()-1); x >= 0; x--) {
			if (s[x] > '0' && s[x] <= '9') {
				l = (s[x] - '0');
				break;
			}

			number.insert(number.begin(), s[x]);
			
			for (int i = 1; i < nums.size(); i++) {
				if (number.rfind(nums[i]) != std::string::npos) {
					l = i;
					break;
				}
			}

			if (l) break;
		}

		res += ((f*10)+l);
	}

	std::cout << res << std::endl;
}