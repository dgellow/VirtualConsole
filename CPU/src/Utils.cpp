#include "virtualcpu/Utils.hpp"

namespace Utils {
uint16_t to_uint16(char c) {
	unsigned char uc = c;
	return uint16_t(uc);
}

std::ostringstream sstreamDecByte(uint16_t v, unsigned int w) {
	std::ostringstream os;
	os << std::setfill('0') << std::setw(w) << std::dec << v;
	return os;
}

std::ostringstream sstreamHexByte(char c, unsigned int w) {
	std::ostringstream os;
	os << std::setfill('0') << std::setw(w) << std::hex << to_uint16(c);
	return os;
}

std::ostringstream sstreamBoolByte(bool b) {
	std::ostringstream os;
	os << (b ? "true" : "false");
	return os;
}
} // namespace Utils
