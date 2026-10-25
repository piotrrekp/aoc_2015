#include "CSolution.h"
#include <fstream>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Input path to file!" << std::endl;
		return -1;
	}
	std::fstream file(argv[1]);
	std::vector<std::string> input;
	std::string line;
	while (getline(file, line)) {
		input.push_back(line);
	}
	file.close();

	CSolution solution(input);
	int vResult = solution.getTotalNeededSurface();
	int vSecondResult = solution.getTotalRibbonNeeded();
	std::cout << vResult << ", " << vSecondResult << std::endl;

	return 0;
}
