#include <gtest/gtest.h>
#include "../src/CSolution.h"

TEST(tester, getTotalNeededSurface) {
	std::vector<std::string> vList = {"1x1x1"};
	CSolution sol(vList);
	ASSERT_EQ(sol.getTotalNeededSurface(), 7);
}

TEST(tester, getTotalNeededSurface_multipleLine) {
	std::vector<std::string> vList = {"1x1x1", "2x3x4", "1x1x10"};
	CSolution sol(vList);
	ASSERT_EQ(sol.getTotalNeededSurface(), 108);
}

TEST(tester, getTotalRibbon_1) {
	std::vector<std::string> vList = {"2x3x4"};
	CSolution sol(vList);
	ASSERT_EQ(sol.getTotalRibbonNeeded(), 34);

}
