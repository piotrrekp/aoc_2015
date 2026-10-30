#include "CSolution.h"

#include <array>
#include <iostream>
#include <set>

struct Position {
	int x{};
	int y{};
	auto operator<=>(const Position &) const = default;

};

void move(Position& pos, char c) {
	auto &[x, y] = pos;
	switch (c) {
		case 'v': --y; break;
		case '^': ++y; break;
		case '>': ++x; break;
		case '<': --x; break;
		default:
			std::cerr << "unhandled char: " << c <<  std::endl;
			break;
	}
}

int CSolution::getVisitedHouses(std::string_view list) {
	std::set<Position> visitedHouses;
	Position pos{0,0};
	visitedHouses.insert(pos);

	for (const auto &c : list) {
		move(pos, c);
		visitedHouses.insert(pos);
	}
	return visitedHouses.size();
}

int CSolution::getVisitedHouses_v2(std::string_view list) {
	std::set<Position> visitedHouses;
	std::array<Position, 2> positions{{{0,0}, {0,0}}};
	visitedHouses.insert({0,0});

	for (std::size_t i = 0; i < list.size(); ++i) {
		move(positions[i%2], list[i]);
		visitedHouses.insert(positions[i % 2]);
	}
	return visitedHouses.size();
}
