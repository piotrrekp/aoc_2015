#ifndef _CSOLUTION_H_
#define _CSOLUTION_H_

#include <vector>
#include <string>
#include <string_view>

class CBox {
public:
	explicit CBox(std::string_view dimension);
	int a{}, b{}, c{};
};

class CSolution {
public:
	explicit CSolution(const std::vector<std::string> &);
	int getTotalNeededSurface() const;
	int getTotalRibbonNeeded() const;
private:
	int getNeededRibbon(const CBox) const;
	int getNeededSurface(const CBox) const;
	std::vector<CBox> boxes;
};

#endif // _CSOLUTION_H_
