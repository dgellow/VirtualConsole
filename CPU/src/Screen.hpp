#ifndef __Screen__
#define __Screen__

#include "RAM.hpp"

#include <sstream>

struct Screen : RAM {
  Screen(unsigned int registerWidth, unsigned int registers)
    : RAM(registerWidth, registers) {
  }

  ~Screen() {}

  std::ostringstream ostream();
};

#endif /* __Screen__ */
