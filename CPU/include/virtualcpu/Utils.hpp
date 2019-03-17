#pragma once

#include <iomanip>
#include <sstream>

namespace Utils {
uint16_t to_uint16(char c);
std::ostringstream sstreamDecByte(uint16_t v, unsigned int w = 4);
std::ostringstream sstreamHexByte(char c, unsigned int w = 2);
std::ostringstream sstreamBoolByte(bool b);
} // namespace Utils
