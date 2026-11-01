#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "CSolution.h"

using namespace aoc2015::day6;
std::vector<std::string> readInput(const char *aPath) {
	std::fstream file(aPath);
	std::vector<std::string> input;
	std::string line;
	while (getline(file, line)) {
		input.push_back(line);
	}
	file.close();
	return input;
}

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Input path to file!" << std::endl;
		return -1;
	}
	auto input = readInput(argv[1]);
	CSolution light(ERule::partOne);
	CSolution brightness(ERule::partTwo);
	for (const auto &line : input) {
		light.command(line);
		brightness.command(line);
	}
	std::cout << light.getTurnedLights() << std::endl;
	std::cout << brightness.getTurnedLights() << std::endl;


	return 0;
}
