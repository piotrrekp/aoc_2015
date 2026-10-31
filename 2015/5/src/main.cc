#include "CSolution.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <ranges>
#include <algorithm>

std::vector<std::string> readInput(const char *aPath) {
	std::ifstream file(aPath);
	std::vector<std::string> input;
	std::string line;
	while (getline(file, line)) {
		input.push_back(line);
	}
	return input;
}


int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Input path to file!" << std::endl;
		return -1;
	}
	auto input = readInput(argv[1]);

	std::cout <<
		std::ranges::count_if(input, aoc2015::day5::reqPartOne)
			<< std::endl;
	std::cout <<
		std::ranges::count_if(input, aoc2015::day5::reqPartTwo)
			<< std::endl;

	return 0;
}
