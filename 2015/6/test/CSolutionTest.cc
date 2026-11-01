#include <bitset>
#include <gtest/gtest.h>
#include <numeric>
#include <regex>

#include "../src/CSolution.h"

using namespace aoc2015::day6;

struct CTestData {
	std::string_view command;
	int expected;
	friend std::ostream& operator<<(std::ostream &os, const CTestData &obj) {
		os << "command \"" << obj.command
			<< "\", should result with expeced = " << obj.expected;
		return os;
	}

};

class CSolutionTester : public CSolution, public testing::TestWithParam<CTestData> {
public:
	CSolutionTester() : CSolution(ERule::partOne) {}
};

std::vector<CTestData> testingData{
	CTestData("turn on 0,0 throught 999,999", size*size),
	CTestData("turn on 0,0 throught 999,0", size),
	CTestData("toggle 0,0 throught 999,0", size),
	CTestData("turn on 3,8 throught 999,13", 5982),
};

INSTANTIATE_TEST_CASE_P(, CSolutionTester, testing::ValuesIn(testingData));

TEST_P(CSolutionTester, check) {
	command(GetParam().command);
	ASSERT_EQ(getTurnedLights(), GetParam().expected);
}

TEST(commandParser, parseCommandTurnOn) {
	auto result = aoc2015::day6::getCommand("turn on 1,2 throught 3,4");
	ASSERT_EQ(result.command, ECommand::turnOn);
	ASSERT_EQ(result.start, Point(1, 2));
	ASSERT_EQ(result.end, Point(3, 4));
}


TEST(commandParser, parseCommandTurnOff) {
	auto result = aoc2015::day6::getCommand("turn off 100,200 throught 999,999");
	ASSERT_EQ(result.command, ECommand::turnOff);
	ASSERT_EQ(result.start, Point(100, 200));
	ASSERT_EQ(result.end, Point(999, 999));
}

TEST(commandParser, parseCommandToggle) {
	auto result = aoc2015::day6::getCommand("toggle 100,0 throught 100,69");
	ASSERT_EQ(result.command, ECommand::toggle);
	ASSERT_EQ(result.start, Point(100, 0));
	ASSERT_EQ(result.end, Point(100, 69));
}

TEST(lights, noLightlitWhenStart) {
	CLights light(ERule::partOne);
	ASSERT_EQ(light.getLit(), 0);
}


TEST(lights, turnOnSingleLight) {
	CLights light(ERule::partOne);
	Command command{ECommand::turnOn, Point(0,0), Point(0,0)};
	light.execute(command);
	ASSERT_EQ(light.getLit(), 1);
}


TEST(lights, turnOnSingleLightAndTurnThemOff) {
	CLights light(ERule::partOne);
	Command commandON{ECommand::turnOn, Point(0,0), Point(0,0)};

	light.execute(commandON);
	Command commandOFF{ECommand::turnOff, Point(0,0), Point(0,0)};
	light.execute(commandOFF);
	ASSERT_EQ(light.getLit(), 0);
}

TEST(lighs, part2) {
	CLights lights(ERule::partTwo);
	Command commandON{ECommand::turnOn, Point(0,0), Point(0,0)};
	lights.execute(commandON);
	ASSERT_EQ(lights.getLit(), 1);
	Command commandToggle{ECommand::toggle, Point(0,0), Point(0,0)};
	lights.execute(commandToggle);
	ASSERT_EQ(lights.getLit(), 3);
	lights.execute(commandToggle);
	ASSERT_EQ(lights.getLit(), 5);
	Command commandOff{ECommand::turnOff, Point(0,0), Point(0,0)};
	lights.execute(commandOff);
	ASSERT_EQ(lights.getLit(), 4);
	lights.execute(commandOff);
	ASSERT_EQ(lights.getLit(), 3);
	lights.execute(commandOff);
	ASSERT_EQ(lights.getLit(), 2);
	lights.execute(commandOff);
	lights.execute(commandOff);
	ASSERT_EQ(lights.getLit(), 0);
	lights.execute(commandOff);
	ASSERT_EQ(lights.getLit(), 0);
}

