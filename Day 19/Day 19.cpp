#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct workflow {
	std::unordered_map<char, int> values;
};

int main() {
	std::fstream file("test.txt");
	std::string s;

	std::unordered_map<std::string, std::vector<std::string>> rules;
	bool gettingRules = true;
	int accepted = 0; // Part 1

	while (std::getline(file, s)) {
		if (s == "") {
			gettingRules = false;
			continue;
		}
		if (gettingRules) {
			std::string namespc = s.substr(0, s.find('{'));
			std::vector<std::string> ruleset;
			s = s.substr(s.find('{')+1);
			int splitpos = 0;
			while (splitpos != -1) {
				splitpos = s.find(',');
				if (splitpos == -1) {
					ruleset.push_back(s.substr(0, s.size()-1));
					break;
				}
				ruleset.push_back(s.substr(0, splitpos));
				s = s.substr(splitpos+1);
			}
			rules[namespc] = ruleset;
			continue;
		}
		workflow work = *new workflow();
		s = s.substr(1);
		for (char x : "xmas") {
			if (x == 's') {
				work.values[x] = std::stoi(s.substr(2, s.find('}')));
				continue;
			}
			work.values[x] = std::stoi(s.substr(2, s.find(',')));
			s = s.substr(s.find(',')+1);
		}

		std::string workfl = "in";
		bool accepted_rejected = false;
		while (true) {
			std::vector<std::string> ruleset = rules[workfl];
			for (std::string rule : ruleset) {
				if (rule == "A") {
					accepted += work.values['x'] + work.values['m'] + work.values['a'] + work.values['s'];
					accepted_rejected = true;
					break;
				}
				if (rule == "R") {
					accepted_rejected = true;
					break;
				}
				if (rule.find(':') == -1) {
					workfl = rule;
					break;
				}
				char used = rule[0];
				char op = rule[1];
				int num = std::stoi(rule.substr(2, s.find(':')));
				std::string next = rule.substr(rule.find(':')+1);
				if (op == '>') {
					if (work.values[used] > num) {
						if (next == "A") {
							accepted += work.values['x'] + work.values['m'] + work.values['a'] + work.values['s'];
							accepted_rejected = true;
							break;
						}
						if (next == "R") {
							accepted_rejected = true;
							break;
						}
						workfl = next;
						break;
					}
				} else if (op == '<') {
					if (work.values[used] < num) {
						if (next == "A") {
							accepted += work.values['x'] + work.values['m'] + work.values['a'] + work.values['s'];
							accepted_rejected = true;
							break;
						}
						if (next == "R") {
							accepted_rejected = true;
							break;
						}
						workfl = next;
						break;
					}
				}
			}
			if (accepted_rejected) break;
		}
	}

	std::cout << accepted << '\n';
}