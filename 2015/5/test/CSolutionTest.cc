#include <gtest/gtest.h>
#include <ostream>
#include <string_view>
#include <vector>
#include "../src/CSolution.h"

struct TestCase {
	std::string_view input;
	bool expected;
	friend std::ostream& operator<<(std::ostream& out, const TestCase& t) {
		return out << "input=\"" << t.input << "\",expected="
			<< (t.expected ? "true" : "false");
	}
};

class PartOne : public testing::TestWithParam<TestCase> {};

std::vector<TestCase> testingData{
	{"", false},
	{"axxx", false},
	{"axra", false},
	{"axxaxa", true},
	{"axexxa", true},
	{"axeqxa", false},
	{"ggaaa", true},
	{"cdaxxaxa", false},
	{"abaxxaxa", false},
	{"xyaxxaxa", false},
	{"pqaxxaxa", false},
	{"ugknbfddgicrmopn", true},
	{"jchzalrnumimnmhp", false},
	{"haegwjzuvuyypxyu", false},
	{"dvszwmarrgswjxmb", false}

};

INSTANTIATE_TEST_CASE_P(, PartOne, testing::ValuesIn(testingData));

TEST_P(PartOne, check) {

	ASSERT_EQ(aoc2015::day5::reqPartOne(GetParam().input), GetParam().expected);
}


class PartTwo :  public testing::TestWithParam<TestCase> {};

std::vector<TestCase> testingDataPartTwo{
	{"ieodomkazucvgmuy", false},
	{"uurcxstgmygtbstg", false},
	{"aba", false},
	{"aaa", false},
	{"xxyxx", true},
	{"qjhvhtzxzqqjkmpb", true},
	{"", false},
	{"a", false},
	{"aa", false},
	{"aaaa", true},
	{"xyxy", true},
	{"aabcdefgaa", false},

};

INSTANTIATE_TEST_CASE_P(, PartTwo, testing::ValuesIn(testingDataPartTwo));

TEST_P(PartTwo, check) {
	ASSERT_EQ(aoc2015::day5::reqPartTwo(GetParam().input), GetParam().expected);
}

