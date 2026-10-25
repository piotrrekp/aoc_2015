#include <cassert>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <ranges>
#include <algorithm>

int countFloor(std::string_view atext) {
	return std::ranges::count(atext, '(') - std::ranges::count(atext,')');
}

std::optional<std::size_t> getBasementPosition(std::string_view atext) {
	int vResult = 0;
	std::size_t pos = 1;
	for (auto c : atext) {
		vResult += (c == '(') ? 1 : -1;
		if (vResult < 0)
			return pos;
		++pos;
	}
	return std::nullopt;
}

int main(int argc, const char **argv) {
	const std::string testCase1 = "(())";
	const std::string testCase2 = "(((()()))";
	const std::string testCase3 = "))(())";
	const std::string testCase4 = "()()))(())";
	assert(countFloor(testCase1) == 0);
	assert(countFloor(testCase2) == 1);
	assert(countFloor(testCase3) == -2);
	assert(countFloor(testCase4) == -2);

	const std::string testCaseSecondPart1 = ")";
	const std::string testCaseSecondPart2 = "(((()()))))";
	assert(getBasementPosition(testCaseSecondPart1) == 1);
	assert(getBasementPosition(testCaseSecondPart2) == 11);

	std::fstream vFile(argv[1]);
	std::string line;
	getline(vFile, line);
	auto part2ans = getBasementPosition(line);

	std::cout << "part 1: " << countFloor(line) <<std::endl;
	std::cout << "part 2: ";
	if (part2ans)
		std::cout << *part2ans << std::endl;
	else
		std::cout << "not found" << std::endl;;
	return 0;
}
