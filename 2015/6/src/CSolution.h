#ifndef _CSOLUTION_H_
#define _CSOLUTION_H_

#include <array>
#include <functional>
#include <ostream>
#include <string_view>
#include <vector>


namespace aoc2015::day6 {
	enum class ECommand {unknown, turnOn, turnOff, toggle};
	enum class ERule{partOne, partTwo};
	struct Point {
		int x{};
		int y{};
		bool operator<=>(const aoc2015::day6::Point &) const = default;
		friend std::ostream &operator<<(std::ostream &os,const aoc2015::day6::Point &point) {
			os << "Point(" << point.x << ", " << point.y << ")";
		return os;
		};
	};
	struct Command {
		ECommand command{};
		Point start{};
		Point end{};
	};

	Command getCommand(std::string_view command);

	constexpr std::size_t size = 1000;

	class CLights {
	public:
		explicit CLights(const ERule &rule) : rule(rule) {};
		void execute(const aoc2015::day6::Command &_command);
		int getLit();

	private:
		void doIt(const Point &_start, const Point &_end, std::function<void(int &)> f);
		std::vector<std::array<int, size>> matrix = std::vector<std::array<int, size>>(size);
		int totalBrightness{0};
		ERule rule;
	};

	class CSolution {
	public:
		explicit CSolution(const ERule &rule) : lights(rule) {};
		void command(std::string_view command);
		int getTurnedLights();
	private:
		CLights lights;

	};

}

#endif // _CSOLUTION_H_


