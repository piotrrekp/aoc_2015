#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string_view>
#include <stdexcept>
#include <openssl/evp.h>

const std::string_view input{"yzbqklnj"};

using MD5Digest = std::array<unsigned char, 16>;
using MDCTX = std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)>;
using EVPMD = std::unique_ptr<EVP_MD, decltype(&EVP_MD_free)>;

class MD5calculator {
	public:
	MD5calculator() {
		if (!mdctx)
			throw std::runtime_error("nie udało się utworzyć mdctx");
		if (!md)
			throw std::runtime_error("nie udało się utworzyć md");
	}

	MD5Digest calculateMD5(std::string_view in) {
		auto rv = EVP_DigestInit_ex(mdctx.get(), md.get(), nullptr);
		if (rv !=1)
			throw std::runtime_error("nie udało się zainicjować md");
		rv = EVP_DigestUpdate(mdctx.get(), in.data(), in.size());
		if (rv !=1)
			throw std::runtime_error("evp_digestupdate error");
		unsigned int len{};
		MD5Digest result{};
		rv = EVP_DigestFinal_ex(mdctx.get(), result.data(), &len);
		if (rv !=1)
			throw std::runtime_error("evp_digestFinal_ex error");
		return result;
	}
	MDCTX mdctx{EVP_MD_CTX_new(), &EVP_MD_CTX_free};
	const EVPMD md{EVP_MD_fetch(nullptr, "md5", nullptr), &EVP_MD_free};
};

std::string to_string(const std::array<unsigned char, 16> &array) {
	std::stringstream ss;
	for (const auto c : array)
		ss << std::hex << std::setfill('0') << std::setw(2)<< (int)c;
	return ss.str();
}

int main() {
	MD5calculator sol;
	MD5Digest result{};
	std::string keyword{};

	for (std::size_t n = 0; ; ++n) {
		keyword = std::string(input) + std::to_string(n);
		result = sol.calculateMD5(keyword);
		if (result[0] == 0 && result[1] == 0 && result[2] && (result[2] & 0xF0) == 0) {
			break;
		}
	}

	std::cout << "Part one: "  << keyword << " -> " << to_string(result) << std::endl;
	for (std::size_t n = 0; ; ++n) {
		keyword = std::string(input) + std::to_string(n);
		result = sol.calculateMD5(keyword);
		if (result[0] == 0 && result[1] == 0 && result[2] == 0) {
			break;
		}
	}

	std::cout << "Part two: "  << keyword << " -> " << to_string(result) << std::endl;
	return 0;
}
