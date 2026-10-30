#include "CSolution.h"
#include <iostream>
#include <fstream>
#include <unistd.h>

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cerr << "Input path to file!" << std::endl;
		return -1;
	}
	std::fstream file(argv[1]);
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Problem z otwarciem pliku" << std::endl;
		return -1;
	}
	getline(file, line);
	file.close();

	CSolution solution;
	std::cout << solution.getVisitedHouses(line) << std::endl;
	std::cout << solution.getVisitedHouses_v2(line) << std::endl;

	return 0;
}
