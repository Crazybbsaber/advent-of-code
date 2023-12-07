#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

std::string revert(std::string affected) {
	std::replace(affected.begin(), affected.end(), 'B', 'T');
	std::replace(affected.begin(), affected.end(), '1', 'J');
	std::replace(affected.begin(), affected.end(), 'D', 'Q');
	std::replace(affected.begin(), affected.end(), 'E', 'K');
	std::replace(affected.begin(), affected.end(), 'F', 'A');

	return affected;
}

int main() {
	std::fstream file("test.txt");
	std::string s;
	std::unordered_map<std::string, int> biddings;

	int res = 0;
	int c = 1;

	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> highcards;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> onepair;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> twopair;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> threeofkind;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> fullhouse;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> fourofkind;
	std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> fiveofkind;

	while (std::getline(file, s)) {
		std::string hand = s.substr(0, 5);
		int bid = std::stoi(s.substr(6));

		std::vector<char> cards;
		std::vector<char> cards2;
		std::unordered_map<char, int> pairs;

		for (char x : hand) {
			if (pairs.find(x) == pairs.end()) {
				cards.push_back(x);
				if (x != 'J') cards2.push_back(x);
				pairs[x] = 0;
			}
			pairs[x]++;
		}

		biddings[hand] = bid;
		std::replace(hand.begin(), hand.end(), 'T', 'B');
		std::replace(hand.begin(), hand.end(), 'J', '1');
		std::replace(hand.begin(), hand.end(), 'Q', 'D');
		std::replace(hand.begin(), hand.end(), 'K', 'E');
		std::replace(hand.begin(), hand.end(), 'A', 'F');

		int jokers = pairs['J'];

		switch (cards.size()) {
			case 1:
				fiveofkind.push(hand);
				break;
			case 2:
				if (jokers) {
					fiveofkind.push(hand);
					break;
				}
				if (pairs[cards[0]] == 4 || pairs[cards[1]] == 4) fourofkind.push(hand);
				else fullhouse.push(hand);
				break;
			case 3:
				if (jokers) {
					if ((pairs[cards2[0]] + jokers) == 4 || (pairs[cards2[1]] + jokers) == 4) fourofkind.push(hand); 
					else fullhouse.push(hand);
					break;
				}
				if (pairs[cards[0]] == 3 || pairs[cards[1]] == 3 || pairs[cards[2]] == 3) threeofkind.push(hand);
				else twopair.push(hand);
				break;
			case 4:
				if (jokers) {
					if (pairs[cards2[0]] + jokers == 3 || pairs[cards2[1]] + jokers == 3 || pairs[cards2[2]] + jokers == 3) threeofkind.push(hand);
					else twopair.push(hand);
					break;
				}
				onepair.push(hand);
				break;
			case 5:
				if (jokers) onepair.push(hand);
				else highcards.push(hand);
				break;
			default:
				break;
		}
	}

	while (!highcards.empty()) {
		std::string hand = revert(highcards.top());
		highcards.pop();
		// std::cout << hand << '\n';

		res += (biddings[hand]*c);
		c++;
	}
	while (!onepair.empty()) {
		std::string hand = revert(onepair.top());
		onepair.pop();
		// std::cout << hand << '\n';

		res += (biddings[hand]*c);
		c++;
	}
	while (!twopair.empty()) {
		std::string hand = revert(twopair.top());
		twopair.pop();
		// std::cout << hand << '\n';

		res += (biddings[hand]*c);
		c++;
	}
	while (!threeofkind.empty()) {
		std::string hand = revert(threeofkind.top());
		threeofkind.pop();
		// std::cout << hand << '\n';
	
		res += (biddings[hand]*c);
		c++;
	}
	while (!fullhouse.empty()) {
		std::string hand = revert(fullhouse.top());
		fullhouse.pop();
		// std::cout << hand << '\n';
	
		res += (biddings[hand]*c);
		c++;
	}
	while (!fourofkind.empty()) {
		std::string hand = revert(fourofkind.top());
		fourofkind.pop();
		// std::cout << hand << '\n';
		
		res += (biddings[hand]*c);
		c++;
	}
	while (!fiveofkind.empty()) {
		std::string hand = revert(fiveofkind.top());
		fiveofkind.pop();
		// std::cout << hand << '\n';
	
		res += (biddings[hand]*c);
		c++;
	}

	std::cout << res << '\n';
}