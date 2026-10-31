#include "CSolution.h"
#include <algorithm>
#include <array>

namespace aoc2015::day5 {
namespace {

constexpr std::array<std::string_view, 4> excluded{"ab", "cd", "pq", "xy"};

bool hasAtLeast3vowels(std::string_view text) {
	return std::ranges::count_if(text, [](char c){
		return std::string_view{"eaiou"}.find(c) != std::string_view::npos;
	}) >= 3;
}

bool hasAtLeastOneLetterTwiceInRow(std::string_view text) {
	return std::ranges::adjacent_find(text) != text.end();
}

bool notContainExcludedStrings(std::string_view text) {
	return std::ranges::none_of(excluded, [text](auto s){
		return text.find(s) != std::string_view::npos;
	});
}

bool hasPairWithOneLetterBetween(std::string_view text) {
	for (std::size_t i = 0; i + 2 < text.size(); ++i) {
		if (text.at(i) == text.at(i + 2)) return true;
	}
	return false;
}

bool hasRepeatedPair(std::string_view text) {
	for(std::size_t i = 0; i + 2 < text.size(); ++i) {
		if (text.find(text.substr(i, 2), i + 2) != std::string_view::npos)
			return true;
	}
	return false;
}
} //namespace

bool reqPartOne(std::string_view text) {
	return hasAtLeast3vowels(text) &&
		hasAtLeastOneLetterTwiceInRow(text) &&
		notContainExcludedStrings(text);
}

bool reqPartTwo(std::string_view text) {
	return hasPairWithOneLetterBetween(text) && hasRepeatedPair(text);
}
} // namespace aoc2015::day5
