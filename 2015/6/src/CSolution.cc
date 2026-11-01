#include "CSolution.h"
#include <algorithm>
#include <array>
#include <charconv>
#include <cmath>
#include <numeric>


namespace aoc2015::day6 {
namespace {
	Point getPointFrom(std::string_view text) {
		auto pos = text.find(',');
		Point p;
		std::from_chars(text.data(), text.data() + pos, p.x);
		text.remove_prefix(pos + 1);
		std::from_chars(text.data(), text.data() + text.size(), p.y);
		return p;
	}
	using namespace std::string_view_literals;
	constexpr std::array commands{
		std::pair{"turn on "sv, ECommand::turnOn},
		std::pair{"turn off "sv, ECommand::turnOff},
		std::pair{"toggle "sv, ECommand::toggle}
	};

	ECommand consumeCommand(std::string_view &text) {
		for (const auto &[t, c] : commands) {
			if (text.starts_with(t)) {
				text.remove_prefix(t.size());
				return c;
			}
		}
		return ECommand::unknown;
	}
} //namespace

	Command getCommand(std::string_view text) {
		const auto com = consumeCommand(text);
		const auto start = getPointFrom(text.substr(0, text.find(" ")));
		const auto end = getPointFrom(text.substr(text.find_last_of(" ") + 1));
		return {com, start, end};
	}


	void CLights::execute(const Command &_command) {
		switch (_command.command) {
		case ECommand::turnOn:
			doIt(_command.start, _command.end, [rule = rule](auto &p) {
				p = rule == ERule::partOne ? 1 : p + 1;});
			break;
		case ECommand::turnOff:
			doIt(_command.start, _command.end, [rule = rule](auto &p) {
				p = rule == ERule::partOne ?   0 : std::max (0, p - 1);});
			break;
		case ECommand::toggle:
			doIt(_command.start, _command.end, [rule = rule](auto &p) {
				p = rule == ERule::partOne ? !p : p + 2;});
			break;
		case ECommand::unknown:
		ddefault:
			break;
		};

	}
	void CLights::doIt(const Point &_start,const Point &_end, std::function<void(int &)> f) {
		auto const startRow = matrix.begin() + _start.y;
		auto const endRow = matrix.begin() + _end.y + 1;

		std::for_each(startRow, endRow, [&](std::array<int, size> &row) {
			std::for_each(row.begin() + _start.x, row.begin() + _end.x + 1, f);
		});
	}

	int CLights::getLit() {
		auto suma = [](int sum, const auto &b) {
			return sum + std::accumulate(b.begin(), b.end(), 0);
		};
		return std::accumulate(matrix.begin(), matrix.end(), 0, suma);
	}

	void CSolution::command(std::string_view _command) {
		lights.execute(getCommand(_command));
	}

	int CSolution::getTurnedLights() {
		return lights.getLit();
	}
}
