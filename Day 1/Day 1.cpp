#include <fstream>
#include <string>
#include <iostream>

int main() {
	std::fstream file("input.txt");
	std::string s;
	int res;

	while (std::getline(file, s)) {
		int f, l;

		for (int x = 0; x < s.size(); x++) {
			if (s[x] > '0' && s[x] <= '9') {
				f = (s[x] - '0');
				break;
			}
		}

		for (int x = (s.size()-1); x >= 0; x--) {
			if (s[x] > '0' && s[x] <= '9') {
				l = (s[x] - '0');
				break;
			}
		}

		res += ((f*10)+l);
	}

	std::cout << res << std::endl;
}