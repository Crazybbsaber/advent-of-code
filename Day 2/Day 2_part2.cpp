#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
	std::fstream file("input.txt");
	std::string s;
	int res;

	while (std::getline(file, s)) {
		// Get Game ID

		std::string gamepart = s.substr(0, s.find(':'));
		int gameid = std::stoi(gamepart.substr(s.find(' ')+1));

		// Get Sets
		s = s.substr(s.find(':')+2);
		std::unordered_map<std::string, int> max = {{"blue", 0}, {"green", 0}, {"red", 0}};

		int setend = 1;
		while (setend != std::string::npos) {

			setend = s.find(';');
			std::string set;
			if (setend == -1) set = s;
			else set = s.substr(0, setend);
			s = s.substr(setend+2);
			
			int gameend = 1;
			while (gameend != std::string::npos) {
				gameend = set.find(',');
				std::string game;
				if (gameend == -1) game = set;
				else game = set.substr(0, gameend);
				set = set.substr(gameend+2);
				
				int split = game.find(' ');
				std::string current = game.substr(split+1);
				int value = std::stoi(game.substr(0, split));
				if (max[current] < value) {
					max[current] = value;
				}
			}
		}
		
		res += (max["blue"] * max["green"] * max["red"]);
	}

	std::cout << res << std::endl;
}