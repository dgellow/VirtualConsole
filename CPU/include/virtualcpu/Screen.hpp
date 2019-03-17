#pragma once

#include <sstream>

#include "RAM.hpp"

struct Screen : RAM {
	Screen(unsigned int registerWidth, unsigned int registers) : RAM(registerWidth, registers) {}

	~Screen() {}

	std::ostringstream ostream();
};
