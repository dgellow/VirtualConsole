#ifndef SCREEN
#define SCREEN

#include "RAM.hpp"

#include <sstream>

struct Screen : RAM {
  Screen(unsigned int registerWidth, unsigned int registers) : RAM(registerWidth, registers) {}

  ~Screen() {}

  std::ostringstream ostream();
};

#endif /* SCREEN */
