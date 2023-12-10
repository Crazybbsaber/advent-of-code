#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <numeric>

bool isNull(std::vector<int> &res) {
	for (int i : res) if (i) return false;
	return true;
}

int main() {
	std::fstream file("input.txt");
	std::string s;

	int sum = 0;
	int sum_part2 = 0;

	while (std::getline(file, s)) {
		std::stringstream ss(s);

		std::vector<std::vector<int>> nums = {{}};
		std::string num;
		while (std::getline(ss, num, ' ')) nums[0].push_back(std::stoi(num));

		while (!isNull(nums.back())) {
			std::vector<int> new_it;
			for (int i = 1; i < nums.back().size(); i++) new_it.push_back(nums.back()[i]-nums.back()[i-1]);
			nums.push_back(new_it);
		}

		int part_2 = 0;

		while (!nums.empty()) {
			sum += nums.back().back();
			part_2 = nums.back()[0] - part_2;
			nums.pop_back();
		}

		sum_part2 += part_2;
	}

	std::cout << sum << '\n' << sum_part2 << '\n';
}