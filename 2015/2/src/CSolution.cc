#include "CSolution.h"
#include <algorithm>
#include <charconv>
#include <stdexcept>

CSolution::CSolution(const std::vector<std::string> &list) {
	boxes.reserve(list.size());
	for (const auto &line : list) {
		boxes.emplace_back(line);
	}
}

CBox::CBox(std::string_view dimension) {
	std::from_chars_result res;

	res = std::from_chars(
			dimension.data(),
			dimension.data() + dimension.size(),
			a);
	if (res.ec != std::errc()
			|| res.ptr == dimension.data() + dimension.size()
			|| *res.ptr != 'x') {
		throw std::invalid_argument("niepoprawne wymiary");
	}
	dimension.remove_prefix(res.ptr - dimension.data() + 1);

	res = std::from_chars(
			dimension.data(),
			dimension.data() + dimension.size(),
			b);
	if (res.ec != std::errc()
			|| res.ptr == dimension.data() + dimension.size()
			|| *res.ptr != 'x') {
		throw std::invalid_argument("niepoprawne wymiary");
	}

	dimension.remove_prefix(res.ptr - dimension.data() + 1);
	res = std::from_chars(
			dimension.data(),
			dimension.data() + dimension.size(),
			c);
	if (res.ec != std::errc() ||
			res.ptr != dimension.data() + dimension.size()) {
		throw std::invalid_argument("niepoprawne wymiary");
	}
}

int CSolution::getNeededSurface(const CBox box) const {
	const auto &[a,b,c] = box;
	int surfaceArea = 2 * (a*b + b*c + a*c);
	int extraWrapping = std::min({a*b, b*c, a*c});
	int vResult = surfaceArea + extraWrapping;

	return vResult;
}

int CSolution::getTotalNeededSurface() const {
	int vResult = 0;
	for (const auto &box:  boxes) {
		vResult += getNeededSurface(box);
	}

	return vResult;
}

int CSolution::getTotalRibbonNeeded() const {
	int vResult = 0;
	for (const auto &box : boxes) {
		vResult += getNeededRibbon(box);
	}

	return vResult;
}

int CSolution::getNeededRibbon(const CBox box) const {
	const auto &[a,b,c] = box;
	int vResult = a * b * c + 2 * (a + b + c);
	int vMax = std::max ({a, b, c});
	vResult -= 2 * vMax;
	return vResult;
}
